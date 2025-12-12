#pragma once
#include <memory>	
#include <iostream>
#include "Weapon.h"

class Essence
{
protected:	
	int health_point;
	int basic_damage;
	int speed_point;

public:
	Essence(int health_point, int basic_damage, int speed_point) // hp bd sp
	{
		this->health_point = health_point;
		this->basic_damage = basic_damage;	
		this->speed_point = speed_point;
	}

	virtual void Attack(Essence& target) = 0;
	virtual ~Essence() = default;
};

