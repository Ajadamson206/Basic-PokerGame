#include "poker.h"
#include "renderer.c"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define HAND_SIZE 5

struct gameSettings{
    bool jokers; // Are Jokers involved
    short wildCard; // Any Wildcards; 0 for Jokers
}game = {false , 0};

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
    int winnings = 5;
    while(winnings != 0)
    {
        int* pDeck = deckStart;
        shuffleCards();
        int hand[5];
        for (int i = 0; i < 5; i++) // Add Cards to the Hand
        {
            if (!game.jokers) // Jokers are not in Game 
            {   
                if((*pDeck == 53) || (*pDeck == 54)) // If card is Joker
                {
                    pDeck++;
                    if((*pDeck == 53) || (*pDeck == 54)) // If next card is also a Joker
                        pDeck++;
                }
            }
            hand[i] = *pDeck; // No need to check for a third Joker, there are only two
            renderCard(getCardSuit(hand[i]), getCardValue(hand[i]), i);
            pDeck++;
        }
        int* phand = &hand[0];
    
        // Get Userinput to replace cards in their hand
        // if (has an Ace) -> Possible replace cards = 4; else possible replace cards = 3;
        int numCardsPosReplace;
        if (handHasAce(hand[0]))
            numCardsPosReplace = 4;
        else
            numCardsPosReplace = 3;
    


    }

}