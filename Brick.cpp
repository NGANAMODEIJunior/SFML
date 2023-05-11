#include "Brick.h"

Brick::Brick(int x, int y, int width, int height, int health) :
	position(x, y), size(width, height), health(health)
{
	shape.setSize(size);
	shape.setOutlineThickness(2);
	shape.setOutlineColor(sf::Color::Black);
	shape.setPosition(position);
	shape.setFillColor(getColorFromLife());
}

void Brick::draw(sf::RenderWindow& window)
{
	if (isAlive()) {
		window.draw(shape);
	}
}

sf::Color Brick::getColorFromLife()
{
	switch (health) {
	case 1:
		return sf::Color::Red;
	case 2:
		return sf::Color::Yellow;
	case 3:
		return sf::Color::Green;
	default:
		return sf::Color::White;
	}
}

bool Brick::isAlive() const
{
	return health > 0;
}

void Brick::hit()
{
	--health;
	shape.setFillColor(getColorFromLife());
}

const sf::Vector2f& Brick::getPosition() const
{
	return position;
}

const sf::Vector2f& Brick::getSize() const
{
	return size;
}

void Brick::destroyAndDelete(std::deque<Brick*>& bricks)
{
	auto it = std::find(bricks.begin(), bricks.end(), this);
	if (it != bricks.end()) {
		bricks.erase(it);
	}
	delete this;
}
