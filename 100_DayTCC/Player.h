#pragma once
#include "Essence.h"
class Player: public Essence
{
public:	
	std::unique_ptr<Weapon> player_weapon;
	int hunger_point;
    int thirst_point;	
	int stamina_point;
	
	Player() : Essence(10, 2, 5), hunger_point(10), thirst_point(10), stamina_point(100) {}

	virtual void Attack(Essence& target) override;
	void SetWeapon(std::unique_ptr<Weapon> new_weapon);
	void SetItem(std::unique_ptr<Item> new_item);
			
};


