#pragma once
#include "Essence.h"
#include <string>
#include <vector>
#include <memory>
#include "Item.h"

class Player : public Essence
{
public:
    const int MAX_WEIGHT = 20000;
    int current_weight = 0;
    std::vector<std::unique_ptr<Item>> inventory;

    int hunger_point;
    int thirst_point;
    int stamina_point;

    Player() : Essence(10, 2, 5), hunger_point(10), thirst_point(10), stamina_point(100) {}

    virtual void Attack(Essence& target) override;
    bool PickUpItem(std::unique_ptr<Item> new_item);

    // wstring
    std::wstring GetInventoryString() const;
};


