#pragma once
#include "raylib.h"

typedef struct TileSet {
    Texture2D texture;
    int tileWidth;
    int tileHeight;
    int columns;
} TileSet;

TileSet LoadTileSet(const char* fileName, int tileWidth, int tileHeight);

void UnloadTileSet(TileSet* tileset);

Rectangle GetTileSourceRect(TileSet tileset, int tileID);

void DrawTile(TileSet tileset, int tileID, Vector2 position, Color tint);