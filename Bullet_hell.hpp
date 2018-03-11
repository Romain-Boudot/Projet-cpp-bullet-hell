#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include "Enemy.hpp"

class Bullet_hell {

    public:
        
        int windowHeight;
        int windowWidth;
        int framerate;

        std::vector<Enemy> enemy;

        sf::CircleShape player_sprite;

        sf::RenderWindow *window;

        Bullet_hell();

};

Bullet_hell::Bullet_hell() {

    this->windowHeight = 800;
    this->windowWidth = 500;
    this->framerate = 60;

    sf::CircleShape player_sprite(5.f,100);
    player_sprite.setFillColor(sf::Color::Green);

    this->player_sprite = player_sprite;

    Enemy enemy1(250.f, 60.f);
    Enemy enemy2(250.f, 90.f);
    Enemy enemy3(220.f, 60.f);
    Enemy enemy4(280.f, 60.f);

    this->enemy.push_back(enemy1);
    this->enemy.push_back(enemy2);
    this->enemy.push_back(enemy3);
    this->enemy.push_back(enemy4);

}