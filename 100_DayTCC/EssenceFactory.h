#pragma once
#include <memory>
#include "Essence.h"	
class EssenceFactory
{
	virtual ~EssenceFactory() = default;
	virtual std::unique_ptr<Essence> CreateItem() const = 0;
};

