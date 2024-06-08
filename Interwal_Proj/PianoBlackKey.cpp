#include "PianoBlackKey.h"
#include "SFML/Audio.hpp"
#include <iostream>
#include <string>

PianoBlackKey::PianoBlackKey() : Button()
{
}

PianoBlackKey::PianoBlackKey(int id, float x, float y, std::string pitch)
	:Button(x, y, 20, 60, sf::Color::Black, sf::Color(20, 20, 20), sf::Color(119, 136, 153))
{
	this->id = id;
	this->key = pitch;
}

PianoBlackKey::~PianoBlackKey()
{
}

std::string PianoBlackKey::getPitch()
{
	return this->key;
}

int PianoBlackKey::getID()
{
	return this->id;
}

void PianoBlackKey::onButtonPress()
{
	if (this->isPressed()) {
		//sf::SoundBuffer buffer;

		//if (!buffer.loadFromFile("Assets/Piano/" + this->key + ".ogg")) {
		//	// Error loading the sound file
		//}

		//sf::Sound sound;
		//sound.setBuffer(buffer);

		//// Play the sound
		//sound.play();

		std::cout << this->key << std::endl;
	}
}
