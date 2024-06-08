#include "Klasa.h"
#include "Cointainers.h"

#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

int main() {

	Cointainers cointainers;
	cointainers.setUp();

	sf::RenderWindow window(sf::VideoMode(1000, 600), "Grand Piano", sf::Style::Close);

	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("Assets/stainway2.png");
	sf::Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundTexture);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		window.draw(backgroundSprite);

		cointainers.drawAll(window);
		cointainers.update(window);

		window.display();
	}


	return 0;
}

