cmake_minimum_required(VERSION 3.5)
project(simplekv LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# this setting can export compile_commands.json file for include path searching for VScode
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(
    -Wall # print warning info
    -Wextra # print extra warning info
)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
        message(STATUS "Setting build type to `Debug` as none was specified.")
        set(CMAKE_BUILD_TYPE "Debug")
endif()

set(SIMPLEKV_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})

include_directories(${SIMPLEKV_ROOT_DIR})
include(${SIMPLEKV_ROOT_DIR}/cmake/basic.cmake)
