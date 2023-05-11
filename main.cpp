#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Player.h"
#include "Brick.h"
#include <memory>

double mapValue(double x, double a, double b, double c, double d)
{
	double y = (x - a) / (b - a) * (d - c) + c;
	return y;
}

int main(int argc, char** argv)
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "ma magnifique fenetre");

	Ball ball(200, 250, 10, 400);
	Player player(500, 100, 10);

	int brickInitial = 100; // Nombre de briques dans le tableau
	std::deque<std::unique_ptr<Brick>> bricks;

	int brickWidth = 80;
	int brickHeight = 35;

	for (int i = 1; i < 9; i++)
	{
		for (int j = 1; j < 8; j++)
		{
			int x = i * brickWidth;
			int y = j * brickHeight;
			bricks.push_back(std::make_unique<Brick>(x, y, brickWidth, brickHeight, 3));
		}
	}

	sf::RectangleShape rdr2;
	rdr2.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));

	sf::Clock clock;
	sf::Vector3f xFactor(10, 20, 30);
	float ellapsedTime = 0;

	while (window.isOpen())
	{
		ellapsedTime = clock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		ball.move(ellapsedTime);
		player.update();

		ball.update(ellapsedTime, player, window);

		window.clear();

		for (int i = 0; i < window.getSize().y; i++)
		{
			double mappedValue = mapValue(i, 0, window.getSize().y, 0, 255);
			rdr2.setFillColor(sf::Color(mappedValue, 0, 0));
			rdr2.setPosition(0, i);
			window.draw(rdr2);
		}

		ball.draw(window);
		player.draw(window);

		for (auto it = bricks.begin(); it != bricks.end();)
		{
			if ((*it)->isAlive())
			{
				(*it)->draw(window);
				ball.manageCollisionWithBrick(*it);
				++it;
			}
			else
			{
				it = bricks.erase(it);
			}
		}

		window.display();
	}

	return 0;
}
