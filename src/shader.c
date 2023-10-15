#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

static const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

static const char *orangeFragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n";
static const char *yellowFragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f, 1.0f, 0.2f, 1.0f);\n"
"}\n";

static void shade(GLuint* vertexShader, GLuint* fragmentShader, GLuint* shaderProgram, unsigned int color)
{
    // Error Checking
    int success;
    char infoLog[512];

    
    // Compile the vertex shader
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
    if(color)
        glShaderSource(*fragmentShader, 1, &orangeFragmentShaderSource, NULL);
    else
        glShaderSource(*fragmentShader, 1, &yellowFragmentShaderSource, NULL);
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
    //glDeleteShader(*vertexShader);
    //glDeleteShader(*fragmentShader);

}