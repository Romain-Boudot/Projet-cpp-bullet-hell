#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include <unistd.h>
#include "class/Event.hpp"
#include "class/Controler.hpp"
#include "class/Game_event.hpp"
#include "class/Enemy.hpp"
#include "class/Bullet.hpp"
#include "class/Player.hpp"
#include "class/Bullet_hell.hpp"
#include "include/functions.cpp"

void thread_aff(Bullet_hell *game) { // thread d'affichage

    sf::RenderWindow window(sf::VideoMode(game->windowWidth, game->windowHeight), "Bullet Hell");
    window.setFramerateLimit(game->framerate); // framerate
    //sf::Clock fps_clock;
    //float fps = 0, fps_tmp = 0;

    window.setMouseCursorVisible(false); // pas de pointeur en jeu

    while (window.isOpen()) {
        
        sf::Event event;

        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
            }

            game->mtx_event.lock();

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
            game->mtx_controler.lock();

            if (event.type == sf::Event::MouseMoved) {
                
                if (game->controler.joy != 0) game->controler.joy = 0;

                game->controler.mouse_posi.x = event.mouseMove.x;
                game->controler.mouse_posi.y = event.mouseMove.y;

            }

            if (event.type == sf::Event::JoystickMoved) {

                if (game->controler.joy != 1) game->controler.joy = 1;

                if (event.joystickMove.axis == sf::Joystick::X) {
                    game->controler.axisX = event.joystickMove.position;
                } else if (event.joystickMove.axis == sf::Joystick::Y) {
                    game->controler.axisY = event.joystickMove.position;
                } else if (event.joystickMove.axis == sf::Joystick::R) {
                    if (event.joystickMove.position < -95) {
                        game->addEvent(0, 2);
                    } else {
                        game->addEvent(0, 1);
                    }
                }

            }
    
            game->mtx_controler.unlock();
            
        }

        window.clear(sf::Color(0, 0, 30, 200));
        window.draw(game->player.player_hit_box);


        game->mtx_vect_enemy.lock();

        for (int cpt = 0; cpt < game->enemy.size(); cpt++) {

            window.draw(game->enemy[cpt].enemy_circle);

        }

        game->mtx_vect_enemy.unlock();


        game->mtx_vect_player_bullet.lock();

        for (int cpt = 0; cpt < game->player.bullet_list.size(); cpt++) {

            window.draw(game->player.bullet_list[cpt].bullet_hit_box);

        }

        game->mtx_vect_player_bullet.unlock();

        window.display();

    }

    game->end();

}

void thread_player(Bullet_hell *game) {

    bool fire = false;
    int event, ticks = 0;
    Controler controler;
    sf::Clock tick_clock;
    std::vector<Event> events;

    while(!game->isEnded()) {

        tickcounter(&tick_clock, &ticks);

        game->mtx_event.lock();
            eventPull(game, &events, 0);
        game->mtx_event.unlock();

        for (int cpt = 0; cpt < events.size(); cpt++) {

            if (events[cpt].name == 1) {
                fire = true;
            } else if (events[cpt].name == 2) {
                fire = false;
            }

        }
        
        events.clear();

        if (ticks%200 == 0 && fire == true) {
            game->player.fire();
        }

        game->mtx_controler.lock();
            move(game); // mouvement du player
            move_bullet(game); // mouvement des bullet
        game->mtx_controler.unlock();

    }

}

void thread_enemy(Bullet_hell *game) {

    int event, ticks = 0, pl;
    sf::Clock tick_clock;
    sf::Clock random;

    sf::Vector2f corectif_hit_box_enemy(-10.f, -10.f);
    sf::Vector2f corectif_hit_box_bullet_player(-2.f, -3.f);

    while(!game->isEnded()) {

        tickcounter(&tick_clock, &ticks);

        for (int cpt = 0; cpt < game->enemy.size(); cpt++) {

            game->enemy[cpt].move();
            
            if (game->enemy[cpt].enemy_circle.getPosition().y > 800) {
                game->enemy.erase(game->enemy.begin() + cpt);
            }
            
            for (int cpt1 = 0; cpt1 < game->player.bullet_list.size(); cpt1++) {

                if (collision(game->player.bullet_list[cpt1].bullet_hit_box.getPosition() + corectif_hit_box_enemy, 
                    game->player.bullet_list[cpt1].radiusHit, 
                    game->enemy[cpt].enemy_circle.getPosition() + corectif_hit_box_bullet_player, 
                    game->enemy[cpt].radiusHit ))
                {
                    game->hitEnemy(cpt);
                    game->killPlayerBullet(cpt1);
                }

            }

        }

        if (game->placesLeft() > 0 and ticks%200 == 0) {

            game->addEnemy(
                (int)(random.getElapsedTime().asSeconds() * 1000)%500,
                1.f,
                ((int)random.getElapsedTime().asSeconds() * 1000)%100 / 100,
                0.005f
            );

        }

        /* system("clear");
        std::cout << "perf  : " << tick_clock.getElapsedTime().asSeconds() << std::endl; */

    }

}

int main() {    

    Bullet_hell game;

    sf::Thread th_aff(&thread_aff, &game);
    sf::Thread th_player(&thread_player, &game);
    sf::Thread th_enemy(&thread_enemy, &game);

    th_player.launch();
    th_enemy.launch();
    th_aff.launch();

    th_aff.wait();
    th_enemy.wait();
    th_player.wait();

    return 0;

}