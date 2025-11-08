#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/structs/systick.h"
// #include "hardware/gpio.h"
// #include "pico/time.h"

static const bool LCD_CMD = false;
static const bool LCD_DATA = true;

const uint GPIO_LCD_BACKLIGHT_PIN = 2;
const uint GPIO_LCD_DCX = 3;
const uint GPIO_LCD_RESETn = 4;

const uint GPIO_SPI0_RX = 16;
const uint GPIO_SPI0_CSn = 17;
const uint GPIO_SPI0_SCK = 18;
const uint GPIO_SPI0_TX = 19;

static uint32_t tick_count = 0;

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


int main()
{
    stdio_init_all();
    setup_isr();
    initialise_lcd_hw();
    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
