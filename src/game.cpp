#include "game.h"
#include "text_render.h"
#include "resource_manager.h"
#include "deck.h"


Game::Game() 
    : Keys(), KeysProcessed(), Winnings(HAND_SIZE)
{

}


void Game::Init(bool jokers, unsigned short wildCard, unsigned int width, unsigned int height)
{
    // Things to do in this file:
    this->Width = width;
    this->Height = height;
    MainDeck.ResetReplace();
    // Set Settings
    this->Jokers = jokers;
    this->WildCard = wildCard;
    MainDeck.Draw();
    // Load Shaders
    
    // Card Shaders
    ResourceManager::LoadShader(VERTEX_FILE, WHITE_FILE, nullptr, "card");

    // Text Shaders
    TextRenderer *Text;
    Text = new TextRenderer(this->Width, this->Height);
    Text->Load("/home/albert/Documents/Projects/C/Basic-PokerGame/Antonio-Bold.ttf", 24);
    // Render Cards


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
        MainDeck.ReplacePositions[0] = !(MainDeck.ReplacePositions[0]);
    }
    if (this->Keys[GLFW_KEY_2])
    {
        MainDeck.ReplacePositions[1] = !(MainDeck.ReplacePositions[1]);
    }
    if (this->Keys[GLFW_KEY_3])
    {
        MainDeck.ReplacePositions[2] = !(MainDeck.ReplacePositions[2]);
    }
    if (this->Keys[GLFW_KEY_4])
    {
        MainDeck.ReplacePositions[3] = !(MainDeck.ReplacePositions[3]);
    }
    if (this->Keys[GLFW_KEY_5])
    {
        MainDeck.ReplacePositions[4] = !(MainDeck.ReplacePositions[4]);
    }
    if (this->Keys[GLFW_KEY_SPACE])
        MainDeck.ReplaceHand();
}