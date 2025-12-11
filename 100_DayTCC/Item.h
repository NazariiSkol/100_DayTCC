#pragma once
#include "IItem.h"  

class Item : public IItem {
protected:
    int weight;
public:
    int GetWeight() const override;
};
