#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

class Param {
    public:
        sf::RenderWindow *window;
        sf::CircleShape *shape;
};

void thread_aff(Param param) {

    sf::RenderWindow *window = param.window;
    sf::CircleShape *shape = param.shape;

    std::cout << "thread aff" << std::endl;

    window->create(sf::VideoMode(500, 800), "SFML works!");

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        sf::Vector2i mouse_posi = sf::Mouse::getPosition(*window);
        sf::Vector2f mouse_posf;

        mouse_posf.x = ((int) mouse_posi.x) - shape->getRadius();
        mouse_posf.y = ((int) mouse_posi.y) - shape->getRadius();

        shape->setPosition(mouse_posf);

        window->clear();
        window->draw(*shape);
        window->display();


    }

}

int main() {

    sf::RenderWindow window(sf::VideoMode(500, 800), "SFML works!");
    window.setFramerateLimit(60); // framerate
    sf::CircleShape shape(100.f,100);
    shape.setFillColor(sf::Color::Green);

    Param param;

    param.shape = &shape;
    param.window = &window;

    std::cout << "main thread" << std::endl;

    

    sf::Thread thread1(&thread_aff, param);
    
    thread1.launch();

    thread1.wait();

    return 0;
}