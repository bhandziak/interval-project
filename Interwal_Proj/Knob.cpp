#include "Knob.h"

Knob::Knob()
{
	this->m_mouse_last_pos = 0;
	this->value = 0;

	this->button_state = BTN_IDLE;
	this->activated = false;

	this->shape.setPosition(sf::Vector2f(0, 0));
	this->shape.setRadius(100);

	//this->hand.setPosition(sf::Vector2f(0 + 100 / 2.0f, 0));
	//this->hand.setSize(sf::Vector2f(5, 10));
	//this->hand.setFillColor(sf::Color::Black);



	this->defaultColor = defaultColor;
	this->hoverColor = hoverColor;
	this->pressedColor = pressedColor;

	this->shape.setFillColor(this->defaultColor);
}

Knob::Knob(float x, float y, float radius, sf::Color defaultColor, sf::Color hoverColor, sf::Color pressedColor)
{
	this->m_mouse_last_pos = 0;
	this->value = 0;

	this->button_state = BTN_IDLE;
	this->activated = false;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setRadius(radius);

	sf::Texture texture;
	texture.loadFromFile("Assets/knob.png");

	this->shape.setTexture(&texture);

	//this->hand.setPosition(sf::Vector2f(x + radius - 2.5f, y));
	//this->hand.setSize(sf::Vector2f(5, 10));
	//this->hand.setFillColor(sf::Color::Black);


	this->shape.setOrigin(shape.getLocalBounds().width / 2.0f, shape.getLocalBounds().height / 2.0f);
	this->shape.setRotation(312);

	//this->hand.setOrigin(shape.getLocalBounds().width / 2.0f - 3*radius, shape.getLocalBounds().height / 2.0f);


	this->defaultColor = defaultColor;
	this->hoverColor = hoverColor;
	this->pressedColor = pressedColor;

	this->shape.setFillColor(this->defaultColor);
}

Knob::~Knob()
{
}

const bool Knob::isPressed() const
{
	return this->activated;
}

void Knob::update(const sf::Vector2f mousePos)
{
	this->button_state = BTN_IDLE;

	this->activated = false;

	if (this->shape.getGlobalBounds().contains(mousePos)) {
		this->activated = false;
		this->button_state = BTN_HOVER;

		bool isCurrentlyPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
		if (isCurrentlyPressed && !wasPressedLastFrame) {
			// PRESSED ONES
			this->button_state = BTN_PRESS;
			this->activated = true;
			wasPressedLastFrame = true; 

			this->m_mouse_last_pos = mousePos.y;
		}
		else if (!isCurrentlyPressed) {
			// NOT PRESSED
			wasPressedLastFrame = false;
			this->m_mouse_last_pos = 0;
			//this->value = 0;
		}
		else {
			// ROTATE AND CALC VAL
			this->button_state = BTN_PRESS;
			float pos_difference = this->m_mouse_last_pos - mousePos.y;

			float rotation = this->shape.getRotation();

			if (rotation >= 160) {
				this->value = rotation - 168;
			}
			else {
				this->value = rotation + 192;
			}

			this->value = this->value / 294.f * 100;

			if (pos_difference > 0 && ((160 < rotation && rotation <= 360) || (0 <= rotation && rotation < 98))) {
				this->shape.rotate(6.f);
			}
			else if (pos_difference < 0 && ((168 < rotation && rotation <= 360) || (0 <= rotation && rotation < 110))) {
				this->shape.rotate(-6.f);
			}
			//this->hand.rotate(angle);
			//std::cout << this->value << std::endl;

			this->m_mouse_last_pos = mousePos.y;
		}
	}
	else {
		// NOT HOVER
		wasPressedLastFrame = false;
	}

}

void Knob::render(sf::RenderWindow& window)
{
	sf::Texture texture;
	texture.loadFromFile("Assets/knob.png");

	this->shape.setTexture(&texture);

	window.draw(this->shape);
	//window.draw(this->hand);
}

float Knob::getValue()
{
	return this->value;
}

void Knob::setValue(float val)
{
	this->value = val;
}
