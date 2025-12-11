#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Game {
public:
    Game();
    void run();

private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text text;
    std::wstring message;

    void processEvents();
    void update();
    void render();
};