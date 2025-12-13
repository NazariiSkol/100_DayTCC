#pragma once
#include <SFML/Graphics.hpp>
#include "IState.h"
#include "Player.h"
#include "Stew.h"
#include <iostream>
#include "MenuState.h"  

class Game {
public:
    Game();
    ~Game();

	Player player;  

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