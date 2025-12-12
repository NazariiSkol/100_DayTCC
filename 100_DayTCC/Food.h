#pragma once
#include "IItem.h"

class Food : public Item {
protected:
    int weight = 0;
    int saturation = 0;

public:
    int GetWeight() const override;
    int GetSaturation() const;
};

