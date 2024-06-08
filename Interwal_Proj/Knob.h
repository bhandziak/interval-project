#pragma once

#include <iostream>
#include "Button.h"
#include "TextDisplay.h"

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"


class Knob{
private:
	bool wasPressedLastFrame;
	bool activated;

	float value;
	float m_mouse_last_pos;

	sf::Color defaultColor;
	sf::Color hoverColor;
	sf::Color pressedColor;
public:
	sf::CircleShape shape;
	//sf::RectangleShape hand;
	Knob();
	Knob(float x, float y, float radius, sf::Color defaultColor, sf::Color hoverColor, sf::Color pressedColor);
	~Knob();

	short button_state;

	const bool isPressed() const;

	void update(const sf::Vector2f mousePos);
	void virtual render(sf::RenderWindow& window);

	float getValue();
	void setValue(float val);
};