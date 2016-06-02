#include "Utility.h"

float distance(const sf::Vector2f& a, const sf::Vector2f& b)
{
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}