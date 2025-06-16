# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 1.5.1)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

cmake_minimum_required(VERSION 3.12)

# Set any variables required for importing libraries
if (DEFINED ENV{FREERTOS_PATH})
  SET(FREERTOS_PATH $ENV{FREERTOS_PATH})
else()
  SET(FREERTOS_PATH ${CMAKE_CURRENT_LIST_DIR}/FreeRTOS)
endif()

message("FreeRTOS Kernel located in ${FREERTOS_PATH}")

# Import those libraries
include(pico_sdk_import.cmake)
include(${FREERTOS_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)

# Define project
project(rp2040-freertos-template C CXX ASM)

# Initialize the Raspberry Pi Pico SDK
pico_sdk_init()

add_executable(rp2040-freertos-template
    main.c
  ./drivers/buttons_driver.c
  ./drivers/buzzer_driver.c
  ./drivers/joystick_driver.c
  ./drivers/ssd1306_i2c.c
  ./drivers/led_rgb_driver.c
  ./hal/hal_buttons.c
  ./hal/hal_buzzer.c
  ./hal/hal_joystick.c
  ./hal/hal_ssd1306.c
  ./hal/hal_led_rgb.c
)

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(rp2040-freertos-template 0)
pico_enable_stdio_usb(rp2040-freertos-template 1)

target_include_directories(rp2040-freertos-template PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_libraries(rp2040-freertos-template 
    pico_stdlib 
    FreeRTOS-Kernel-Heap4 
    hardware_gpio
    hardware_pio
    hardware_adc
    hardware_dma
    hardware_pwm
    hardware_i2c
    )

pico_add_extra_outputs(rp2040-freertos-template)

# if you have anything in "lib" folder then uncomment below - remember to add a CMakeLists.txt
# file to the "lib" directory
#add_subdirectory(lib)
