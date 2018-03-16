#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include <unistd.h>
#include "class/Event.hpp"
#include "class/Game_event.hpp"
#include "class/Enemy.hpp"
#include "class/Bullet.hpp"
#include "class/Player.hpp"
#include "class/Bullet_hell.hpp"
#include "include/functions.cpp"

void thread_aff(Bullet_hell *game) { // thread d'affichage

    sf::RenderWindow window(sf::VideoMode(game->windowWidth, game->windowHeight), "Bullet Hell");
    window.setFramerateLimit(game->framerate); // framerate
    sf::Clock fps_clock;

    float fps = 0, fps_tmp = 0;

    window.setMouseCursorVisible(false); // pas de pointeur en jeu

    while (window.isOpen()) {
        
        sf::Event event;

        while (window.pollEvent(event)) {

            game->mtx_event.lock();

            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Right) {
                    game->addEvent(0, 0);
                }
            }

            if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Space){
                    game->addEvent(0, 1);
                }
            }

            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Space) {
                    game->addEvent(0, 2);
                }
            }

            game->mtx_event.unlock();
        }

        game->mtx_pos_player.lock();
        game->mouse_posi = sf::Mouse::getPosition(window); // recuperation de la position de la souris
        game->mtx_pos_player.unlock();

        fps_tmp++;

        if (fps_clock.getElapsedTime().asSeconds() >= 1) {
            fps = fps_tmp;
            fps_tmp = 0;
            fps_clock.restart();
        }

        /* system("clear");
        std::cout << "pos player x : " << game->mouse_posi.x << std::endl;
        std::cout << "pos player y : " << game->mouse_posi.y << std::endl;
        //std::cout << "nb enmey     : " << game->enemy.size() << std::endl;
        std::cout << "fire         : " << game->player.bullet_list.size() << std::endl;
        std::cout << "nb event     : " << game->events.size() << std::endl;
        std::cout << "fps          : " << fps << std::endl;
        // std::cout << "ticks        : " << game->time << std::endl; */

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

    bool fire = false;
    int event, ticks = 0;
    sf::Clock tick_clock;
    std::vector<Event> events;

    while(!game->isEnded()) {

        tickcounter(&tick_clock, &ticks);

        game->mtx_event.lock();
        eventPull(game, &events, 0);
        game->mtx_event.unlock();

        for (int cpt = 0; cpt < events.size(); cpt++) {

            event = events[cpt].code;

            if (event == 1) {
                fire = true;
            } else if (event == 2) {
                fire = false;
            }

        }
        
        events.clear();

        if (ticks%200 == 0) {
            game->player.fire();
        }

        game->mtx_pos_player.lock();
        move(game); // mouvement du player
        move_bullet(game); // mouvement des bullet
        game->mtx_pos_player.unlock();

    }

}

/* void thread_enemy(Bullet_hell *game) {



} */

int main() {    

    Bullet_hell game;

    sf::Thread th_aff(&thread_aff, &game);
    sf::Thread th_player(&thread_player, &game);
    //sf::Thread th_enemy(&thread_enemy, &game);

    th_player.launch();
    //th_enemy.launch();
    th_aff.launch();

    th_aff.wait();
    //th_enemy.wait();
    th_player.wait();

    return 0;
}