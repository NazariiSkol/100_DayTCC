#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>   
#include "Game.h"
#include "Stew.h"   
#include "Food.h"   
#include "Item.h"       
#include "ItemFactory.h" 
#include "RegistryFactory.h"    

using namespace std;

int main() {
    setlocale(LC_ALL, "ukr");

    Game game;
    game.run();
    
    RegistryFactory<Food> foodFactory;
    foodFactory.Register<Stew>("stew");

    auto stew = foodFactory.Create("stew");

    return 0;
}



