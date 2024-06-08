#include "PianoBlackKey.h"
#include "SFML/Audio.hpp"
#include <iostream>
#include <string>
#include "TextButton.h"

TextButton::TextButton() : Button()
{
}

TextButton::TextButton(float x, float y, float width, float height,float fontSize ,sf::Color defaultColor, sf::Color hoverColor, sf::Color pressedColor, std::string text)
	:Button(x, y, width, height, defaultColor, hoverColor, pressedColor)
{
	this->fontSize = fontSize;
	this->colorOfFont = defaultColor;
	this->pos_x = x;
	this->pos_y = y;
	this->text = text;
}

TextButton::~TextButton()
{
}

void TextButton::render(sf::RenderWindow& window)
{
	Button::render(window);
	


	TextDisplay textDisplay(this->pos_x, this->pos_y,this->fontSize ,sf::Color::Black, this->text);
	
	//center text
	float text_pos_x = this->pos_x + this->shape.getGlobalBounds().width / 2.0f - textDisplay.m_text.getGlobalBounds().width / 2.0f;
	float text_pos_y = this->pos_y + this->shape.getGlobalBounds().height / 2.0f - textDisplay.m_text.getGlobalBounds().height;


	textDisplay.m_text.setPosition(text_pos_x, text_pos_y);

	this->textToDisplay = textDisplay;

	this->textToDisplay.render(window);

}

void TextButton::onButtonPress()
{
}

