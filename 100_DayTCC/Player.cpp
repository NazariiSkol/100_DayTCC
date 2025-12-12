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
