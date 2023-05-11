#include "Player.h"

Player::Player(int y, int width, int height) : position(0, y), size(width, height)
{
	shape.setPosition(position);
	shape.setSize(size);
	shape.setFillColor(sf::Color::Green);
}

void Player::draw(sf::RenderWindow& window)
{
	position.x = sf::Mouse::getPosition(window).x - size.x / 2;
	shape.setPosition(position);
	window.draw(shape);
}

const sf::Vector2f& Player::getPosition() const
{
	return position;
}

const sf::Vector2f& Player::getSize() const
{
	return size;
}
