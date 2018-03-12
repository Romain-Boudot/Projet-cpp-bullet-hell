#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include <unistd.h>
#include "class/Game_event.hpp"
#include "class/Enemy.hpp"
#include "class/Bullet.hpp"
#include "class/Player.hpp"
#include "class/Bullet_hell.hpp"
#include "include/functions.cpp"

void thread_aff(Bullet_hell *game) { // thread d'affichage

    sf::RenderWindow window(sf::VideoMode(game->windowWidth, game->windowHeight), "Bullet Hell");
    window.setFramerateLimit(game->framerate); // framerate

    window.setMouseCursorVisible(false); // pas de pointeur en jeu

    while (window.isOpen()) {
        
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
                if (event.mouseButton.button == sf::Mouse::Right)
                    game->addEvent(0);
            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Space)
                    game->addEvent(1);
            if (event.type == sf::Event::KeyReleased)
                if (event.key.code == sf::Keyboard::Space)
                    game->addEvent(2);
        }


        game->mouse_posi = sf::Mouse::getPosition(window); // recuperation de la position de la souris


        system("clear");
        std::cout << "pos player x : " << game->mouse_posi.x << std::endl;
        std::cout << "pos player y : " << game->mouse_posi.y << std::endl;
        std::cout << "nb enmey     : " << game->enemy.size() << std::endl;
        std::cout << "fire         : " << game->player.bullet_list.size() << std::endl;


        window.clear(sf::Color(0, 0, 30, 200));
        window.draw(game->player.player_hit_box);
        for (int cpt = 0; cpt < game->enemy.size(); cpt++) {
            if (!game->enemy[cpt].isdead()) {
                window.draw(game->enemy[cpt].enemy_circle);
            }
        }
        for (int cpt = 0; cpt < game->player.bullet_list.size(); cpt++) {
            if (!game->player.bullet_list[cpt].isDead()) {
                window.draw(game->player.bullet_list[cpt].bullet_hit_box);
            }
        }
        window.display();

    }

    game->end();

}

void thread_player(Bullet_hell *game) {

    while(!game->isEnded()) {

        int event = eventPull(game);
        if (event != -1) {
            if (event == 0) game->player.fire();
        }

        move(game); // mouvement du player

        move_bullet(game); // mouvement des bullet

    }

}

int main() {    

    Bullet_hell game;

    sf::Thread th_aff(&thread_aff, &game);
    sf::Thread th_player(&thread_player, &game);
    
    th_aff.launch();
    th_player.launch();

    th_aff.wait();
    th_player.wait();

    return 0;
}