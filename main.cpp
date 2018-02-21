#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 800), "SFML works!");
    window.setFramerateLimit(60); // framerate
    sf::CircleShape shape(100.f,100);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Vector2i mouse_posi = sf::Mouse::getPosition(window);
        sf::Vector2f mouse_posf;

        mouse_posf.x = ((int) mouse_posi.x) - shape.getRadius();
        mouse_posf.y = ((int) mouse_posi.y) - shape.getRadius();

        shape.setPosition(mouse_posf);

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}