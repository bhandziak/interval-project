#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "TextDisplay.h"

TextDisplay::TextDisplay()
{
}

TextDisplay::TextDisplay(float x, float y,float fontSize ,sf::Color color, const std::string& text)
{
    if (!m_font.loadFromFile("Assets/Fartage.ttf")) {
    }

    this->defaultColor = color;

    m_text.setFont(m_font);
    m_text.setString(text);
    m_text.setFillColor(color);
    m_text.setCharacterSize(fontSize);

    m_text.setPosition(x, y);
}

void TextDisplay::render(sf::RenderWindow& window)
{
    window.draw(m_text);
}
