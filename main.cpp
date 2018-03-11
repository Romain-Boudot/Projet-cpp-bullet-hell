#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include "Enemy.hpp"
#include "Bullet_hell.hpp"

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
        }

        sf::Vector2i mouse_posi = sf::Mouse::getPosition(window);
        sf::Vector2f mouse_posf;

        mouse_posf.x = ((int) mouse_posi.x) - game->player_sprite.getRadius();
        mouse_posf.y = ((int) mouse_posi.y) - game->player_sprite.getRadius();

        game->player_sprite.setPosition(mouse_posf);

        system("clear");
        std::cout << "pos player x :" << mouse_posi.x << std::endl;
        std::cout << "pos player y :" << mouse_posi.y << std::endl;
        std::cout << "nb enmey     :" << game->enemy.size() << std::endl;

        window.clear(sf::Color(0, 0, 30, 200));
        window.draw(game->player_sprite);
        for (int cpt = 0; cpt < game->enemy.size(); cpt++) {
            if (!game->enemy[cpt].isdead()) {
                window.draw(game->enemy[cpt].enemy_circle);
            }
        }
        window.display();

    }

}

int main() {    

    Bullet_hell game;

    sf::Thread th_aff(&thread_aff, &game);
    
    th_aff.launch();

    th_aff.wait();

    return 0;
}