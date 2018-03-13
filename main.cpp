#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include "class/Game_event.hpp"
#include "class/Enemy.hpp"
#include "class/Bullet.hpp"
#include "class/Player.hpp"
#include "class/Bullet_hell.hpp"
#include "include/functions.cpp"

void thread_ticker(Bullet_hell *game) {

    int game_clock = clock();
    int time_tick;

    while(!game->isEnded()) {

        time_tick = floor(((double) (clock() - game_clock) / CLOCKS_PER_SEC) * 1000); // 1 sec = 10,000 UA

        if (time_tick%2 == 0) {
            //game->mtx_event.lock();
            game->addEvent(0);
            //game->mtx_event.unlock();
        }

    }

}

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
        //std::cout << "nb enmey     : " << game->enemy.size() << std::endl;
        std::cout << "fire         : " << game->player.bullet_list.size() << std::endl;
        std::cout << "nb event     : " << game->events.size() << std::endl;
        /* std::cout << "ticks        : " << game->time << std::endl; */


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
    int game_clock = clock();
    int time_tick, time_tick_old;

    while(!game->isEnded()) {

        time_tick_old = time_tick;
        time_tick = floor(((double) (clock() - game_clock) / CLOCKS_PER_SEC) * 10000); // 1 sec = 10 UA

        int event = eventPull(game);
        if (event != -1) {
            if (event == 1) {
                fire = true;
            } else if (event == 2) {
                fire = false;
            }
        }

        if (time_tick != time_tick_old && time_tick%2 == 0) {
            move_bullet(game); // mouvement des bullet
        }
            
        if (time_tick != time_tick_old && fire == true && time_tick%400 == 0) {
            game->player.fire();
        }


        move(game); // mouvement du player

    }

}

int main() {    

    Bullet_hell game;

    sf::Thread th_aff(&thread_aff, &game);
    sf::Thread th_player(&thread_player, &game);
    //sf::Thread ticker(&thread_ticker, &game);

    //ticker.launch();
    th_player.launch();
    th_aff.launch();

    th_aff.wait();
    th_player.wait();
    //ticker.wait();

    return 0;
}