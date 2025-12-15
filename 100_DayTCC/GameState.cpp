#include "GameState.h"
#include "Stew.h"
#include "Water.h" // Підключаємо Воду (якщо є такий клас)
#include <iostream>
#include <cmath>
#include <algorithm> // Для std::shuffle
#include <random>    // Для генератора випадкових чисел

GameState::GameState(Game& g, sf::Font& f)
    : game(g), font(f)
{
    // Ініціалізація змінних
    current_phase = GamePhase::COUNTDOWN;
    start_countdown_val = 3;
    timer_accumulator = 0.0f;
    main_game_timer = 100.0f;
    dt_clock.restart();

    // Налаштування тексту по центру (Відлік)
    center_text.setFont(font);
    center_text.setCharacterSize(100);
    center_text.setFillColor(sf::Color::Yellow);
    center_text.setString(std::to_wstring(start_countdown_val));

    sf::FloatRect textRect = center_text.getLocalBounds();
    center_text.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
    center_text.setPosition(game.window.getSize().x / 2.0f, game.window.getSize().y / 2.0f);

    // Таймер
    timer_text.setFont(font);
    timer_text.setCharacterSize(40);
    timer_text.setFillColor(sf::Color::Red);
    timer_text.setPosition(game.window.getSize().x - 150.f, 10.f);

    // Інвентар
    inventory_text.setFont(font);
    inventory_text.setCharacterSize(20);
    inventory_text.setFillColor(sf::Color::White);
    inventory_text.setPosition(50, 50);

    // Ініціалізація дому
    current_view = HouseView::SELECT_ROOM;
    InitHouse();

    // Кнопка Назад
    back_button.setFont(font);
    back_button.setString(L"<< Назад");
    back_button.setCharacterSize(30);
    back_button.setFillColor(sf::Color::Yellow);
    back_button.setPosition(50, game.window.getSize().y - 100.f);
}

void GameState::InitHouse() {
    // --- 1. КУХНЯ ---
    Room kitchen;
    kitchen.name = L"Кухня";

    Furniture fridge;
    fridge.name = L"Холодильник";
    fridge.slots.push_back(SearchSlot(L"Верхня полиця", std::make_unique<Stew>()));
    fridge.slots.push_back(SearchSlot(L"Нижня полиця", nullptr));
    fridge.slots.push_back(SearchSlot(L"Морозилка", std::make_unique<Stew>())); // Додали морозилку
    kitchen.furniture.push_back(std::move(fridge));

    Furniture table;
    table.name = L"Обідній стіл";
    table.slots.push_back(SearchSlot(L"На столі", std::make_unique<Water>())); // Тут вода
    table.slots.push_back(SearchSlot(L"Під столом", nullptr));
    kitchen.furniture.push_back(std::move(table));

    Furniture oven;
    oven.name = L"Плита";
    oven.slots.push_back(SearchSlot(L"Духовка", std::make_unique<Stew>()));
    kitchen.furniture.push_back(std::move(oven));

    // --- 2. СПАЛЬНЯ ---
    Room bedroom;
    bedroom.name = L"Спальня";

    Furniture wardrobe;
    wardrobe.name = L"Шафа для одягу";
    wardrobe.slots.push_back(SearchSlot(L"Кишеня пальто", nullptr));
    wardrobe.slots.push_back(SearchSlot(L"Верхня полиця", std::make_unique<Water>()));
    wardrobe.slots.push_back(SearchSlot(L"Нижня шухляда", nullptr));
    bedroom.furniture.push_back(std::move(wardrobe));

    Furniture bed;
    bed.name = L"Ліжко";
    bed.slots.push_back(SearchSlot(L"Під подушкою", std::make_unique<Stew>()));
    bed.slots.push_back(SearchSlot(L"Під ліжком", nullptr));
    bedroom.furniture.push_back(std::move(bed));

    // --- 3. ВАННА (НОВА) ---
    Room bathroom;
    bathroom.name = L"Ванна кімната";

    Furniture cabinet;
    cabinet.name = L"Дзеркальна шафка";
    cabinet.slots.push_back(SearchSlot(L"За дзеркалом", std::make_unique<Water>()));
    cabinet.slots.push_back(SearchSlot(L"Нижня полиця", nullptr));
    bathroom.furniture.push_back(std::move(cabinet));

    Furniture bath;
    bath.name = L"Ванна";
    bath.slots.push_back(SearchSlot(L"На бортику", nullptr));
    bathroom.furniture.push_back(std::move(bath));

    // --- 4. ВІТАЛЬНЯ (НОВА) ---
    Room livingroom;
    livingroom.name = L"Вітальня";

    Furniture sofa;
    sofa.name = L"Диван";
    sofa.slots.push_back(SearchSlot(L"Між подушками", std::make_unique<Stew>()));
    livingroom.furniture.push_back(std::move(sofa));

    // Додаємо кімнати в дім
    house.push_back(std::move(kitchen));
    house.push_back(std::move(bedroom));
    house.push_back(std::move(bathroom));
    house.push_back(std::move(livingroom));

    // --- РАНДОМІЗАЦІЯ (ПЕРЕМІШУВАННЯ) ---
    std::random_device rd;
    std::mt19937 g(rd());

    // 1. Перемішуємо порядок кімнат
    std::shuffle(house.begin(), house.end(), g);

    // 2. Перемішуємо меблі всередині кожної кімнати та слоти в меблях
    for (auto& room : house) {
        std::shuffle(room.furniture.begin(), room.furniture.end(), g);

        for (auto& furn : room.furniture) {
            std::shuffle(furn.slots.begin(), furn.slots.end(), g);
        }
    }
}

