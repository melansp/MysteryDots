#ifndef	_ENTITY_H_
#define _ENTITY_H_

#include <memory>
#include <SFML/Graphics.hpp>

struct Entity
{
public:
	typedef std::shared_ptr<Entity> Ptr;

	Entity(const float radius = 7.5f);
	Entity(const Entity&) = delete;
	Entity& operator=(const Entity&) = delete;
	sf::CircleShape shape;
	sf::Vector2f velocity;
	float speedMultiplier;
};


#endif