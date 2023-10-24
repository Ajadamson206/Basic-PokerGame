#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <math.h>
#include <map>
#include <string>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "renderer.c"
#include "shader.h"
#include "resource_manager.h"
#include "text_render.h"
#include "game.h"

#define STD_WINDOW_HEIGHT 480
#define STD_WINDOW_WIDTH 640


Game Poker;

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

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

int main(void)
{
    GLFWwindow* window;

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

    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Set the framebuffer Size Function
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Initialize the Poker Game
    Poker.Init(false, 0, mode->width, mode->height);

    // Set the background
    updateBackground(0.212f, 0.631f, 0.212f, 1.0f);

    // Render Loop
    while (!glfwWindowShouldClose(window))
    {

        // Render Below Here


        glClearColor(mainBG.r, mainBG.g, mainBG.b, mainBG.a);
        glClear(GL_COLOR_BUFFER_BIT);

        
        Poker.Render();
        

        //int vertexColorLocation = glGetUniformLocation(shaderProgram, "Color");
        //cardShader.Use();
        //glUniform4f(vertexColorLocation, 1.0f, 1.0f, 1.0f, 1.0f);
        
        //for(int i = 0; i < 5; i++)
        //{
         //   glBindVertexArray(vertexArrayBuffer[i]);
            //glDrawArrays(GL_TRIANGLES, 0, 3);
         //   glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //    glBindVertexArray(0);
       // }
        

        // Swap Buffers and check events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ResourceManager::Clear();

    glfwTerminate();
    return 0;
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (key >= 0 && key < 1024)
    {
        if(action == GLFW_PRESS)
            Poker.Keys[key] = true;
    }
}
