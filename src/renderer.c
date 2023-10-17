#include <glad/gl.h>
#include <GLFW/glfw3.h>


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define bottomX -0.95f
#define bottomY -0.8f

#define cardGap 0.04f
#define cardLength 0.352f

#define topX -0.61f
#define topY 0.2f

static float card0[] = {
    // Card0
    bottomX, bottomY, 0.0f, // top right
    bottomX, topY, 0.0f, // bottom right
    bottomX+cardLength, topY, 0.0f, // bottom left
    bottomX+cardLength, bottomY, 0.0f // top left
};
static float card1[] = {
    // Card1
    bottomX+cardLength+cardGap, bottomY, 0.0f, // top right
    bottomX+cardLength+cardGap, topY, 0.0f, // bottom right
    bottomX+(2.0*cardLength)+cardGap, topY, 0.0f, // bottom left
    bottomX+(2.0*cardLength)+cardGap, bottomY, 0.0f // top left
};
static float card2[] = {
    // Card2
    bottomX+(2.0*cardLength)+(2.0*cardGap), bottomY, 0.0f, // Bottom Left
    bottomX+(2.0*cardLength)+(2.0*cardGap), topY, 0.0f, // Top Left
    bottomX+(3.0*cardLength)+(2.0*cardGap), topY, 0.0f, // Top Right
    bottomX+(3.0*cardLength)+(2.0*cardGap), bottomY, 0.0f // Bottom Right
};
static float card3[] = {
    // Card3
    bottomX+(3.0*cardLength)+(3.0*cardGap), bottomY, 0.0f, // top right
    bottomX+(3.0*cardLength)+(3.0*cardGap), topY, 0.0f, // bottom right
    bottomX+(4.0*cardLength)+(3.0*cardGap), topY, 0.0f, // bottom left
    bottomX+(4.0*cardLength)+(3.0*cardGap), bottomY, 0.0f // top left
};
static float card4[] = {
    // Card4
    bottomX+(4.0*cardLength)+(4.0*cardGap), bottomY, 0.0f, // top right
    bottomX+(4.0*cardLength)+(4.0*cardGap), topY, 0.0f, // bottom right
    bottomX+(5.0*cardLength)+(4.0*cardGap), topY, 0.0f, // bottom left
    bottomX+(5.0*cardLength)+(4.0*cardGap), bottomY, 0.0f // top left
};


static unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
};

static void renderCards(GLuint *vertexBuffer, GLuint *vertexArrayBuffer, GLuint *elementBuffer, int numCards){
    // _________________________________________________
    // Vertex Arrays

    glGenVertexArrays(numCards, vertexArrayBuffer);
    glGenBuffers(numCards, vertexBuffer);
    glGenBuffers(numCards, elementBuffer);

    // First Triangle
    for(int i = 0; i < numCards; i++)
    {
        static float *card;
        switch(i)
        {
            case 0:
                card = card0;
                break;
            case 1:
                card = card1;
                break;
            case 2:
                card = card2;
                break;
            case 3:
                card = card3;
                break;
            case 4:
                card = card4;
                break;
        }

        glBindVertexArray(*vertexArrayBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, *vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(card0), card, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *elementBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
        vertexArrayBuffer++;
        vertexBuffer++;
        elementBuffer++;
    }
    /* Triangle Two
    glBindVertexArray(*(vertexArrayBuffer+1));
    glBindBuffer(GL_ARRAY_BUFFER, *(vertexBuffer+1));
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleTwo), triangleTwo, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);
    */

    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindVertexArray(0);

#ifdef DEBUG
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#endif
}

//static void renderCard(struct handCard card, int position)
//{
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




//}
