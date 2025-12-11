#pragma once
#include <string>

class IEffect {
public:
    virtual ~IEffect() = default;

    virtual std::string GetName() const = 0;

    virtual void ApplyEffect() const = 0;
};
