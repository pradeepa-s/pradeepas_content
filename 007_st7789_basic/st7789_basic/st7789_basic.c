#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/structs/systick.h"
#include "lvgl.h"
// #include "hardware/gpio.h"
// #include "pico/time.h"

static bool pending_xfer = false;

static const bool LCD_CMD = false;
static const bool LCD_DATA = true;
static const uint32_t LCD_H_RES = 240;
static const uint32_t LCD_V_RES = 320;
const uint GPIO_LCD_BACKLIGHT_PIN = 2;
const uint GPIO_LCD_DCX = 3;
const uint GPIO_LCD_RESETn = 4;

const uint GPIO_SPI0_RX = 16;
const uint GPIO_SPI0_CSn = 17;
const uint GPIO_SPI0_SCK = 18;
const uint GPIO_SPI0_TX = 19;

static uint32_t tick_count = 0;

static lv_display_t *lcd_disp = NULL;

uint32_t get_tick_count()
{
    return tick_count;
}

void setup_isr()
{
    systick_hw_t* systick = systick_hw;
    systick->cvr = 0x00;
    systick->csr = 0x07;
    systick->rvr = 124999;
}

extern void isr_systick()
{
    tick_count++; 
}

static void send_lcd_cmd(lv_display_t *disp, const uint8_t *cmd, size_t cmd_size, const uint8_t *param, size_t param_size)
{
    if (!disp || !cmd) {
        return;
    }

    while (pending_xfer);

    gpio_put(GPIO_LCD_DCX, LCD_CMD);
    gpio_put(GPIO_SPI0_CSn, false);
    spi_set_format(spi0, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);
    spi_write_blocking(spi0, cmd, cmd_size);
    
    if (param) {
        gpio_put(GPIO_LCD_DCX, LCD_DATA);
        spi_write_blocking(spi0, param, param_size);
    }

    gpio_put(GPIO_SPI0_CSn, true);
}

static void send_lcd_data(lv_display_t *disp, const uint8_t *cmd, size_t cmd_size, uint8_t *param, size_t param_size)
{
    if (!disp || !cmd) {
        return;
    }

    // Send the LCD command first
    gpio_put(GPIO_LCD_DCX, LCD_CMD);
    gpio_put(GPIO_SPI0_CSn, false);
    spi_set_format(spi0, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);
    spi_write_blocking(spi0, cmd, cmd_size);
   
    // Send LCD data if available
    if (param) {
        // The data write is alwways 16 bits.
        // The data transfer is MSB first. Refer 8.8.42 in ST7789 datasheet
        uint16_t* data = (uint16_t*)param;
        size_t data_size = param_size / 2;
        spi_set_format(spi0, 16, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);
        gpio_put(GPIO_LCD_DCX, LCD_DATA);
        spi_write16_blocking(spi0, data, data_size);
    }

    gpio_put(GPIO_SPI0_CSn, true);

    // Tell LVGL that the transfer is complete and we are ready for the next set of data.
    lv_display_flush_ready(disp);
}

static void initialise_lcd_hw()
{
	// Backlight
    gpio_init(GPIO_LCD_BACKLIGHT_PIN);
    gpio_set_dir(GPIO_LCD_BACKLIGHT_PIN, GPIO_OUT);

    // LCD reset pin
    gpio_init(GPIO_LCD_RESETn);
    gpio_set_dir(GPIO_LCD_RESETn, GPIO_OUT);

    // DCX pin
    gpio_init(GPIO_LCD_DCX);
    gpio_set_dir(GPIO_LCD_DCX, GPIO_OUT);

	// SPI initialisation
    gpio_init(GPIO_SPI0_CSn);  // Software controlled
    gpio_set_dir(GPIO_SPI0_CSn, GPIO_OUT);

    gpio_init(GPIO_SPI0_RX);
    gpio_init(GPIO_SPI0_SCK);
    gpio_init(GPIO_SPI0_TX);
    gpio_set_function(GPIO_SPI0_RX, GPIO_FUNC_SPI);
    gpio_set_function(GPIO_SPI0_SCK, GPIO_FUNC_SPI);
    gpio_set_function(GPIO_SPI0_TX, GPIO_FUNC_SPI);
    const uint baud = spi_init(spi0, 50000000);   // Maximum supported is 62.5 MHz
    printf("SPI initialised with: %d baudrate\n\r", baud);

    // Switch on backlight
    gpio_put(GPIO_LCD_BACKLIGHT_PIN, 1);

    // Reset the LCD
    gpio_put(GPIO_LCD_RESETn, false);
    sleep_ms(25);   // This needs to be more than 10 us
    gpio_put(GPIO_LCD_RESETn, true);
    sleep_ms(125);   // The worst case time is 120 ms

    gpio_put(GPIO_LCD_DCX, LCD_DATA);
    gpio_put(GPIO_SPI0_CSn, true);
}

static void initialise_lvgl_framework()
{
    // Initialise the library
	lv_init();

    // Set the tick count callbcak
    lv_tick_set_cb(get_tick_count);

    // Setup the display
    lcd_disp = lv_st7789_create(LCD_H_RES, LCD_V_RES, LV_LCD_FLAG_NONE, send_lcd_cmd, send_lcd_data);

    // Colour setting is governed by LV_COLOR_DEPTH. It's set to 16 which leads to RGB565 color format
    // being native.
    lv_disp_set_rotation(lcd_disp, LV_DISP_ROTATION_0);

    lv_color_t *buf1 = NULL;
    lv_color_t *buf2 = NULL;

    // For partial rendering the buffer is set to 1/10th of display size
    const uint32_t buf_size = LCD_H_RES * LCD_V_RES * lv_color_format_get_size(lv_display_get_color_format(lcd_disp)) / 10;
    buf1 = lv_malloc(buf_size);
    if (buf1 == NULL) {
        printf("Buffer1 allocation failed!\n\r");
        return;
    }

    buf2 = lv_malloc(buf_size);
    if (buf2 == NULL) {
        printf("Buffer2 allocation failed!\n\r");
        lv_free(buf1);
        return;
    }

    lv_display_set_buffers(lcd_disp, buf1, buf2, buf_size, LV_DISPLAY_RENDER_MODE_PARTIAL);
}

static void ui_init(lv_display_t *disp)
{
    /* set screen background to yellow */
    lv_obj_t *scr = lv_screen_active();
    lv_obj_set_style_bg_color(scr, lv_color_hex(0xFFFB00), 0);
    lv_obj_set_style_bg_opa(scr, LV_OPA_100, 0);
}

int main()
{
    stdio_init_all();
    setup_isr();
    initialise_lcd_hw();
    initialise_lvgl_framework();
    ui_init(lcd_disp);

    printf("Hello, world!\n");
    while (true) {
        lv_timer_handler();
    }
}
