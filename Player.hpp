/* #include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include <unistd.h> */

class Player {

    public:

        std::vector<Bullet> bullet_list;
        sf::CircleShape player_hit_box;

        Player();

        void fire();

};

Player::Player() {

    sf::CircleShape player_hit_box(5.f,100);
    player_hit_box.setFillColor(sf::Color::Green);

    this->player_hit_box = player_hit_box;

}

void Player::fire() {

    sf::Vector2f pos(this->player_hit_box.getPosition());

    Bullet bullet(pos.x, pos.y);

    this->bullet_list.push_back(bullet);
    
}