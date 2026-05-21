#include <iostream>
#include "Objects.h"
#include <vector>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#define RENDER_HEIGHT 480
#define RENDER_WIDTH 640

// From what i understand it displays byt the "triangles" method the whole window dividing it into two small triangles
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

    // ustawienie wersji
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(RENDER_WIDTH, RENDER_HEIGHT, "Ray-tracer", NULL, NULL);
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
    std::vector<unsigned char> pixels(RENDER_WIDTH * RENDER_HEIGHT * 3);

    // tworzenie tekstury
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    GLuint program = createProgram();
    glUseProgram(program);
    glUniform1i(glGetUniformLocation(program, "tex"), 0);

    int fbWidth, fbHeight;
    glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
    glViewport(0, 0, fbWidth, fbHeight);

    // example objects created to test if it even works
    Raytracer::Material new_material;
    new_material.color = &Colors::White;
    new_material.reflectivity = 0.0f;
    Raytracer::Sphere *s1 = new Raytracer::Sphere(0.0f, 0.0f, 0.0f, &new_material, 1.0f);

    while (!glfwWindowShouldClose(window))
    {
        // narzucanie na piksele tego co juz obliczone  (narazie kropka XD)
        for (int i = 0; i < pixels.size(); i++) {
            pixels[i] = 0;
        }

        int h = RENDER_HEIGHT/2;
        int w = RENDER_WIDTH/2;
        int i = (h * RENDER_WIDTH + w) * 3;
        // testowanie tych kolorow wgl
        pixels[i] = Colors::White.red;
        pixels[i+1] = Colors::White.green;
        pixels[i+2] = Colors::White.blue;

        glClearColor(0,0,0,1);
        glClear(GL_COLOR_BUFFER_BIT);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
    
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
            RENDER_WIDTH,
            RENDER_HEIGHT,
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

    delete s1;
    s1 = nullptr;

    return 0;
}