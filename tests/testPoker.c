#include "../src/poker.h"
#include <stdio.h>
#include <stdlib.h>

// Use this file to test different changes to the "poker.h" file
/*
void testShuffle()
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
*/

void testSort()
{
    printf("test\n");
    int hands[] = {9, 4, 89, 23, 4};
    for(int i = 0; i < 5; i++)
        printf("%d,", hands[i]);
    sort(&hands[0], 5);
    for(int i = 0; i < 5; i++)
        printf("%d,", hands[i]);

}

int main()
{
    testSort();
    return 0;
}