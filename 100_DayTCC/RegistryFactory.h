#pragma once
#include <unordered_map>
#include <functional>
#include <memory>
#include <string>

template<typename Base>
class RegistryFactory {
public:
    template<typename T>
    void Register(const std::string& id) {
        creators[id] = []() { return std::make_unique<T>(); };
    } 

    std::unique_ptr<Base> Create(const std::string& id) const {
        auto it = creators.find(id);
        if (it != creators.end()) {
            return it->second();
        }
        return nullptr;
    }

private:
    std::unordered_map<std::string, std::function<std::unique_ptr<Base>()>> creators;
};
