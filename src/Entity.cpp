#include "Entity.h"

Entity::Entity(const float radius)
	:shape(radius),
	speedMultiplier(1)
{
	shape.setOrigin(radius, radius);
}
