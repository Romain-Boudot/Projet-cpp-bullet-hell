//
// Created by camillebourget on 12/03/18.
//

#ifndef PROJET_CPP_BULLET_HELL_MENU_H
#define PROJET_CPP_BULLET_HELL_MENU_H

#endif //PROJET_CPP_BULLET_HELL_MENU_H
#pragma once
#include "SFML/Graphics.hpp"

#define MAX_NUMBER_OF_ITEMS 3

class Menu
{
public:
    Menu(float width, float height);
    ~Menu();

    void draw(sf::RenderWindow &window);
    void MoveUp();
    void MoveDown();
    int GetPressedItem() { return selectedItemIndex; }

private:
    int selectedItemIndex;
    sf::Font font;
    sf::Text menu[MAX_NUMBER_OF_ITEMS];

};