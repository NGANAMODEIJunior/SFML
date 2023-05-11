#include "Ball.h"
#include "Player.h"

Ball::Ball(int x, int y, int radius, float speed) : position(x, y), oldPosition(position), radius(radius), speed(speed)
{
	shape.setFillColor(sf::Color::White);
	shape.setRadius(radius);

	setRandomDirection();
}

void Ball::setRandomDirection()
{
	// Génère un angle aléatoire entre -30 et 30 degrés
	double angle = ((double)rand() / (double)RAND_MAX) * 60.0 - 30.0;
	setDirection(angle);
}

void Ball::setDirection(double angle)
{
	// Calcule les composantes x et y de la direction en fonction de l'angle
	direction.x = sin(angle);
	direction.y = -cos(angle);
}

void Ball::move(float elapsedTime)
{
	position += elapsedTime * speed * direction;
}

void Ball::draw(sf::RenderWindow& window)
{
	shape.setPosition(position);
	window.draw(shape);
}

void Ball::update(float deltaTime, Player& player, sf::RenderWindow& window)
{
	move(deltaTime);
	shape.setPosition(position);

	manageCollisionWithPlayer(player);
	manageCollisionWithScreenBounds(window);
}

void Ball::manageCollisionWithPlayer(Player& player)
{
	// Vérifie si la balle touche le joueur
	if (shape.getGlobalBounds().intersects(player.getShape().getGlobalBounds()))
	{
		// Calcule la position relative de la balle par rapport au joueur
		double relativeIntersectX = position.x + radius - player.getPosition().x - player.getSize().x / 2.0;

		// Normalise la position relative de la balle
		double normalizedRelativeIntersectionX = relativeIntersectX / (player.getSize().x / 2.0);

		// Calcule l'angle de rebond de la balle
		double angle = normalizedRelativeIntersectionX * MAX_ANGLE;

		// Change la direction de la balle en fonction de l'angle de rebond
		setDirection(angle);

		// Déplace la balle en dehors du joueur
		position.y = player.getPosition().y - 2 * radius - 0.1f;
		direction.y = -std::abs(direction.y);
	}
}

void Ball::manageCollisionWithScreenBounds(sf::RenderWindow& window)
{
	// Vérifie si la balle touche le bord supérieur de l'écran
	if (position.y <= 0)
	{
		direction.y = std::abs(direction.y); // Inverse la direction sur l'axe y
	}

	// Vérifie si la balle touche le bord inférieur de l'écran
	if (position.y >= window.getSize().y - 2 * radius)
	{
		direction.y = -std::abs(direction.y); // Inverse la direction sur l'axe y
	}

	// Vérifie si la balle touche le bord gauche de l'écran
	if (position.x <= 0)
	{
		direction.x = std::abs(direction.x); // Inverse la direction sur l'axe x
	}

	// Vérifie si la balle touche le bord droit de l'écran
	if (position.x >= window.getSize().x - 2 * radius)
	{
		direction.x = -std::abs(direction.x); // Inverse la direction sur l'axe x
	}
}