bool GameState::IsMouseOver(const sf::Text& t, sf::RenderWindow& window) const {
    sf::Vector2i m = sf::Mouse::getPosition(window);
    sf::Vector2f world_pos = window.mapPixelToCoords(m);
    return t.getGlobalBounds().contains(world_pos);
}

void GameState::handleEvents(sf::RenderWindow& window) {
    sf::Event e;
    while (window.pollEvent(e)) {
        if (e.type == sf::Event::Closed) window.close();
        if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape) window.close();

        if (e.type == sf::Event::Resized) {
            center_text.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
            timer_text.setPosition(window.getSize().x - 150.f, 10.f);
        }

        if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
            if (current_phase == GamePhase::GAME_RUNNING) {
                // Кнопка Назад
                if (current_view != HouseView::SELECT_ROOM) {
                    if (IsMouseOver(back_button, window)) {
                        if (current_view == HouseView::INSIDE_FURNITURE) current_view = HouseView::INSIDE_ROOM;
                        else if (current_view == HouseView::INSIDE_ROOM) current_view = HouseView::SELECT_ROOM;
                        return;
                    }
                }

                // Логіка вибору (Room -> Furniture -> Slot)
                if (current_view == HouseView::SELECT_ROOM) {
                    for (size_t i = 0; i < house.size(); ++i) {
                        sf::Text room_text;
                        room_text.setFont(font);
                        room_text.setString(house[i].name);
                        room_text.setCharacterSize(40);
                        // Позиція вже не хардкодна по суті, бо house перемішаний
                        room_text.setPosition(100.f, 150.f + static_cast<float>(i) * 60.f);

                        if (IsMouseOver(room_text, window)) {
                            selected_room_index = static_cast<int>(i);
                            current_view = HouseView::INSIDE_ROOM;
                            break;
                        }
                    }
                }
                else if (current_view == HouseView::INSIDE_ROOM) {
                    Room& room = house[selected_room_index];
                    for (size_t i = 0; i < room.furniture.size(); ++i) {
                        sf::Text furn_text;
                        furn_text.setFont(font);
                        furn_text.setString(room.furniture[i].name);
                        furn_text.setCharacterSize(40);
                        furn_text.setPosition(100.f, 150.f + static_cast<float>(i) * 60.f);

                        if (IsMouseOver(furn_text, window)) {
                            selected_furniture_index = static_cast<int>(i);
                            current_view = HouseView::INSIDE_FURNITURE;
                            break;
                        }
                    }
                }
                else if (current_view == HouseView::INSIDE_FURNITURE) {
                    Furniture& furn = house[selected_room_index].furniture[selected_furniture_index];

                    for (size_t i = 0; i < furn.slots.size(); ++i) {
                        if (furn.slots[i].is_searched && furn.slots[i].item_inside == nullptr) continue;

                        sf::Text slot_text;
                        slot_text.setFont(font);
                        slot_text.setCharacterSize(35);
                        slot_text.setPosition(100.f, 150.f + static_cast<float>(i) * 60.f);

                        if (!furn.slots[i].is_searched) {
                            slot_text.setString(furn.slots[i].hidden_name);
                            slot_text.setFillColor(sf::Color::White);
                        }
                        else {
                            std::wstring full_text = L"Забрати: " + furn.slots[i].item_inside->GetName();
                            slot_text.setString(full_text);
                            slot_text.setFillColor(sf::Color::Green);
                        }

                        if (IsMouseOver(slot_text, window)) {
                            if (!furn.slots[i].is_searched) {
                                furn.slots[i].is_searched = true;
                            }
                            else if (furn.slots[i].item_inside) {
                                game.player.PickUpItem(std::move(furn.slots[i].item_inside));
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
}

void GameState::update() {
    float dt = dt_clock.restart().asSeconds();

    if (current_phase == GamePhase::COUNTDOWN) {
        timer_accumulator += dt;
        if (timer_accumulator >= 1.0f) {
            start_countdown_val--;
            timer_accumulator = 0.0f;
            if (start_countdown_val > 0) {
                center_text.setString(std::to_wstring(start_countdown_val));
            }
            else {
                current_phase = GamePhase::GAME_RUNNING;
                center_text.setString(L"");
            }
            sf::FloatRect textRect = center_text.getLocalBounds();
            center_text.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
            center_text.setPosition(game.window.getSize().x / 2.f, game.window.getSize().y / 2.f);
        }
    }
    else if (current_phase == GamePhase::GAME_RUNNING) {
        main_game_timer -= dt;
        int seconds_left = static_cast<int>(std::ceil(main_game_timer));
        timer_text.setString(std::to_wstring(seconds_left));

        if (main_game_timer <= 0.0f) {
            main_game_timer = 0.0f;
            current_phase = GamePhase::NEXT_LEVEL;
            center_text.setString(L"Час вийшов!");
            sf::FloatRect textRect = center_text.getLocalBounds();
            center_text.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
            center_text.setPosition(game.window.getSize().x / 2.f, game.window.getSize().y / 2.f);
        }
    }
}

void GameState::render(sf::RenderWindow& window) {
    if (current_phase == GamePhase::COUNTDOWN) {
        window.draw(center_text);
    }
    else if (current_phase == GamePhase::GAME_RUNNING) {

        std::wstring info = game.player.GetInventoryString();
        inventory_text.setString(info);
        window.draw(inventory_text);
        window.draw(timer_text);

        // --- ЗАГОЛОВОК ПО ЦЕНТРУ ---
        sf::Text title;
        title.setFont(font);
        title.setCharacterSize(50);
        title.setFillColor(sf::Color::Cyan);

        // Встановлюємо текст залежно від вигляду
        if (current_view == HouseView::SELECT_ROOM) {
            title.setString(L"Оберіть кімнату:");
        }
        else if (current_view == HouseView::INSIDE_ROOM) {
            title.setString(house[selected_room_index].name);
        }
        else if (current_view == HouseView::INSIDE_FURNITURE) {
            title.setString(house[selected_room_index].furniture[selected_furniture_index].name);
        }

        // ЦЕНТРУВАННЯ ТЕКСТУ
        sf::FloatRect titleRect = title.getLocalBounds();
        title.setOrigin(titleRect.left + titleRect.width / 2.0f, titleRect.top);
        title.setPosition(window.getSize().x / 2.0f, 20.f); // По центру зверху

        window.draw(title);

        // Малювання списків
        if (current_view == HouseView::SELECT_ROOM) {
            for (size_t i = 0; i < house.size(); ++i) {
                sf::Text item;
                item.setFont(font);
                item.setString(house[i].name);
                item.setCharacterSize(40);
                item.setFillColor(sf::Color::White);
                item.setPosition(100.f, 150.f + static_cast<float>(i) * 60.f);
                if (IsMouseOver(item, window)) item.setFillColor(sf::Color::Yellow);
                window.draw(item);
            }
        }
        else if (current_view == HouseView::INSIDE_ROOM) {
            window.draw(back_button);
            Room& room = house[selected_room_index];
            for (size_t i = 0; i < room.furniture.size(); ++i) {
                sf::Text item;
                item.setFont(font);
                item.setString(room.furniture[i].name);
                item.setCharacterSize(40);
                item.setFillColor(sf::Color::White);
                item.setPosition(100.f, 150.f + static_cast<float>(i) * 60.f);
                if (IsMouseOver(item, window)) item.setFillColor(sf::Color::Yellow);
                window.draw(item);
            }
        }
        else if (current_view == HouseView::INSIDE_FURNITURE) {
            window.draw(back_button);
            Furniture& furn = house[selected_room_index].furniture[selected_furniture_index];
            for (size_t i = 0; i < furn.slots.size(); ++i) {
                if (furn.slots[i].is_searched && furn.slots[i].item_inside == nullptr) continue;

                sf::Text item;
                item.setFont(font);
                item.setCharacterSize(35);
                item.setPosition(100.f, 150.f + static_cast<float>(i) * 60.f);

                if (!furn.slots[i].is_searched) {
                    item.setString(furn.slots[i].hidden_name);
                    item.setFillColor(sf::Color::White);
                }
                else {
                    std::wstring full_text = L"Забрати: " + furn.slots[i].item_inside->GetName();
                    item.setString(full_text);
                    item.setFillColor(sf::Color::Green);
                }
                if (IsMouseOver(item, window)) item.setFillColor(sf::Color::Yellow);
                window.draw(item);
            }
        }
    }
    else if (current_phase == GamePhase::NEXT_LEVEL) {
        window.draw(center_text);
    }
}