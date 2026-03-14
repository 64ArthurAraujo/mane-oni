#include "entity.h"
#include "raylib.h"

Rectangle GetEntityHitbox(Entity entity)
{
	Rectangle hitbox = {entity.position.x, entity.position.y,
						entity.width, entity.height};
	return hitbox;
}