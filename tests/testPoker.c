#include "../src/poker.h"
#include <stdio.h>

// Use this file to test different changes to the "poker.h" file

int main()
{
    printf("Original Deck: ");
    for(int i = 0; i < SIZE_OF_DECK; i++)
        printf("%d,", deck[i]);
    printf("\n");
    shuffleCards();
    printf("Shuffled Deck: ");
    for(int i = 0; i < SIZE_OF_DECK; i++)
        printf("%d,", deck[i]);
    printf("\n");
    resetDeck();
    printf("Reset Deck: ");
    for(int i = 0; i < SIZE_OF_DECK; i++)
        printf("%d,", deck[i]);
    printf("\n");
}