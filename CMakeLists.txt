PROJECT(uBITXFly C)
CMAKE_MINIMUM_REQUIRED(VERSION 3.14)
SET(STM32CubeF0_FW ${CMAKE_SOURCE_DIR}/../STM32Cube_FW_F0_V1.11.0)
SET(STLINK_BIN ${CMAKE_SOURCE_DIR}/../TOOLS/st-flash)

IF(NOT EXISTS "${STM32CubeF0_FW}")
	MESSAGE( FATAL_ERROR "Not found STM32CubeF0 FW 1.11.0, please download from st.com." )
ENDIF()

IF(NOT EXISTS "${STLINK_BIN}")
	MESSAGE( WARNING "Not found st-flash, disable flash command." )
ENDIF()

INCLUDE_DIRECTORIES(
    ${STM32CubeF0_FW}/Drivers/CMSIS/Include/
    ${STM32CubeF0_FW}/Drivers/CMSIS/Device/ST/STM32F0xx/Include/
    ${STM32CubeF0_FW}/Drivers/STM32F0xx_HAL_Driver/Inc/
    Inc
)
SET(HAL_LIB_SRC ${STM32CubeF0_FW}/Drivers/STM32F0xx_HAL_Driver/Src/)

SET(CMAKE_VERBOSE_MAKEFILE OFF)
SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_BUILD_TYPE RELEASE)
SET(CMAKE_C_COMPILER "arm-none-eabi-gcc")
SET(CMAKE_LINKER "arm-none-eabi-ld")
SET(CMAKE_OBJCOPY "arm-none-eabi-objcopy")
SET(CMAKE_SIZE "arm-none-eabi-size")

SET(FAMILY "STM32F070x6")

SET(LINK_SCRIPT ${CMAKE_SOURCE_DIR}/Boot/STM32F070F6Px_FLASH.ld)

SET(STARTUP Boot/startup_stm32f070x6.s Boot/system_stm32f0xx.c)
SET_PROPERTY(SOURCE Boot/startup_stm32f070x6.s PROPERTY LANGUAGE C)

SET(STARTUP ${STARTUP}
    ${HAL_LIB_SRC}/stm32f0xx_hal.c
    ${HAL_LIB_SRC}/stm32f0xx_hal_cortex.c
    ${HAL_LIB_SRC}/stm32f0xx_hal_rcc.c
    ${HAL_LIB_SRC}/stm32f0xx_hal_rcc_ex.c
    ${HAL_LIB_SRC}/stm32f0xx_hal_gpio.c
    ${HAL_LIB_SRC}/stm32f0xx_hal_uart.c
    ${HAL_LIB_SRC}/stm32f0xx_hal_i2c.c
    ${HAL_LIB_SRC}/stm32f0xx_hal_i2c_ex.c
    ${HAL_LIB_SRC}/stm32f0xx_hal_dma.c
)

SET(SRC Src/main.c Src/stm32f0xx_it.c Src/stm32f0xx_hal_msp.c)

SET(CMAKE_C_FLAGS_DEBUG "-O0 -g -ggdb")
SET(CMAKE_C_FLAGS_RELEASE "-O2")

SET(CMAKE_VERBOSE_MAKEFILE OFF)

SET(MCU_FLAGS "-mlittle-endian -mcpu=cortex-m0 -march=armv6-m -mthumb -mfloat-abi=soft ")
SET(CMAKE_C_FLAGS "${MCU_FLAGS} -Wall --std=gnu99 -Wl,--gc-sections -ffreestanding -fno-builtin  -ffunction-sections -fdata-sections")
ADD_DEFINITIONS(-D${FAMILY} -DUSE_HAL_DRIVER)
SET(CMAKE_EXE_LINKER_FLAGS "--specs=nano.specs --specs=nosys.specs -lc -static -Wl,--cref -Wl,-Map=STM32F070x6.map  -Wl,--gc-section -T${LINK_SCRIPT}")

SET(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM BOTH)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

ADD_EXECUTABLE(${PROJECT_NAME}.elf ${SRC} ${STARTUP})

ADD_CUSTOM_COMMAND(DEPENDS ${PROJECT_NAME}.elf OUTPUT ${PROJECT_NAME}.hex COMMAND ${CMAKE_OBJCOPY} -Oihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex)
ADD_CUSTOM_COMMAND(DEPENDS ${PROJECT_NAME}.elf OUTPUT ${PROJECT_NAME}.bin COMMAND ${CMAKE_OBJCOPY} -Obinary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin)
ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME}.elf POST_BUILD COMMAND ${CMAKE_SIZE} -x -A ${PROJECT_NAME}.elf)

ADD_CUSTOM_TARGET(generate_bin ALL DEPENDS ${PROJECT_NAME}.bin)
ADD_CUSTOM_TARGET(generate_hex ALL DEPENDS ${PROJECT_NAME}.hex)

ADD_CUSTOM_TARGET(flash ${STLINK_BIN} --format ihex write ${PROJECT_NAME}.hex DEPENDS ${PROJECT_NAME}.hex)
