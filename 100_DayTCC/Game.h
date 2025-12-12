#pragma once
#include <SFML/Graphics.hpp>
#include "IState.h"
#include <iostream>
#include "MenuState.h"  

class Game {
public:
    Game();
    ~Game();

    void run();
    void changeState(IState* newState);

    sf::RenderWindow window;  

private:
    sf::Font font;
    IState* currentState = nullptr;

    void processEvents();
    void update();
    void render();
};