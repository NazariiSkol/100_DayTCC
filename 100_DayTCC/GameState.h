#pragma once
#include "IState.h"
#include "Game.h"   
#include <string>
#include "Player.h"
#include <SFML/Graphics.hpp>

class Game;
class Player;   

class GameState : public IState {
public:
    GameState(Game& game, sf::Font& font);

    void handleEvents(sf::RenderWindow& window) override;
    void update() override;
    void render(sf::RenderWindow& window) override;

private:
    Game& game;
    sf::Font& font;

    sf::Text title;
};


