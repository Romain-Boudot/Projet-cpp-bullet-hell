#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include <unistd.h>
#include "Enemy.hpp"
#include "Player.hpp"
#include "Bullet_hell.hpp"

void thread_aff(Bullet_hell *game) { // thread d'affichage

    sf::RenderWindow window(sf::VideoMode(game->windowWidth, game->windowHeight), "Bullet Hell");
    window.setFramerateLimit(game->framerate); // framerate

    sf

    game->window = &window;

    window.setMouseCursorVisible(false); // pas de pointeur en jeu

    while (window.isOpen()) {
        
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        game->mouse_posi = sf::Mouse::getPosition(window);

        system("clear");
        std::cout << "pos player x :" << game->mouse_posi.x << std::endl;
        std::cout << "pos player y :" << game->mouse_posi.y << std::endl;
        std::cout << "nb enmey     :" << game->enemy.size() << std::endl;

        window.clear(sf::Color(0, 0, 30, 200));
        window.draw(game->player.player_hit_box);
        for (int cpt = 0; cpt < game->enemy.size(); cpt++) {
            if (!game->enemy[cpt].isdead()) {
                window.draw(game->enemy[cpt].enemy_circle);
            }
        }
        window.display();

    }

    game->end();

}

void thread_player(Bullet_hell *game) {

    sf::RenderWindow *window = game->window;
    sf::Vector2f mouse_posf;

    while(!game->isEnded()) {

        mouse_posf.x = ((int) game->mouse_posi.x) - game->player.player_hit_box.getRadius();
        mouse_posf.y = ((int) game->mouse_posi.y) - game->player.player_hit_box.getRadius();

        game->player.player_hit_box.setPosition(mouse_posf);

        game->player->fire();

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