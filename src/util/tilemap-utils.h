#pragma once 
#include "map/parser.h"
#include "raylib.h"

int GetTileIDAt(const TileMap* map, Vector2 worldPos, int layerIndex, int tileSize);

bool isWalkableAt(const TileMap* map, Vector2 worldPos, int collisionLayerIndex, int tileSize);