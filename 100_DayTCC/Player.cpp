#include "Player.h"

void Player::Attack(Essence& target)
{
}

void Player::SetWeapon(std::unique_ptr<Weapon> new_weapon)
{
	player_weapon = std::move(new_weapon);
}

void Player::SetItem(std::unique_ptr<Item> new_item)
{

}

bool Player::PickUpItem(std::unique_ptr<Item> new_item)
{
    {
        if (!new_item) return false;

        int item_weight = new_item->GetWeight();

        // Перевіряємо, чи не перевищимо ліміт
        if (current_weight + item_weight > MAX_WEIGHT) {
            return false; // Предмет не взято (заважкий)
        }

        // Додаємо вагу
        current_weight += item_weight;

        // Переміщуємо предмет у вектор інвентаря
        inventory.push_back(std::move(new_item));

        return true; // Успішно взяли
    }
}

std::string Player::GetInventoryString() const
{
    {
        std::stringstream ss;

        // Заголовок з вагою
        ss << "Inventory: " << current_weight << "g / " << MAX_WEIGHT << "g\n";
        ss << "-----------------------------\n";

        if (inventory.empty()) {
            ss << "Empty...";
            return ss.str();
        }

        // Групуємо предмети: Назва -> {Кількість, Загальна вага}
        std::map<std::string, std::pair<int, int>> groupedItems;

        for (const auto& item : inventory) {
            // Переконайся, що в Item.h є метод GetName()
            std::string name = item->GetName();
            int w = item->GetWeight();

            groupedItems[name].first++;    // +1 кількість
            groupedItems[name].second += w; // +вага
        }

        // Формуємо рядок: "Stew x5 - 1500g"
        for (const auto& kv : groupedItems) {
            ss << kv.first << " x" << kv.second.first
                << " - " << kv.second.second << "g\n";
        }

        return ss.str();
    }
}
