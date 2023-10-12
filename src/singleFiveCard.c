#include "poker.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define HAND_SIZE 5

struct gameSettings{
    bool jokers; // Are Jokers involved
    short wildCard; // Any Wildcards; 0 if no
}game = {true , 0};

void updateSettings(bool newJokers, short newWildCard)
{
    game.jokers = newJokers;
    game.wildCard = newWildCard;
}

void replaceCard(int* hand, int* deck, int handPos)
{
    hand[handPos] = *deck;
}

void play(void)
{
    int* pDeck = deckStart;
    shuffleCards();
    int hand[5] = {pDeck[0], pDeck[1], pDeck[2], pDeck[3], pDeck[4]};
    pDeck+=5; // Change pDeck to the 5th card
    int* phand = &hand[0];

}