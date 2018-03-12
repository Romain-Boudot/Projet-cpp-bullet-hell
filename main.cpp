#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include <unistd.h>
#include "Enemy.hpp"
#include "Bullet.hpp"
#include "Player.hpp"
#include "Bullet_hell.hpp"
#include "menu/Menu.h"

void thread_aff(Bullet_hell *game) { // thread d'affichage

    sf::RenderWindow window(sf::VideoMode(game->windowWidth, game->windowHeight), "Bullet Hell");
    window.setFramerateLimit(game->framerate); // framerate

    game->window = &window;

    window.setMouseCursorVisible(false); // pas de pointeur en jeu

    while (window.isOpen()) {

        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
                if (event.mouseButton.button == sf::Mouse::Right)
                    game->player.fire();
            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Space)
                    game->pause();
            if (event.type == sf::Event::KeyReleased)
                if (event.key.code == sf::Keyboard::Space)
                    game->resume();
        }

        game->mouse_posi = sf::Mouse::getPosition(window);

        system("clear");
        std::cout << "pos player x : " << game->mouse_posi.x << std::endl;
        std::cout << "pos player y : " << game->mouse_posi.y << std::endl;
        std::cout << "nb enmey     : " << game->enemy.size() << std::endl;
        std::cout << "fire         : " << game->player.bullet_list.size() << std::endl;

        window.clear(sf::Color(0, 0, 30, 200));
        //if (game->isPaused()) {
        window.draw(game->pauset);
        //}
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

    sf::Vector2f mouse_posf;

    while(!game->isEnded()) {

        mouse_posf.x = ((int) game->mouse_posi.x) - game->player.player_hit_box.getRadius();
        mouse_posf.y = ((int) game->mouse_posi.y) - game->player.player_hit_box.getRadius();

        game->player.player_hit_box.setPosition(mouse_posf);

        //game->player.fire();

    }

}

int main() {

    {
        sf::RenderWindow window(sf::VideoMode(600, 600), "SFML WORK!");

        Menu menu(window.getSize().x, window.getSize().y);

        while (window.isOpen())
        {
            sf::Event event;

            while (window.pollEvent(event))
            {
                switch (event.type)
                {
                    case sf::Event::KeyReleased:
                        switch (event.key.code)
                        {
                            case sf::Keyboard::Up:
                                menu.MoveUp();
                                break;

                            case sf::Keyboard::Down:
                                menu.MoveDown();
                                break;

                            case sf::Keyboard::Return:
                                switch (menu.GetPressedItem())
                                {
                                    case 0:
                                        std::cout << "Play button has been pressed" << std::endl;
                                        break;
                                    case 1:
                                        std::cout << "Option button has been pressed" << std::endl;
                                        break;
                                    case 2:
                                        window.close();
                                        break;
                                }

                                break;
                        }

                        break;
                    case sf::Event::Closed:
                        window.close();

                        break;

                }
            }

            window.clear();

            menu.draw(window);

            window.display();
        }
    }

    Bullet_hell game;

    sf::Thread th_aff(&thread_aff, &game);
    sf::Thread th_player(&thread_player, &game);

    th_aff.launch();
    th_player.launch();

    th_aff.wait();
    th_player.wait();

    return 0;
}

