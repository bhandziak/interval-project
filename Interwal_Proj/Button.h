#pragma once

#include <iostream>

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

enum button_states {BTN_IDLE = 0, BTN_HOVER, BTN_PRESS};

class Button
{
private:
	bool wasPressedLastFrame;
	bool activated;


	sf::Color defaultColor;
	sf::Color hoverColor;
	sf::Color pressedColor;

public:
	sf::RectangleShape shape;
	Button();
	Button(float x, float y, float width, float height, sf::Color defaultColor, sf::Color hoverColor, sf::Color pressedColor);
	~Button();

	short button_state;

	const bool isPressed() const;

	void virtual onButtonPress();

	void update(const sf::Vector2f mousePos);
	void virtual render(sf::RenderWindow& window);


	void setPressedColor();
	void setDefaultColor();
};