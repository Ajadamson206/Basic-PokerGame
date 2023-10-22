#ifndef POKER_H
#define POKER_H

#include "poker.c"
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
typedef struct handCard Card;

int deck[] = {
            1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 
            14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 
            27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 
            40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 
            53, 54
            };
const int* deckStart = &deck[0];

// Shuffle a deck - Uses the Fisher-Yates Shuffle
extern void shuffleCards(void);
// 1 = Diamonds 2 = Spades 3 = Hearts 4 = Clubs 5 = Joker
extern short getCardSuit(int card);
// 0 = Joker, 1 = Ace, 11 = Jack, 12 = Queen, 13 = King
extern short getCardValue(int card);

extern bool handHasAce(Card* card);

extern void resetDeck(void);
extern void replaceCard(int* hand, int* pdeck, int handPos);

extern void updateCard(int Deck, Card* card);

extern void replaceHand(Card* hand, int** pDeck, bool* posReplace, int deckSize);
// Move b into a
extern void swap(int* a, int* b);

extern void sort(int hand[], int handSize);
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
extern int checkWinnings(Card* hand, int handSize);

#endif