#include <glad/gl.h>
#include <GLFW/glfw3.h>


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define STD_WINDOW_HEIGHT 480
#define STD_WINDOW_WIDTH 640

struct background{
    float r, g, b, a;
} mainBG;

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.5f, 0.5f, 0.0f
};

void updateBackground(float red, float green, float blue, float alpha)
{
    mainBG.r = red;
    mainBG.g = green;
    mainBG.b = blue;
    mainBG.a = alpha;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    switch (key)
    {
    case GLFW_KEY_ESCAPE:
        glfwSetWindowShouldClose(window, true);
        break;
    case GLFW_KEY_SPACE:
        mainBG.r = 1.0f;
        mainBG.g = 0.0f;
        mainBG.b = 0.0f;    
        break;
    }
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(STD_WINDOW_WIDTH, STD_WINDOW_HEIGHT, "Poker", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    if (!gladLoadGL(glfwGetProcAddress))
    {
        fprintf(stderr, "Unable to load GLAD\n");

    }

    // Set the framebuffer Size Function
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Default Background Color
    updateBackground(0.2f, 0.3f, 0.3f, 1.0f);

    // Render Loop
    while (!glfwWindowShouldClose(window))
    {

        // Render Below Here

        glClearColor(mainBG.r, mainBG.g, mainBG.b, mainBG.a);
        glClear(GL_COLOR_BUFFER_BIT);




        // Swap Buffers and check events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}