#pragma once
#include "IState.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <memory>
#include <cmath>
#include "HouseSystem.h" // Тепер підключаємо новий файл

class Game;

enum class GamePhase {
    COUNTDOWN,
    GAME_RUNNING,
    NEXT_LEVEL
};

enum class HouseView {
    SELECT_ROOM,
    INSIDE_ROOM,
    INSIDE_FURNITURE
};

class GameState : public IState {
public:
    GameState(Game& game, sf::Font& font);

    // Ці методи залишаються camelCase, бо вони з IState
    void handleEvents(sf::RenderWindow& window) override;
    void update() override;
    void render(sf::RenderWindow& window) override;

private:
    Game& game;
    sf::Font& font;

    // --- Змінні snake_case ---
    GamePhase current_phase;
    sf::Clock dt_clock;
    float timer_accumulator;
    int start_countdown_val;
    float main_game_timer;

    sf::Text center_text;
    sf::Text timer_text;
    sf::Text inventory_text;
    sf::Text back_button;

    // Логіка будинку
    HouseView current_view;
    std::vector<Room> house;
    int selected_room_index = -1;
    int selected_furniture_index = -1;

    // --- Методи PascalCase ---
    void InitHouse();
    bool IsMouseOver(const sf::Text& t, sf::RenderWindow& window) const;
};

