#include <iostream>
#include "Vec3.h"
#include <vector>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#define HEIGHT 480
#define WIDTH 640

// From what i understand it displays byt the "triangles" method the one pixel, dividing it into two small triangles
const char* vertexShaderSrc = R"(
#version 410 core

out vec2 uv;

void main() {
    vec2 pos[6] = vec2[](
        vec2(-1,-1), vec2(1,-1), vec2(1,1), 
        vec2(-1,-1), vec2(1,1), vec2(-1,1)
    );
    vec2 p = pos[gl_VertexID];
    uv = (p + 1.0) * 0.5;
    gl_Position = vec4(p, 0, 1);
}
)";

// this is the shader for coloring the pixels, here i just pass the colors through texture function
// bc the color will be calculated not by opengl but raytracer directly
const char* fragmentShaderSrc = R"(
#version 410 core

in vec2 uv;
out vec4 color;
uniform sampler2D tex;

void main() {
    color = texture(tex, uv);
}
)";


struct Vec {
    Vec3 *position;
    float colors[3];
};

Vec3 pixel(0.0f, 0.0f, 0.0f);
// Vec example;
// example.position = pixel;
// colors = [0.2f, 0.4f, 0.2f];

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

// wyjscie z okna
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

GLuint compileShader(GLenum type, const char* src) {
    GLuint s = glCreateShader(type);
    glShaderSource(s, 1, &src, NULL);
    glCompileShader(s);
    return s;
}

GLuint createProgram() {
    GLuint vs = compileShader(GL_VERTEX_SHADER, vertexShaderSrc);
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSrc);
    GLuint p = glCreateProgram();

    glAttachShader(p, vs);
    glAttachShader(p, fs);
    glLinkProgram(p);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return p;
}

int main() {
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Ray-tracer", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, key_callback);

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "GLAD failed\n";
    }

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // jak czesto te buffory beda sie zmieniac (sa 2 - ten co widac i ten do ktorego renderujesz)
    glfwSwapInterval(1);

    // tutaj jest matryca pikseli z czego kazdy ma 3 wartosci r g b 
    // co petle bedzie narzucanie pikseli na podstawie ray tracera
    std::vector<unsigned char> pixels(WIDTH * HEIGHT * 3);

    // tworzenie tekstury
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    GLuint program = createProgram();
    glUseProgram(program);
    glUniform1i(glGetUniformLocation(program, "tex"), 0);

    while (!glfwWindowShouldClose(window))
    {

        glViewport(0, 0, WIDTH, HEIGHT);
        // narzucanie na piksele tego co juz obliczone  (narazie kropka XD)
        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                int i = (y * WIDTH + x) * 3;
        
                pixels[i + 0] = (unsigned char)(x % 255);   // R gradient
                pixels[i + 1] = (unsigned char)(y % 255);   // G gradient
                pixels[i + 2] = 80;         
            }
        }

        glClearColor(0,0,0,1);
        glClear(GL_COLOR_BUFFER_BIT);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
    
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
            WIDTH,
            HEIGHT,
            0,
            GL_RGB,
            GL_UNSIGNED_BYTE,
            pixels.data());       
    
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // wymiana bufferow ktore sa wyswietlane
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}