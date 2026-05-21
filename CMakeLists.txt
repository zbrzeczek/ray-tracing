cmake_minimum_required(VERSION 3.10)
project(OpenGLApp)

set(CMAKE_CXX_STANDARD 17)

# GLFW (installed via brew)
find_package(glfw3 REQUIRED)

add_executable(app
    src/main.cpp
    src/Objects.cpp
    src/Vec3.cpp
    glad/src/glad.c
)

target_include_directories(app PRIVATE
    glad/include
    /opt/homebrew/include
)

target_link_libraries(app PRIVATE
    glfw
    "-framework OpenGL"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)
