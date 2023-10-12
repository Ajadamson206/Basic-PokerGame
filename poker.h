/*
In this file

Create an integer array with 54 Elements (2 jokers are included)
    - If wildcards are disabled then it will just be skipped over

Clubs Positions 0-12
Spades 13 - 25

Diamonds 26 - 38
Hearts 39-51

Joker1 52
Joker2 53


*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define SIZE_OF_DECK 54


/*
Value range 1-13

    1 = Ace
    2-10 = Self explanatory
    11 = Jack
    12 = Queen
    13 = King

Suit range 1-4
    (Black is Even, Red is Odd)
    1 = Diamonds
    2 = Spaces
    3 = Hearts
    4 = Clubs
*/

int deck[] = {
            1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 
            14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 
            27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 
            40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 
            53, 54
            };
const int* deckStart = &deck[0];

// Shuffle a deck - Uses the Fisher-Yates Shuffle
void shuffleCards(){

    int n = SIZE_OF_DECK;

    struct timespec tv;
    timespec_get(&tv, TIME_UTC);
    srand48(tv.tv_nsec);


    if (n > 1) {
        size_t i;
        for (i = n - 1; i > 0; i--) {
            size_t j = (unsigned int) (drand48()*(i+1));
            int t = deck[j];
            deck[j] = deck[i];
            deck[i] = t;
        }
    }
}
// 1 = Diamonds 2 = Spades 3 = Hearts 4 = Clubs 5 = Joker
short getCardSuit(int card)
{
    if (card > 52) // Joker
        return 5;
    else if(card > 39) // Clubs
        return 4;
    else if (card > 26) // Hearts
        return 3;
    else if (card > 13) // Spades
        return 2;
    else // Diamonds
        return 1;

}
// 0 = Joker, 1 = Ace, 11 = Jack, 12 = Queen, 13 = King
short getCardValue(int card)
{
    if (card > 52) // Jokers
        return 0;
    int value = card % 13; // Ignores Suit
    if (!value) // Kings return a zero from Mod Operator
        return 13; // Set Kings to 13
    return value;
}

void resetDeck()
{
    for(int i = 1; i <= SIZE_OF_DECK; i++)
        deck[i-1] = i;
}