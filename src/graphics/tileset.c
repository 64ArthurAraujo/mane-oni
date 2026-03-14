#include "tileset.h"

TileSet LoadTileSet(const char *fileName, int tileWidth, int tileHeight)
{
    TileSet ts = {0};

    ts.texture = LoadTexture(fileName);
    ts.tileHeight = tileHeight;
    ts.tileWidth = tileWidth;
    ts.columns = ts.texture.width / tileWidth;

    return ts;
}

void UnloadTileSet(TileSet *tileset)
{
    UnloadTexture(tileset->texture);
}

Rectangle GetTileSourceRect(TileSet tileset, int tileID)
{
    int col = tileID % tileset.columns;
    int row = tileID / tileset.columns;

    return (Rectangle){col * tileset.tileWidth, row * tileset.tileHeight, tileset.tileWidth, tileset.tileHeight};
}

void DrawTile(TileSet tileset, int tileID, Vector2 position, Color tint)
{
    Rectangle src = GetTileSourceRect(tileset, tileID);
    DrawTextureRec(tileset.texture, src, position, tint);
}