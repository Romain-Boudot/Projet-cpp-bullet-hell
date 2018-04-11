#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include <unistd.h>
#include <sstream>

#define PI 3.14159265 // nombre pi ... simplement
#define WINDOW_HEIGHT 800 // taille de la fenetre (hauteur)
#define WINDOW_WIDTH 500 // taille de la fenetre (largeur)
#define FRAMERATE 90 // image par second (max)
#define ENEMY_MOVEMENT_DEC 0.99998 // multiplicateur pour la ralentissement des ennemis
#define ENEMY_MOVEMENT_INC 1.00003 // multiplicateur pour l'acceleration des ennemis
#define DEBUG 0

#include "class/Background.hpp"
#include "class/Menu.hpp"
#include "class/Event.hpp"
#include "class/Controler.hpp"
#include "class/Bullet.hpp"
#include "class/Enemy.hpp"
#include "class/Player.hpp"
#include "class/Bullet_hell.hpp"
#include "include/functions.cpp"

/*
 * Thread d'affichage
 * parametre :
 *   Bullet_hell // class de jeu
 * 
 * retourne rien
 * 
 */

void thread_aff(Bullet_hell *game) { // thread d'affichage

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Bullet Hell");
    window.setFramerateLimit(FRAMERATE); // framerate
    sf::Font font;
    font.loadFromFile("assets/Roboto-Regular.ttf");
    sf::Text text("coucou", font, 30);
    text.setColor(sf::Color::Magenta);
    text.setPosition(0.f, 0.f);
    sf::Clock game_clock;

    window.setMouseCursorVisible(false); // pas de pointeur en jeu

    while (window.isOpen()) {

        sf::Event event;

        if (game->isEnded()) {
            sf::Clock waiter;
            sf::Text game_over("GAME OVER", font, 30);
            game_over.setColor(sf::Color::Magenta);
            game_over.setPosition(170.f, 20.f);
            window.draw(game_over);
            window.display();
            while (waiter.getElapsedTime().asSeconds() < 5) { /* waiting */ }
            window.close();
        }

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

            game->mtx_controler.lock();

            if (event.type == sf::Event::JoystickMoved) {

                if (game->controler.joy != 1) game->controler.joy = 1;

                if (event.joystickMove.axis == sf::Joystick::X) {
                    game->controler.axisX = event.joystickMove.position;
                }
                if (event.joystickMove.axis == sf::Joystick::Y) {
                    game->controler.axisY = event.joystickMove.position;
                }
                if (event.joystickMove.axis == sf::Joystick::R) {
                    if (event.joystickMove.position < -95) {
                        game->addEvent(0, 2);
                    } else {
                        game->addEvent(0, 1);
                    }
                }
                if (event.joystickMove.axis == sf::Joystick::PovY) {
                    if (event.joystickMove.position == 100) {
                        sf::Vector2f correctif;
                        correctif.x = -game->controler.axisX;
                        correctif.y = -game->controler.axisY;                        
                        game->controler.correctif = correctif;
                    }

                }

            }

            text.setString(tostring(game));

            // (int) (game->get_killed_enemy() * (game_clock.getElapsedTime().asSeconds() + 1))

            game->mtx_event.unlock();

            if (event.type == sf::Event::KeyPressed) {

                if (game->controler.joy == true) game->controler.joy = false;

                if (event.key.code == sf::Keyboard::Up) {
                    game->controler.keyDir.y = -1;
                } else if (event.key.code == sf::Keyboard::Down) {
                    game->controler.keyDir.y = 1;
                } else if (event.key.code == sf::Keyboard::Right) {
                    game->controler.keyDir.x = 1;
                } else if (event.key.code == sf::Keyboard::Left) {
                    game->controler.keyDir.x = -1;
                }

            }

            if (event.type == sf::Event::KeyReleased) {
                
                if (event.key.code == sf::Keyboard::Up) {
                    game->controler.keyDir.y = 0;
                } else if (event.key.code == sf::Keyboard::Down) {
                    game->controler.keyDir.y = 0;
                } else if (event.key.code == sf::Keyboard::Right) {
                    game->controler.keyDir.x = 0;
                } else if (event.key.code == sf::Keyboard::Left) {
                    game->controler.keyDir.x = 0;
                }
            
            }

            game->controler.shiftKey = event.key.shift;

            game->mtx_controler.unlock();
            
        }

        window.clear(sf::Color(0, 0, 30, 200));
        window.draw(game->player.player_hit_box);

        game->mtx_vect_enemy.lock();

        for (int cpt = 0; cpt < game->enemy.size(); cpt++) {

            window.draw(game->enemy[cpt].enemy_circle);
            //window.draw(game->enemy[cpt].overcircle);
            
        }

        game->mtx_vect_enemy.unlock();


        game->mtx_vect_player_bullet.lock();

        for (int cpt = 0; cpt < game->player.bullet_list.size(); cpt++) {

            window.draw(game->player.bullet_list[cpt].bullet_hit_box);

        }

        game->mtx_vect_player_bullet.unlock();

        game->mtx_vect_enemy_bullet.lock();

        for (int cpt = 0; cpt < game->enemy_bullet_list.size(); cpt++) {

            window.draw(game->enemy_bullet_list[cpt].bullet_hit_box);

        }

        game->mtx_vect_enemy_bullet.unlock();

        window.draw(text);

        window.display();

    }

    game->end();

}


