#pragma once
#include <SFML/Graphics.hpp>
#include <deque>


class Brick
{
private:
	sf::RectangleShape shape;
	sf::Vector2f position;
	sf::Vector2f size;
	int health;
public:
	Brick(int x, int y, int width, int height, int health);
	~Brick();
	void draw(sf::RenderWindow& window);
	sf::Color getColorFromLife();
	bool isAlive();
	void hit();
	sf::Vector2f getPosition();
	sf::Vector2f getSize();
	sf::RectangleShape getShape(); // Renvoyer la forme de la brique
	void destroyAndDelete(std::deque<Brick*>& bricks); // Supprimer la brique de la mémoire et de la deque

};

