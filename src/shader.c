#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ORANGE_FILE "src/shaders/orange.glsl"
#define YELLOW_FILE "src/shaders/yellow.glsl"
#define WHITE_FILE "src/shaders/white.glsl"
#define RUN_TIME_COLOR "src/shaders/runTimeColor.glsl"
#define VERTEX_FILE "src/shaders/vertex.glsl"
#define RED_FILE "src/shaders/red.glsl"
#define BLACK_FILE "src/shaders/black.glsl"

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

static GLuint shade(char* color)
{
    GLuint vertexShader, fragmentShader, shaderProgram;

    // Error Checking
    int success;
    char infoLog[512];

    
    // Compile the vertex shader
    const char* vertexShaderSource = getShaderContent(VERTEX_FILE);
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1 , &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Get Vertex Shader Compile Status
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    // Failed Vertex Shader Compile
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        fprintf(stderr, "VERTEX SHADER COMPILE ERROR\n%s\n", infoLog);
    }

    // Compile the Fragment Shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentShaderSource = getShaderContent(color);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader); 
    
    // Get Fragment Shader Compile Status
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    // Failed Fragment Shader Comile
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        fprintf(stderr, "FRAGEMENT SHADER COMPILE ERROR\n%s\n", infoLog);
    }


    // Generate Shader Program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Get Shader Program Status
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    // Check Shader Program Status
    if(!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        fprintf(stderr, "UNABLE TO LINK SHADER PROGRAM\n%s\n", infoLog);
    }
   
    // Delete Already Linked Shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}