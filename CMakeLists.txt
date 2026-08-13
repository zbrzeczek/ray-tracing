cmake_minimum_required(VERSION 3.10)
project(RayTracer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(app
    src/main.cpp
    src/Objects.cpp
)

target_include_directories(app PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Compiler-specific settings
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # MSVC (Visual Studio) configuration
    message(STATUS "Building with MSVC")
    target_compile_options(app PRIVATE /W4)
else()
    # GCC and Clang configuration (MinGW, Linux, macOS)
    message(STATUS "Building with GCC/Clang")
    target_compile_options(app PRIVATE -Wall -Wextra)
endif()
