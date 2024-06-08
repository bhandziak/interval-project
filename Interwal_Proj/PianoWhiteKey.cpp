#include "PianoWhiteKey.h"
#include "SFML/Audio.hpp"
#include <iostream>
#include <string>

PianoWhiteKey::PianoWhiteKey() : Button()
{
}

PianoWhiteKey::PianoWhiteKey(int id, float x, float y, std::string pitch)
	:Button(x, y, 25, 100, sf::Color::White, sf::Color(220, 220, 220), sf::Color(119, 136, 153))
{
	this->id = id;
	this->key = pitch;
}

PianoWhiteKey::~PianoWhiteKey()
{
}

std::string PianoWhiteKey::getPitch()
{
	return this->key;
}

int PianoWhiteKey::getID()
{
	return this->id;
}

void PianoWhiteKey::onButtonPress()
{
	if (this->isPressed()) {
		std::cout << this->key << std::endl;
	}
}
