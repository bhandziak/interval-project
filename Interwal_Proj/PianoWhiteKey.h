#pragma once

#include <iostream>
#include "Button.h"

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class PianoWhiteKey : public Button {
private:
	std::string key;
	int id;
public:
	PianoWhiteKey();
	PianoWhiteKey(int id, float x, float y, std::string pitch);
	~PianoWhiteKey();

	std::string getPitch();
	int getID();

	void onButtonPress() override;
};