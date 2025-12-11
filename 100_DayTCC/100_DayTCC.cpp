#include <iostream>
#include <string>   
#include "Game.h"
#include "Stew.h"   
#include "Food.h"   
#include "Item.h"       
#include "ItemFactory.h" 
#include "RegistryFactory.h"    
#include <SFML/Graphics.hpp>

using namespace std;

int main() {
    setlocale(LC_ALL, "ukr");

    Game game;
    game.run();
    return 0;


    RegistryFactory<Food> foodFactory;
    foodFactory.Register<Stew>("stew");

    auto stew = foodFactory.Create("stew");

    cout << stew->GetSaturation();

    return 0;
}



