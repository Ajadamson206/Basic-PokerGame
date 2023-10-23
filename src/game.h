#ifndef GAME_H
#define GAME_H

#include <vector>
#include <tuple>

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "deck.h"


// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability.
class Game
{
public:
    // game state
    bool                    Keys[1024];
    bool                    KeysProcessed[1024];
    unsigned int            Width, Height;
    unsigned int            Winnings;
    bool                    Jokers; // Are Jokers involved
    unsigned short          WildCard; // Any Wildcards; 0 for Joker
    unsigned short          NumReplaced;
    unsigned short          MaxReplace;
    Deck                    MainDeck;
    // constructor/destructor
    Game();
    ~Game();
    // initialize game state (load all shaders/textures/levels)
    void Init(bool jokers, unsigned short wildCard, unsigned int width, unsigned int height);
    // game loop
    void ProcessInput(float dt);
    void Update(float dt);
    void Render();
    // reset
    void Reset();
};

#endif