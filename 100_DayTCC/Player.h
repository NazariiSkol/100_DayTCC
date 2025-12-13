#pragma once
#include "Essence.h"
#include <sstream>
#include <string>
#include <vector>
#include <map>

class Player: public Essence
{
public:
	const int MAX_WEIGHT = 20000; 
	int current_weight = 0;
	std::vector<std::unique_ptr<Item>> inventory;
	std::unique_ptr<Weapon> player_weapon;  

	int hunger_point;
    int thirst_point;	
	int stamina_point;
	
	Player() : Essence(10, 2, 5), hunger_point(10), thirst_point(10), stamina_point(100) {}

	virtual void Attack(Essence& target) override;
	void SetWeapon(std::unique_ptr<Weapon> new_weapon);
	void SetItem(std::unique_ptr<Item> new_item);
	bool PickUpItem(std::unique_ptr<Item> new_item);	
	std::string GetInventoryString() const;
			
};


