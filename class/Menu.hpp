#include "SFML/Graphics.hpp"
#include <iostream>
using namespace std;

#define MAX_NUMBER_OF_ITEMS 6

class Menu {

    public:

        Menu(float width, float height);
        ~Menu();
		

        void draw(sf::RenderWindow &window);
		void drawOptions(sf::RenderWindow &window);
        void MoveUp();
        void MoveDown();
        int  GetPressedItem() { return selectedItemIndex; }
		void SetPressedItem(int key) { selectedItemIndex = key; }

    private:

        int selectedItemIndex;
        sf::Font font;
        sf::Text menu[MAX_NUMBER_OF_ITEMS];

};

Menu::Menu(float width, float height) {

	if (!font.loadFromFile("assets/Roboto-Regular.ttf")) {

		cout << "Erreur durant le chargement de la police" << endl;
	}


	menu[0].setFont(font);
	menu[0].setColor(sf::Color::Red);
	menu[0].setString("Jouer");
	menu[0].setPosition(sf::Vector2f(width / 2.5, height / (MAX_NUMBER_OF_ITEMS + 1) * 0));

	menu[1].setFont(font);
	menu[1].setColor(sf::Color::White);
	menu[1].setString("Options");
	menu[1].setPosition(sf::Vector2f(width / 2.5, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	menu[2].setFont(font);
	menu[2].setColor(sf::Color::White);
	menu[2].setString("Quitter");
	menu[2].setPosition(sf::Vector2f(width / 2.5, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

    menu[3].setFont(font);
	menu[3].setColor(sf::Color::White);
	menu[3].setString("Clavier");
	menu[3].setPosition(sf::Vector2f(width / 2.5, height / (MAX_NUMBER_OF_ITEMS + 1) * 0));

    menu[4].setFont(font);
	menu[4].setColor(sf::Color::White);
	menu[4].setString("Mannetes");
	menu[4].setPosition(sf::Vector2f(width / 2.5, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	menu[5].setFont(font);
	menu[5].setColor(sf::Color::White);
	menu[5].setString("Retour");
	menu[5].setPosition(sf::Vector2f(width / 2.5, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));


	selectedItemIndex = 0;
}

Menu::~Menu() {
    
}

void Menu::draw(sf::RenderWindow &window) {

	for (int i = 0; i < 3; i++) {

		window.draw(menu[i]);
	}
}

void Menu::drawOptions(sf::RenderWindow &window) {

	for (int i = 3; i < 6; i++) {

		window.draw(menu[i]);
	}
}

void Menu::MoveUp() {

	if (selectedItemIndex - 1 >= 0) {

		menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setColor(sf::Color::Red);
	}
}

void Menu::MoveDown() {

	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS) {

		menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setColor(sf::Color::Red);
	}
}