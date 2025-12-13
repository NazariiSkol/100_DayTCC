#include "GameState.h"
 
GameState::GameState(Game& g, sf::Font& f)
    : game(g), font(f)
{
    title.setFont(font);
    title.setCharacterSize(60);
    title.setFillColor(sf::Color::White);
    title.setString(L"Гра почалася!");
    // Центрирование по горизонтали
    float centerX = game.window.getSize().x / 2.f;
    title.setPosition(centerX - title.getGlobalBounds().width / 2.f, 200.f);
}

void GameState::handleEvents(sf::RenderWindow& window) {
    sf::Event e;
    while (window.pollEvent(e)) {

        if (e.type == sf::Event::Closed)
            window.close();

        // ESC → выход назад (или можешь поменять)
        if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape) {
            window.close();
        }

        if (e.type == sf::Event::Resized) {
            // при изменении размера — перелэйаутим надпись
            float centerX = window.getSize().x / 2.f;
            title.setPosition(centerX - title.getGlobalBounds().width / 2.f, 200.f);
        }
    }
}

void GameState::update() {
    // пока логики нет — позже добавим таймеры, врагов и т.д.
}

void GameState::render(sf::RenderWindow& window) {
    // 1. Створюємо або оновлюємо текст (зазвичай це поле класу, а не локальна змінна)
    sf::Text inventoryText;
    inventoryText.setFont(font); // font завантажений у Game
    inventoryText.setCharacterSize(20);
    inventoryText.setFillColor(sf::Color::White);
    inventoryText.setPosition(50, 50); // Позиція на екрані

    // 2. Отримуємо актуальний рядок від гравця
    std::string info = game.player.GetInventoryString();

    // 3. Встановлюємо рядок
    inventoryText.setString(info);

    // 4. Малюємо
    window.draw(inventoryText);
}