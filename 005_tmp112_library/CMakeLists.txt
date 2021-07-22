cmake_minimum_required(VERSION 3.10)

project(tmp112_lib_test)

add_subdirectory(../googletest gtest)
# include(FetchContent)
# FetchContent_Declare(
#   googletest
#   URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
# )
# # For Windows: Prevent overriding the parent project's compiler/linker settings
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# FetchContent_MakeAvailable(googletest)

add_executable(
    tmp112_lib_test test_tmp112_sensor.cpp tmp112_sensor.c fake_i2c_driver.cpp)
target_link_libraries(tmp112_lib_test gtest_main)

include(GoogleTest)
gtest_discover_tests(tmp112_lib_test)

