#include "poker.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define HAND_SIZE 5

struct gameSettings{
    bool jokers; // Are Jokers involved
    short wildCard; // Any Wildcards?
}game = {true , -1};

void updateSettings(bool newJokers, short newWildCard)
{
    game.jokers = newJokers;
    game.wildCard = newWildCard;
}

void play()
{
    int* pDeck = deckStart;
    shuffleCards();
    int hand[5] = {pDeck[0], pDeck[1], pDeck[2], pDeck[3], pDeck[4]};
    int* phand = &hand[0];

}