#pragma once
#include "IItem.h" 
#include <string>

class Item : public IItem {
protected:
    int weight;
public:
    int GetWeight() const override;
    virtual std::string GetName() const = 0;
};
