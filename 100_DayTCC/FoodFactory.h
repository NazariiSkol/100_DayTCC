#pragma once
#include <memory>
#include "IFood.h"
class FoodFactory
{
public:
	virtual std::unique_ptr<IFood> CreateFood() const = 0;
};


