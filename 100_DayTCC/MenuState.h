#pragma once
#include "IState.h"
#include "Game.h"
#include "GameState.h"
#include "LoreState.h"
#include <SFML/Graphics.hpp>    

class Game;

class MenuState : public IState {
public:
    // ВАЖНО: сигнатура ДОЛЖНА совпадать с вызовом new MenuState(*this, font)
    MenuState(Game& game, sf::Font& font);

    void handleEvents(sf::RenderWindow& window) override;
    void update() override;
    void render(sf::RenderWindow& window) override;

private:
    Game& game;
    sf::Font& font;

    sf::Text title;
    sf::Text btnStart;
    sf::Text btnLore;
    sf::Text btnExit;

    bool isMouseOver(const sf::Text& t, sf::RenderWindow& window) const;
    void layout();
};

