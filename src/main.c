#include <glad/gl.h>
#include <GLFW/glfw3.h>


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "singleFiveCard.c"
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
    case GLFW_KEY_A:   
        double mouseX, mouseY;
        glfwGetCursorPos(window,&mouseX, &mouseY);
        printf("MouseX: %f, MouseY: %f\n", mouseX, mouseY);
        break;
    case GLFW_KEY_1:
        if(action == GLFW_PRESS)
            if(posReplace[0])
                posReplace[0] = false;
            else
                posReplace[0] = true;
        break;
    case GLFW_KEY_2:
        if(action == GLFW_PRESS)
            if(posReplace[1])
                posReplace[1] = false;
            else
                posReplace[1] = true;
        break;
    case GLFW_KEY_3:
        if(action == GLFW_PRESS)
            if(posReplace[2])
                posReplace[2] = false;
            else
                posReplace[2] = true;
        break;
    case GLFW_KEY_4:
        if(action == GLFW_PRESS)
            if(posReplace[3])
                posReplace[3] = false;
            else
                posReplace[3] = true;
        break;
    case GLFW_KEY_5:
        if(action == GLFW_PRESS)
            if(posReplace[4])
                posReplace[4] = false;
            else
                posReplace[4] = true;
        break;
    }
}

int main(void)
{
    GLFWwindow* window;
    GLuint vertexBuffer[5], vertexArrayBuffer[5], elementBuffer[5];


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

    GLuint whiteProgram = shade(WHITE_FILE);
    renderCards(&vertexBuffer[0], &vertexArrayBuffer[0], &elementBuffer[0], 5);
    
    
    updateBackground(0.212f, 0.631f, 0.212f, 1.0f);

    // Render Loop
    while (!glfwWindowShouldClose(window))
    {

        // Render Below Here


        glClearColor(mainBG.r, mainBG.g, mainBG.b, mainBG.a);
        glClear(GL_COLOR_BUFFER_BIT);

        //int vertexColorLocation = glGetUniformLocation(shaderProgram, "Color");
        glUseProgram(whiteProgram);
        //glUniform4f(vertexColorLocation, 1.0f, 1.0f, 1.0f, 1.0f);
        for(int i = 0; i < 5; i++)
        {
            glBindVertexArray(vertexArrayBuffer[i]);
            //glDrawArrays(GL_TRIANGLES, 0, 3);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }

        // Swap Buffers and check events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}