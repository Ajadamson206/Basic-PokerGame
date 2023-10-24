#ifndef DECK_H
#define DECK_H

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

static void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void sort(int hand[], int handSize) 
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

        void Draw(bool Jokers){
            for(int i = 0; i < HAND_SIZE; i++)
            {
                if (Jokers)
                {
                    HandCards[i].value = GetCardValue(*DeckStart);
                    HandCards[i].suit = GetCardSuit(*DeckStart);
                    DeckStart++;
                }
                else
                {
                    if(*DeckStart == 53 || *DeckStart == 54) // Check for a Joker
                        DeckStart++; // Skip to Next Card
                    if(*DeckStart == 53 || *DeckStart == 54) // Check for a Joker (Only 2 in a deck, so we check Twice)
                        DeckStart++;
                    HandCards[i].value = GetCardValue(*DeckStart);
                    HandCards[i].suit = GetCardSuit(*DeckStart);
                    DeckStart++;
                }
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
        int checkWinnings(){
            bool flush, straight, royal;
            int flushValue = HandCards[0].suit * HAND_SIZE;
            int handSuits = 0;
            int handValues[HAND_SIZE];

            for (int i = 0; i < HAND_SIZE; i++)
            {
                handSuits += HandCards[i].suit;
                handValues[i] = HandCards[i].value;
            }
            // Check for a flush
            if (flushValue == handSuits)
                flush = true;
            sort(handValues, HAND_SIZE);
            // Check for royal straight flush
            if (handValues[HAND_SIZE-1] == 13)
                royal = true;
            // Check for pairs and straight
            int binaryPairs = 0;
            int numStraight = 0;
            for (int i = 0; i < HAND_SIZE - 1; i++)
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
            if(numStraight == HAND_SIZE-1)
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

            if(handValues[HAND_SIZE-1] >= 11)
                return WIN_ROYAL_HIGH;

            return 0;
                } 
};
#endif