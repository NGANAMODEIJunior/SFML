#pragma once
#include "Player.h"
#include "Brick.h"


#include <SFML/Graphics.hpp>

class Ball
{
private:
	sf::CircleShape shape;
	sf::Vector2f oldPosition;
	sf::Vector2f position;
	float speed;
	int radius;
	int collisionCount; // Compteur de collisions avec le joueur

	sf::Vector2f direction;
	static bool isRandInitialized;
	double randomizeAngle();
	void setAngle(double angle);
public:
	Ball(int x, int y, int radius, float speed);
	~Ball();
	void move(float ellapsedTime);
	void draw(sf::RenderWindow& window);
	float getSpeed();
	void setSpeed(float newSpeed);
	void setPosition(sf::Vector2f newPosition);
	void setDirection(sf::Vector2f newDirection);
	sf::Vector2f getPosition();
	void manageCollisionWith(Player& player, sf::RenderWindow& window);
	void update(float deltaTime, Player& player, sf::RenderWindow& window);
	void manageCollisionWithBrick(Brick* brick);


};
