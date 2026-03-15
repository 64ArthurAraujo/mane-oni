#pragma once

typedef struct
{
    int width;
    int height;
    int id;
    char *name;
    int *data;
} Layer;

typedef struct
{
    char *name;
    int firstGid;
} MapTileset;

typedef struct
{
    int width;
    int height;

    int mapTilesetCount;
    MapTileset *mapTilesets;

    int layerCount;
    Layer *layers;
} TileMap;

TileMap ParseMap(char *path);

void UnloadMap(TileMap *map);