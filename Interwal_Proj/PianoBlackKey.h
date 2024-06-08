#pragma once

#include <iostream>
#include "Button.h"

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class PianoBlackKey : public Button {
private:
	int id;
	std::string key;
public:
	PianoBlackKey();
	PianoBlackKey(int id, float x, float y, std::string pitch);
	~PianoBlackKey();

	std::string getPitch();
	int getID();

	void onButtonPress() override;
};