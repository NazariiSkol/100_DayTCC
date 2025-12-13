#include "Stew.h"

Stew::Stew()
{
	weight = 300;
	saturation = 4;
}

int Stew::GetSaturation() const
{
	return saturation;
}

std::string Stew::GetName() const
{
	return "Тушонка";
}
