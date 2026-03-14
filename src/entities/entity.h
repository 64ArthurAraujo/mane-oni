#pragma once
#include "raylib.h"

typedef struct
{
	Vector2 position;
	float speed;
	int width;
	int height;
} Entity;

Rectangle GetEntityHitbox(Entity entity);