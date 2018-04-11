#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class Background {

    public:

    Background();

    void drawBackground(sf::RenderWindow &window);

    private:

    sf::Texture backgroundTexture;
    sf::Sprite background; 
};

Background::Background() {

    if (!backgroundTexture.loadFromFile("assets/background.jpg")) {

    cout << "Erreur durant le chargement de l'image de background" << endl;

    }else {

        background.setTexture(backgroundTexture); 
               
    }
}

void Background::drawBackground(sf::RenderWindow &window) {

    window.draw(background);
}