cmake_minimum_required(VERSION 3.22)
project(roguegba LANGUAGES C CXX ASM)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(DEVKITPRO $ENV{DEVKITPRO})
set(DEVKITARM $ENV{DEVKITARM})

if(NOT DEFINED DEVKITPRO)
    message(FATAL_ERROR "Export DEVKITPRO")
endif()

if(NOT DEFINED DEVKITARM)
    message(FATAL_ERROR "Export DEVKITARM")
endif()

set(ENV{PATH} "${DEVKITPRO}/portlibs/gba/bin:${DEVKITPRO}/portlibs/armv4t/bin:${DEVKITPRO}/tools/bin:${DEVKITPRO}/devkitARM/bin:$ENV{PATH}")

set(TOOL_PREFIX "arm-none-eabi-")
set(CMAKE_C_COMPILER "${TOOL_PREFIX}gcc")
set(CMAKE_CXX_COMPILER "${TOOL_PREFIX}g++")
set(CMAKE_ASM_COMPILER "${TOOL_PREFIX}as")
set(CMAKE_AR "${TOOL_PREFIX}gcc-ar")
set(CMAKE_NM "${TOOL_PREFIX}gcc-nm")
set(CMAKE_OBJCOPY "${TOOL_PREFIX}objcopy")
set(CMAKE_RANLIB "${TOOL_PREFIX}gcc-ranlib")
set(CMAKE_STRIP "${TOOL_PREFIX}strip")

include(cmake/gba-functions.cmake)

if(NOT DEFINED GAME_TITLE)
    set(GAME_TITLE ${PROJECT_NAME})
endif()

if(NOT DEFINED GAME_CODE)
    set(GAME_CODE 0000)
endif()

if(NOT DEFINED MAKER_CODE)
    set(MAKER_CODE 00)
endif()

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/source/*.c" "${CMAKE_CURRENT_SOURCE_DIR}/source/*.s")
set(INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(ARCH -mthumb -mthumb-interwork)
set(SPECS ${DEVKITARM}/arm-none-eabi/lib)

add_executable(${GAME_TITLE}.elf
    ${SOURCES})

target_include_directories(${GAME_TITLE}.elf PRIVATE
    ${INCLUDES}
    ${DEVKITPRO}/libtonc/include)

target_compile_options(${GAME_TITLE}.elf PRIVATE
    -g -Wall -O2 -mcpu=arm7tdmi -mtune=arm7tdmi ${ARCH})

target_link_libraries(${GAME_TITLE}.elf PRIVATE
    tonc)

# TODO gba.specs is broken
target_link_options(${GAME_TITLE}.elf PRIVATE
    -specs=${SPECS}/gba.specs -g ${ARCH} -Wl,-Map,${GAME_TITLE}.map)