#pragma once
#include "tileset.h"
#include "map/parser.h"

void DrawTileMap(
    const TileMap *map,
    const TileSet *tilesets,
    int tileWidth,
    int tileHeight,
    Vector2 offset);