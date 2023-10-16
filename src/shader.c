#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Load Shaders from a file
static const char* getShaderContent(char* fileName)
{
    FILE *shaderSource;
    long size = 0;
    char* shaderContent;
    
    /* Read File to get size */
    shaderSource = fopen(fileName, "rb");
    if(shaderSource == NULL) {
        fprintf(stderr, "Unable to read shader\n");
        return "";
    }
    fseek(shaderSource, 0L, SEEK_END);
    size = ftell(shaderSource)+1;
    fclose(shaderSource);

    /* Read File for Content */
    shaderSource = fopen(fileName, "r");
    shaderContent = memset(malloc(size), '\0', size);
    fread(shaderContent, 1, size-1, shaderSource);
    fclose(shaderSource);

    return shaderContent;
}

static void shade(GLuint* vertexShader, GLuint* fragmentShader, GLuint* shaderProgram, unsigned int color)
{
    // Error Checking
    int success;
    char infoLog[512];

    
    // Compile the vertex shader
    const char* vertexShaderSource = getShaderContent("src/shaders/vertex.glsl");
    *vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(*vertexShader, 1 , &vertexShaderSource, NULL);
    glCompileShader(*vertexShader);

    // Get Vertex Shader Compile Status
    glGetShaderiv(*vertexShader, GL_COMPILE_STATUS, &success);

    // Failed Vertex Shader Compile
    if (!success)
    {
        glGetShaderInfoLog(*vertexShader, 512, NULL, infoLog);
        fprintf(stderr, "VERTEX SHADER COMPILE ERROR\n%s\n", infoLog);
    }

    // Compile the Fragment Shader
    *fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    if(color == 1)
    {
        const char* orangeFragmentShaderSource = getShaderContent("src/shaders/orange.glsl");
        glShaderSource(*fragmentShader, 1, &orangeFragmentShaderSource, NULL);
    }
    else
    {
        const char* yellowFragmentShaderSource = getShaderContent("src/shaders/yellow.glsl");
        glShaderSource(*fragmentShader, 1, &yellowFragmentShaderSource, NULL);
    }
    glCompileShader(*fragmentShader); 
   
    
    
    // Get Fragment Shader Compile Status
    glGetShaderiv(*fragmentShader, GL_COMPILE_STATUS, &success);

    // Failed Fragment Shader Comile
    if(!success)
    {
        glGetShaderInfoLog(*fragmentShader, 512, NULL, infoLog);
        fprintf(stderr, "FRAGEMENT SHADER COMPILE ERROR\n%s\n", infoLog);
    }


    // Generate Shader Program
    *shaderProgram = glCreateProgram();
    glAttachShader(*shaderProgram, *vertexShader);
    glAttachShader(*shaderProgram, *fragmentShader);
    glLinkProgram(*shaderProgram);

    // Get Shader Program Status
    glGetProgramiv(*shaderProgram, GL_LINK_STATUS, &success);

    // Check Shader Program Status
    if(!success)
    {
        glGetProgramInfoLog(*shaderProgram, 512, NULL, infoLog);
        fprintf(stderr, "UNABLE TO LINK SHADER PROGRAM\n%s\n", infoLog);
    }
   
    // Delete Already Linked Shaders
    glDeleteShader(*vertexShader);
    glDeleteShader(*fragmentShader);

}