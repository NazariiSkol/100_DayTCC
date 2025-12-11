#include "Game.h"
#include <iostream>

Game::Game(): window(sf::VideoMode(800, 600), "Text-based SFML Game")
    
{
    // Загружаем шрифт
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Не удалось загрузить шрифт!\n";
    }

    // Настройка текстового объекта
    text.setFont(font);          // ДОЛЖНО БЫТЬ
    text.setCharacterSize(32);
    text.setFillColor(sf::Color::White);
    text.setPosition(20.f, 20.f);

    text.setString(L"Добро пожаловать в текстовую игру!");
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::update() {
   
}

void Game::render() {
    window.clear(sf::Color::Black);
    window.draw(text);
    window.display();
}