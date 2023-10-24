#include "game.h"
#include "text_render.h"
#include "resource_manager.h"
#include "deck.h"
#include <string>

#define CARD_SHADER "card"
#define COLOR_RED glm::vec3(0.863f, 0.102f, 0.102f)


Game::Game() 
    : Keys(), KeysProcessed(), Winnings(HAND_SIZE), NumReplaced(0)
{

}


void Game::Init(bool jokers, unsigned short wildCard, unsigned int width, unsigned int height)
{
    // Things to do in this file:
    this->Width = width;
    this->Height = height;
    MainDeck.ResetReplace(); // Set the replace positions to all false;

    // Set Settings
    this->Jokers = jokers;
    this->WildCard = wildCard;
    MainDeck.Draw(this->Jokers); // Draw the deck of cards
    this->MaxReplace = MainDeck.HandHasAce()? 4 : 3; // Hands with an ace can remove 4 cards rather than 3

    //--- Load Shaders ----//
    
    // Card Shaders
    ResourceManager::LoadShader(VERTEX_FILE, WHITE_FILE, nullptr, "card");

    // Text Shaders
    this->Text = new TextRenderer(this->Width, this->Height);
    this->Text->Load("Antonio-Bold.ttf", 24); // Font for Text


}

void Game::Render()
{
    // Render 5 Blank Cards

    //------- Render Text----------

    // Winnings
    std::string winning_text = "Winnings: ";
    winning_text.append(std::to_string(this->Winnings));
    this->Text->RenderText(winning_text, 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));

    // Discard
    for(int i = 0; i < HAND_SIZE; i++)
    {
        // Check Replace Positions for each place it is true place Discard under the card
        if(MainDeck.ReplacePositions[i])
        {
            this->Text->RenderText("Discard", 25.0f, 1000.0f, 1.0f, glm::vec3(0.863f, 0.102f, 0.102f));
        }
    }

    // Render the suits and values
    for(int i = 0; i < HAND_SIZE; i++)
    {
        std::string card_text;
        glm::vec3 color;
        switch(MainDeck.HandCards[i].value)
        {
            case 1:
                card_text.append("A");
                break;
            case 11:
                card_text.append("J");
                break;
            case 12:
                card_text.append("Q");
                break;
            case 13:
                card_text.append("K");
                break;
            default:
                card_text.append(std::to_string(MainDeck.HandCards[i].value));
                break;
        }
        switch (MainDeck.HandCards[i].suit)
        {
            case 1:
                card_text.append("D");
                color = COLOR_RED;
                break;
            case 2:
                card_text.append("S");

                break;
            case 3:
                card_text.append("H");
                color = COLOR_RED;
                break;
            case 4:
                card_text.append("C");
                break;
        }
        this->Text->RenderText(card_text, 25.0f, 25.0f, 2.0, color);

    }

    // Render Which Cards are being Held
}

void Game::Update(float dt)
{

}

void Game::Reset()
{
    // Reset Replace Positions
    for(int i = 0; i < HAND_SIZE; i++)
        MainDeck.ReplacePositions[i] = false;
}

void Game::ProcessInput(float dt)
{
    if (this->Keys[GLFW_KEY_1])
    {
        MainDeck.ReplacePositions[0]? NumReplaced-- : NumReplaced++; // If its being deactivated decrease number of replaced, vice versa
        MainDeck.ReplacePositions[0] = !(MainDeck.ReplacePositions[0]);
    }
    if (this->Keys[GLFW_KEY_2])
    {
        MainDeck.ReplacePositions[1]? NumReplaced-- : NumReplaced++; // If its being deactivated decrease number of replaced, vice versa
        MainDeck.ReplacePositions[1] = !(MainDeck.ReplacePositions[1]);
    }
    if (this->Keys[GLFW_KEY_3])
    {
        MainDeck.ReplacePositions[2]? NumReplaced-- : NumReplaced++; // If its being deactivated decrease number of replaced, vice versa
        MainDeck.ReplacePositions[2] = !(MainDeck.ReplacePositions[2]);
    }
    if (this->Keys[GLFW_KEY_4])
    {
        MainDeck.ReplacePositions[3]? NumReplaced-- : NumReplaced++; // If its being deactivated decrease number of replaced, vice versa
        MainDeck.ReplacePositions[3] = !(MainDeck.ReplacePositions[3]);
    }
    if (this->Keys[GLFW_KEY_5])
    {
        MainDeck.ReplacePositions[4]? NumReplaced-- : NumReplaced++; // If its being deactivated decrease number of replaced, vice versa
        MainDeck.ReplacePositions[4] = !(MainDeck.ReplacePositions[4]);
    }
    if (this->Keys[GLFW_KEY_SPACE])
    {
        if (!(this->NumReplaced > this->MaxReplace))
            MainDeck.ReplaceHand();
    }
}