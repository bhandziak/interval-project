#pragma once

#include <iostream>
#include "Button.h"
#include "TextDisplay.h"

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class TextButton : public Button {
private:
	sf::Text m_text;
	sf::Font m_font;

	TextDisplay textToDisplay;
	sf::Color colorOfFont;
	float pos_x;
	float pos_y;
	float fontSize;
	std::string text;
public:
	TextButton();
	TextButton(float x, float y, float width, float height,float fontSize ,sf::Color defaultColor, sf::Color hoverColor, sf::Color pressedColor, std::string text);
	~TextButton();

	void render(sf::RenderWindow& window) override;
	void onButtonPress() override;
};