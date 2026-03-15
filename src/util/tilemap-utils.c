#include "map/parser.h"
#include "raylib.h"
#include "stddef.h"


int GetTileIDAt(const TileMap* map, Vector2 worldPos, int layerIndex, int tileSize)
{
    if (map->height == 0 || map->width == 0) return 0;

    int tileX = (int)(worldPos.x / tileSize);
    int tileY = (int)(worldPos.y / tileSize);

    if (tileX < 0 || tileX >= map->width || tileY < 0 || tileY >= map->height)
    {
        return 0;
    }

    const Layer *layer = &map->layers[layerIndex];
    size_t index = (size_t)tileY * layer->width + tileX;

    return layer->data[index];
}

bool isWalkableAt(const TileMap* map, Vector2 worldPos, int collisionLayerIndex, int tileSize)
{
    int tileID = GetTileIDAt(map, worldPos, collisionLayerIndex, tileSize);
    return tileID != 0;
}