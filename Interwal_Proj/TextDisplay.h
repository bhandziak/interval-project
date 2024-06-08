#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class TextDisplay {
private:
    sf::Font m_font;
    sf::Color defaultColor;

public:
    sf::Text m_text;

    TextDisplay();
    TextDisplay(float x, float y, float fontSize,sf::Color color ,const std::string& text);

    void render(sf::RenderWindow& window);
};