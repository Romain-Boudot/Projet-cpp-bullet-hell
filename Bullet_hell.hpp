/* #include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include "Player.hpp"
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
        sf::Text pauset;

        Bullet_hell();

        bool isEnded();
        void end();
        void pause();
        void resume();
        bool isPaused();

    private:

        bool endb;
        bool pauseb;

};

Bullet_hell::Bullet_hell() {

    this->windowHeight = 800;
    this->windowWidth = 500;
    this->framerate = 60;
    this->endb = false;

    sf::Font font;
    font.loadFromFile("Roboto-Regular.ttf");

    sf::Text text("PAUSE", font);
    text.setCharacterSize(25);
    text.setStyle(sf::Text::Bold);
    text.setColor(sf::Color::Red);
    text.setPosition(230.f, 400.f);

    this->pauset = text;

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

void Bullet_hell::pause() {
    this->pauseb = true;
}

void Bullet_hell::resume() {
    this->pauseb = false;
}

bool Bullet_hell::isPaused() {
    return this->pauseb;
}