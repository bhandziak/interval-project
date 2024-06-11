#include "Button.h"

Button::Button()
{
	this->button_state = BTN_IDLE;

	this->shape.setPosition(sf::Vector2f(0, 0));
	this->shape.setSize(sf::Vector2f(100, 100));


	this->defaultColor = defaultColor;
	this->hoverColor = hoverColor;
	this->pressedColor = pressedColor;

	this->shape.setFillColor(this->defaultColor);
}

Button::Button(float x, float y, float width, float height, sf::Color defaultColor, sf::Color hoverColor, sf::Color pressedColor)
{
	this->button_state = BTN_IDLE;
	this->activated = false;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));


	this->defaultColor = defaultColor;
	this->hoverColor = hoverColor;
	this->pressedColor = pressedColor;

	this->shape.setFillColor(this->defaultColor);
}


Button::~Button()
{
}

const bool Button::isPressed() const
{
	return this->activated;
}

void Button::onButtonPress()
{
}

void Button::update(const sf::Vector2f mousePos)
{

	this->button_state = BTN_IDLE;

	this->activated = false;

	if (this->shape.getGlobalBounds().contains(mousePos)) {
		this->activated = false;
		this->button_state = BTN_HOVER;

		bool isCurrentlyPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
		if (isCurrentlyPressed && !wasPressedLastFrame) {
			// PRESSED
			this->button_state = BTN_PRESS;
			this->activated = true;
			wasPressedLastFrame = true;
		}
		else if (!isCurrentlyPressed) {
			// NOT PRESSED
			wasPressedLastFrame = false;
		}
		else {
			this->button_state = BTN_PRESS;
		}
	}
	else {
		// NOT HOVER
		wasPressedLastFrame = false;
	}

	switch (this->button_state)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->defaultColor);
		break;
	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		break;
	case BTN_PRESS:
		this->shape.setFillColor(this->pressedColor);
		break;
	default:
		this->shape.setFillColor(sf::Color::Red);
		break;
	}

	this->onButtonPress();
}

void Button::render(sf::RenderWindow& window)
{
	window.draw(this->shape);
}

void Button::setPressedColor()
{
	this->shape.setFillColor(this->pressedColor);
}

void Button::setDefaultColor()
{
	this->shape.setFillColor(this->defaultColor);
}
