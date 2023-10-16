#include <glad/gl.h>
#include <GLFW/glfw3.h>


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>


static float triangleOne[] = {
    // Triangle One
    -0.9f, -0.5f, 0.0f, // Top Right
    -0.f, -0.5f, 0.0f, // Bottom Right
    -0.45f, 0.5f, 0.0f, // Top Left
};
static float triangleTwo[] = {
    0.0f, -0.5f, 0.0f,
    0.9f, -0.5f, 0.0f,
    0.45f, 0.5f, 0.0f
};

static unsigned int indices[] = {
    0, 1, 2,
    1, 3, 2
};

static void renderBuffers(GLuint *vertexBuffer, unsigned int numVB, GLuint *vertexArrayBuffer, unsigned int numVAB, GLuint *elementBuffer, unsigned int numEB){
    // _________________________________________________
    // Vertex Arrays

    glGenVertexArrays(numVAB, vertexArrayBuffer);
    glGenBuffers(numVB, vertexBuffer);
    glGenBuffers(numEB, elementBuffer);

    // First Triangle

    glBindVertexArray(*vertexArrayBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, *vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleOne), triangleOne, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *elementBuffer);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    // Triangle Two
    glBindVertexArray(*(vertexArrayBuffer+1));
    glBindBuffer(GL_ARRAY_BUFFER, *(vertexBuffer+1));
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleTwo), triangleTwo, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindVertexArray(0);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

}

static void renderCard(int cardSuit, int cardValue, int cardPos)
{
    /*  
    cardSuit ->
        1 = Diamonds
        2 = Spaces
        3 = Hearts
        4 = Clubs

    cardValue ->
        1 = Ace
        2-10
        11 = Jack
        12 = Queen
        13 = King
    
    cardPos ->
        0 = First
        1 = Second
        2 = Third
        3 = Fourth
        4 = Fifth
    */

}