/*
 * Thread du player
 * parametre :
 *   Bullet_hell // class de jeu
 * 
 * retourne rien
 * 
 * gestion du joueur :
 *   evenement de tire
 *   mouvement du joueur
 *   mouvement des balles (joueur + ennemie) // optimisation de la répartition des taches entre thread
 *   check de collision entre le joueur et les entitées ennemis
 * 
 */


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


/*
 * Thread des ennemis
 * parametre :
 *   Bullet_hell // class de jeu
 * 
 * retourne rien
 * 
 * gestion des ennemis:
 *   mouvements des ennemis
 *   gestion des ennemis hors fenetre (kill)
 *   check de collision balles (player) ennemis
 *   gestion des hit ennemis
 *   mort des ennemis
 *   respawn des ennemis
 *   gestion de la balance du jeu (nombre d'ennemis sur le plateau en fonction de leur poids)
 * 
 */


void thread_enemy(Bullet_hell *game) {

    int event, ticks = 0;
    sf::Clock tick_clock;
    sf::Clock random;

    while (random.getElapsedTime().asSeconds() < 3) { /* waiting */ }

    while(!game->isEnded()) {

        tickcounter(&tick_clock, &ticks);

        if (ticks%(5000 - (game->get_killed_enemy() * 10)) == 0 && game->enemy.size() != 0) {

            int rdn = random.getElapsedTime().asSeconds() * 1000;
            rdn = rdn%(game->enemy.size());

            sf::Vector2f pos = game->player.player_hit_box.getPosition() + sf::Vector2f(5.f, 5.f);
            pos -= game->enemy[rdn].enemy_circle.getPosition() + sf::Vector2f(10.f, 10.f);
            float alpha = (float) atan(((double) pos.x / pos.y));
            pos.y = cos(alpha) / 100;
            pos.x = sin(alpha) / 100;

            game->mtx_vect_enemy_bullet.lock();

            Bullet bullet = game->enemy[rdn].fire(pos.x, pos.y, alpha);
            game->enemy_bullet_list.push_back(bullet);

            game->mtx_vect_enemy_bullet.unlock();

        }

        game->mtx_vect_enemy.lock();

        for (int cpt = 0; cpt < game->enemy.size(); cpt++) {

        
            game->enemy[cpt].move();

            // game->enemy[cpt].rotation(0.01); dead
            
            if (game->enemy[cpt].enemy_circle.getPosition().y > 800) {
                game->enemy.erase(game->enemy.begin() + cpt);
            }

            // old check collision player bullet ennemi

        }

        if (game->placesLeft() > 0 and ticks%2000 == 0) {

            game->addEnemy(
                ((int) (random.getElapsedTime().asSeconds() * 1000)%460) + 20,
                1.f, 0.f, 0.005f
            );

        }

        game->mtx_vect_enemy.unlock();

    }

}


void thread_collision(Bullet_hell *game) {

    int ticks = 0;
    sf::Clock tick_clock;

    while(!game->isEnded()) {

        // tick counter
        tickcounter(&tick_clock, &ticks);

        // check collision player / ennemi
        for (int cpt = 0; cpt < game->enemy.size(); cpt++) {
            if (collision(game->player.player_hit_box.getPosition() + sf::Vector2f(5.f, 5.f), 5,
            game->enemy[cpt].enemy_circle.getPosition() + sf::Vector2f(10.f, 10.f), 10)) {

                game->end();
            
            }
        }

        // check collision bullet player / ennemi
        for (int cpt = 0; cpt < game->enemy.size(); cpt++) {
            
            for (int cpt1 = 0; cpt1 < game->player.bullet_list.size(); cpt1++) {

                if (collision(game->player.bullet_list[cpt1].bullet_hit_box.getPosition() + sf::Vector2f(2.f, 3.f), 2,
                game->enemy[cpt].enemy_circle.getPosition() + sf::Vector2f(10.f, 10.f), 10))
                {
                    if (game->hitEnemy(cpt)) {
                        game->inc_killed_enemy();
                        if (game->get_killed_enemy()%5 == 0) {
                            game->inc_max_weight();
                        }
                    }
                    game->killPlayerBullet(cpt1);
                }

            }

        }

        // check collision bullet ennemis / player
        for (int cpt = 0; cpt < game->enemy_bullet_list.size(); cpt++) {

            if (collision(game->enemy_bullet_list[cpt].bullet_hit_box.getPosition() + sf::Vector2f(2.f, 3.f), 2,
            game->player.player_hit_box.getPosition() + sf::Vector2f(5.f, 5.f), 5)) {
                game->end();
            }

        }

    }

}


/*
 * Main thread
 * 
 * retourne int
 * 
 * gestion des thread:
 *   lancement thread player
 *   lancement thread ennemis
 *   lancement thread affichage
 * 
 *   attente du thread d'affichage
 *   attente du thread ennemis
 *   attente du thread player
 * 
 */


int main() {

    bool end = false;
    bool play;

    while(end == false) {

        play = menu();

        if (play == true) {

            std::cout << "je joue" << std::endl;

            Bullet_hell game;

            sf::Thread th_aff(&thread_aff, &game);
            sf::Thread th_player(&thread_player, &game);
            sf::Thread th_enemy(&thread_enemy, &game);
            sf::Thread th_coll(&thread_collision, &game);

            th_player.launch();
            th_enemy.launch();
            th_aff.launch();
            th_coll.launch();

            th_coll.wait();
            th_aff.wait();
            th_enemy.wait();
            th_player.wait();

        } else {
            
            std::cout << "je joue plus" << std::endl;

            end = true;

        }

    }

    std::cout << "je suis sorti" << std::endl;

    return 0;

}