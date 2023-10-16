#include <glad/gl.h>
#include <GLFW/glfw3.h>


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "renderer.c"
#include "shader.c"

#define STD_WINDOW_HEIGHT 480
#define STD_WINDOW_WIDTH 640


struct background{
    float r, g, b, a;
} mainBG;

void updateBackground(float red, float green, float blue, float alpha)
{
    mainBG.r = red;
    mainBG.g = green;
    mainBG.b = blue;
    mainBG.a = alpha;
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
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
    GLuint shaderProgram, vertexShader, fragmentShader, shaderProgram2, vertexShader2, fragmentShader2; 
    GLuint vertexBuffer[2], vertexArrayBuffer[2], elementBuffer[2];


    /* Initialize the library */
    if (!glfwInit())
    {
        fprintf(stderr, "Unable to Initialize GLFW\n");
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Make the Program Fullscreen

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

    /* Create a Fullscreen window and its OpenGL context */
    window = glfwCreateWindow(mode->width, mode->height, "Poker", monitor, NULL);
    if (!window)
    {
        fprintf(stderr, "Unable to Create Window\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    if (!gladLoadGL(glfwGetProcAddress))
    {
        fprintf(stderr, "Unable to load GLAD\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // Set the framebuffer Size Function
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    shade(&vertexShader, &fragmentShader, &shaderProgram, 1);
    shade(&vertexShader2, &fragmentShader2, &shaderProgram2, 2);
    renderBuffers(&vertexBuffer[0], 2, &vertexArrayBuffer[0], 2, &elementBuffer[0], 2);
    
    
    updateBackground(0.2f, 0.3f, 0.3f, 1.0f);

    // Render Loop
    while (!glfwWindowShouldClose(window))
    {

        // Render Below Here


        glClearColor(mainBG.r, mainBG.g, mainBG.b, mainBG.a);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(vertexArrayBuffer[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);


        glUseProgram(shaderProgram2);
        glBindVertexArray(vertexArrayBuffer[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);



        // Swap Buffers and check events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}