#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>

class Bullet_hell {
    public:
        int windowHeight;
        int windowWidth;
        sf::RenderWindow *window;
        sf::CircleShape *player_sprite;
};

void thread_aff(Bullet_hell *game) { // thread d'affichage

    sf::RenderWindow window(sf::VideoMode(500, 800), "SFML works!");
    window.setFramerateLimit(60); // framerate

    game->window = &window;
    sf::CircleShape *player_sprite = game->player_sprite;

    window.setMouseCursorVisible(false);

    while (window.isOpen()) {

        
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Vector2i mouse_posi = sf::Mouse::getPosition(window);
        sf::Vector2f mouse_posf;

        mouse_posf.x = ((int) mouse_posi.x) - player_sprite->getRadius();
        mouse_posf.y = ((int) mouse_posi.y) - player_sprite->getRadius();

        player_sprite->setPosition(mouse_posf);

        window.clear(sf::Color(0, 0, 30, 200));
        window.draw(*player_sprite);
        window.display();

    }

}

int main() {    
    
    sf::CircleShape player_sprite(5.f,100);
    player_sprite.setFillColor(sf::Color::Green);

    Bullet_hell game;

    game.player_sprite = &player_sprite;

    sf::Thread th_aff(&thread_aff, &game);
    
    th_aff.launch();

    th_aff.wait();

    return 0;
}