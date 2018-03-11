/* #include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector> */

class Player {

    public:

        sf::CircleShape player_hit_box;

        Player();
};

Player::Player() {

    sf::CircleShape player_hit_box(5.f,100);
    player_hit_box.setFillColor(sf::Color::Green);

    this->player_hit_box = player_hit_box;

}