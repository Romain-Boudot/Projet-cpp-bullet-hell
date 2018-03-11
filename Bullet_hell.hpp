/* #include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include "player.hpp"
#include "Enemy.hpp" */

class Bullet_hell {

    public:
        
        int windowHeight; // hauteur de la fenetre de jeu
        int windowWidth; // largeur de la fenetre de jeu
        int framerate; // taux de rafraichissement du jeu
        Player player; // class Player
        std::vector<Enemy> enemy; // tableau de class Enemy
        sf::RenderWindow *window; // fenetre de jeu
        sf::Vector2i mouse_posi;

        Bullet_hell();

        bool isEnded();
        void end();

    private:

        bool endb;

};

Bullet_hell::Bullet_hell() {

    this->windowHeight = 800;
    this->windowWidth = 500;
    this->framerate = 60;
    this->endb = false;

    Player player;

    this->player = player;

    Enemy enemy1(250.f, 60.f);
    Enemy enemy2(250.f, 90.f);
    Enemy enemy3(220.f, 60.f);
    Enemy enemy4(280.f, 60.f);

    this->enemy.push_back(enemy1);
    this->enemy.push_back(enemy2);
    this->enemy.push_back(enemy3);
    this->enemy.push_back(enemy4);

}

bool Bullet_hell::isEnded() {
    return this->endb;
}

void Bullet_hell::end() {
    this->endb = true;
}