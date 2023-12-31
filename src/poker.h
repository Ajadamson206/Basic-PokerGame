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
#ifndef POKER_H
#define POKER_H
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#define SIZE_OF_DECK 54

#define WIN_5_KIND 350
#define WIN_ROYAL_FLUSH 250
#define WIN_STRAIGHT_FLUSH 50
#define WIN_4_KIND 30
#define WIN_FULL_HOUSE 10
#define WIN_FLUSH 8
#define WIN_STRAIGHT 6
#define WIN_3_KIND 5
#define WIN_2_KIND 2
#define WIN_ROYAL_HIGH 1


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
typedef struct handCard{
    int suit;
    int value;
}Card;

int deck[] = {
            1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 
            14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 
            27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 
            40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 
            53, 54
            };
const int* deckStart = &deck[0];
// Shuffle a deck - Uses the Fisher-Yates Shuffle
extern void shuffleCards(void){
    struct timespec tv;
    timespec_get(&tv, TIME_UTC);
    srand48(tv.tv_nsec);


    size_t i;
    for (i = SIZE_OF_DECK - 1; i > 0; i--) {
        size_t j = (unsigned int) (drand48()*(i+1));
        int t = deck[j];
        deck[j] = deck[i];
        deck[i] = t;
    }
}
// 1 = Diamonds 2 = Spades 3 = Hearts 4 = Clubs 5 = Joker
extern short getCardSuit(int card)
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
extern short getCardValue(int card)
{
    if (card > 52) // Jokers
        return 0;
    int value = card % 13; // Ignores Suit
    if (!value) // Kings return a zero from Mod Operator
        return 13; // Set Kings to 13
    return value;
}

extern bool handHasAce(Card* card)
{
    for (int i = 0; i < 5; i++)
    {
        if((card[i].value) == 1)
        {
            return true;
        }
    }
    return false;
}

extern void resetDeck(void)
{
    for(int i = 1; i <= SIZE_OF_DECK; i++)
        deck[i-1] = i;
}

extern void replaceCard(int* hand, int* pdeck, int handPos)
{
    hand[handPos] = *deck;
}

extern void updateCard(int Deck, Card* card)
{
    card->suit = getCardSuit(Deck);
    card->value = getCardValue(Deck);
}

extern void replaceHand(Card* hand, int** pDeck, bool* posReplace, int deckSize)
{
    for(int i = 0; i < deckSize; i++)
    {
        if(posReplace[i]) // If a position is true, replace that card
        {
            hand[i].value = getCardValue(**pDeck);
            hand[i].suit = getCardSuit(**pDeck);
            (*pDeck)++;
        }
    }
}

/*
Winnings
5 of a kind - 350
Royal Flush - 250
Straight Flush - 50
4 of a Kind - 25
Full House - 9
Flush - 6
Straight - 4
3 of a kind - 3
2 pair - 2
Jacks or Better - 1
*/
// Move b into a
extern void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

extern void sort(int hand[], int handSize) 
{ 
    int i, j, min; 
  
    // One by one move boundary of 
    // unsorted subarray 
    for (i = 0; i < handSize - 1; i++) { 
        // Find the minimum element in 
        // unsorted array 
        min = i; 
        for (j = i + 1; j < handSize; j++) 
            if (hand[j] < hand[min]) 
                min = j; 
  
        // Swap the found minimum element 
        // with the first element 
        swap(&hand[min], &hand[i]); 
    } 
} 
/*
Winnings
5 of a kind - 350
Royal Flush - 250
Straight Flush - 50
4 of a Kind - 25
Full House - 9
Flush - 6
Straight - 4
3 of a kind - 3
2 pair - 2
Jacks or Better - 1
*/
extern int checkWinnings(Card* hand, int handSize)
{
    bool flush, straight, royal;
    int flushValue = hand[0].suit * handSize;
    int handSuits = 0;
    int handValues[handSize];

    for (int i = 0; i < handSize; i++)
    {
        handSuits += hand[i].suit;
        handValues[i] = hand[i].value;
    }
    // Check for a flush
    if (flushValue == handSuits)
        flush = true;
    sort(handValues, handSize);
    // Check for royal straight flush
    if (handValues[handSize-1] == 13)
        royal = true;
    // Check for pairs and straight
    int binaryPairs = 0;
    int numStraight = 0;
    for (int i = 0; i < handSize - 1; i++)
    {
        // Store Pairs into an integer ie { 4, 4, 4, 8, 8 } becomes 1101 = 13
        if (handValues[i] == handValues[i+1])
            binaryPairs++;
        else if ((handValues[i]+1) == handValues[i+1])
            numStraight++;
        binaryPairs = binaryPairs << 1;
    }

    switch (binaryPairs)
    {
        case 0: // No Pair
            break;
        case 1: // 1 Pair
        case 2:
        case 4:
        case 8:
            return WIN_2_KIND;
            break;
        case 5:
        case 9:
        case 10:
            return WIN_2_KIND + WIN_2_KIND;
            break;
        case 3:
        case 6:
        case 12:
            return WIN_3_KIND;
            break;
        case 7:
        case 14:
            return WIN_4_KIND;
            break;
        case 11:
        case 13:
            return WIN_FULL_HOUSE;
            break;
        case 15:
            return WIN_5_KIND;
            break;
    } 
    if(numStraight == handSize-1)
    {
        if (flush)
        {
            if (royal)
                return WIN_ROYAL_FLUSH;
            else
                return WIN_STRAIGHT_FLUSH;
        }
        else
            return WIN_STRAIGHT;
    }
    else if (flush)
        return WIN_FLUSH;

    if(handValues[handSize-1] >= 11)
        return WIN_ROYAL_HIGH;
    
    return 0;
}
#endif