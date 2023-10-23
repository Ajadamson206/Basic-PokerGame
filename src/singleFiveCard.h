#ifndef FIVE_CARD_P
#define FIVE_CARD_P

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

// Shows which cards to replace {true, false, true, false, true} -> Will replace positions 0, 2, 4
bool posReplace[HAND_SIZE];

void resetReplace()
{
    for(int i = 0; i < HAND_SIZE; i++)
        posReplace[i] = false;
}


void updateSettings(bool newJokers, short newWildCard)
{
    game.jokers = newJokers;
    game.wildCard = newWildCard;
}
void play(void)
{
    int winnings = 5;
    while(winnings != 0)
    {
        Card card[HAND_SIZE];
        resetReplace();
        int* pDeck = deckStart;
        shuffleCards();
        for (int i = 0; i < HAND_SIZE; i++) // Add Cards to the Hand
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
            updateCard(*pDeck, &card[i]); // No need to check for a third Joker, there are only two
            //renderCard(card[i], i);
            pDeck++;
        }
        // Get Userinput to replace cards in their hand
        // if (has an Ace) -> Possible replace cards = 4; else possible replace cards = 3;
        int numCardsPosReplace;
        if (handHasAce(&card[0]))
            numCardsPosReplace = 4;
        else
            numCardsPosReplace = 3;

        replaceHand(&card[0], &pDeck, posReplace, SIZE_OF_DECK);
        
        // update winnings
        winnings += checkWinnings(&card[0], HAND_SIZE);

        // end game
        resetDeck();
        winnings--;
    }

}
#endif