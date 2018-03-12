/* #include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include "Player.hpp"
#include "Enemy.hpp" */

class Bullet {

    public:

        sf::RectangleShape bullet_hit_box;

        Bullet(float x, float y);

        bool isDead();

    private:

        bool dead;

};

Bullet::Bullet(float x, float y) {

    sf::Vector2f size(3.f, 6.f);

    sf::RectangleShape r(size);
    r.setPosition(x, y);

    this->bullet_hit_box = r;
    this->dead = false;

}

bool Bullet::isDead() {

    return this->dead;
    
}