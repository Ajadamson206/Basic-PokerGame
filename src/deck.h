#ifndef POKER_H
#define POKER_H

#define SIZE_OF_DECK 54
#define HAND_SIZE 5

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

static unsigned int    CardDeck[SIZE_OF_DECK] = {
                                    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 
                                    14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 
                                    27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 
                                    40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 
                                    53, 54
                                    };
static unsigned int*   DeckStart = &CardDeck[0];  

typedef struct handCard{
    int suit;
    int value;
}Card;

static short GetCardSuit(int card)
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

static short GetCardValue(int card)
{
    if (card > 52) // Jokers
        return 0;
    int value = card % 13; // Ignores Suit
    if (!value) // Kings return a zero from Mod Operator
        return 13; // Set Kings to 13
    return value;
}

class Deck
{
    public:
        Card                HandCards[HAND_SIZE];
        bool                ReplacePositions[HAND_SIZE];

        void Draw(){
            for(int i = 0; i < HAND_SIZE; i++)
            {
                if(*DeckStart == 53 || *DeckStart == 54)
                    DeckStart++;
                if(*DeckStart == 53 || *DeckStart == 54)
                    DeckStart++;
                HandCards[i].value = GetCardValue(*DeckStart);
                HandCards[i].suit = GetCardSuit(*DeckStart);
                DeckStart++;
            }
        }

        bool HandHasAce() {
            for (int i = 0; i < 5; i++)
            {
                if(HandCards[i].value)
                    return true;
            }
            return false;
        }
        void ResetDeck(){
            for(int i = 1; i <= SIZE_OF_DECK; i++)
                CardDeck[i-1] = i;
        }

        void ReplaceHand(){

            for(int i = 0; i < HAND_SIZE; i++)
            {
                if(ReplacePositions[i]) // If a position is true, replace that card
                {
                    HandCards[i].value = GetCardValue(*DeckStart);
                    HandCards[i].suit = GetCardSuit(*DeckStart);
                    DeckStart++;
                }
            }
        }
        void ResetReplace(){
            for(int i = 0; i < HAND_SIZE; i++)
                ReplacePositions[i] = false;
        }  
};
#endif