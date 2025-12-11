#include "StewFactory.h"

/*std::unique_ptr<Item> StewFactory::CreateItem() const
{
	return std::make_unique<Item>();
}*/

std::unique_ptr<IFood> StewFactory::CreateFood() const
{
    auto stew = std::make_unique<Stew>();
    stew->SetSaturationUnits();
    return stew;
}
