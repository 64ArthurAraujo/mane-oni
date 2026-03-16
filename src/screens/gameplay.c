#include "screens.h"
#include "raylib.h"
#include "entities/entity.h"
#include "entities/player.h"
#include "entities/oni.h"
#include "graphics/tileset.h"
#include "graphics/map-renderer.h"
#include "map/parser.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

static Music wind;

TileMap currentMap = {0};
static TileSet *mapTilests = NULL;
int tileSize = 32;
int collisionLayerIndex = 0;
Vector2 globalOffset = {0,0};

void OnLoad_Gameplay(void)
{
    wind = LoadMusicStream("sounds/wind.ogg");

    currentMap = ParseMap("maps/genkan.lua");
    mapTilests = (TileSet *)malloc(currentMap.mapTilesetCount * sizeof(TileSet));

    // initialize tilesets
    for (int i = 0; i < currentMap.mapTilesetCount; i++)
    {
        char path[256];
        snprintf(path, sizeof(path), "graphics/tilesets/%s.png", currentMap.mapTilesets[i].name);
        mapTilests[i] = LoadTileSet(path, tileSize, tileSize);
    }

    OnLoad_Player();

    PlayMusicStream(wind);
    SetMusicVolume(wind, 0.6f);
}

void OnUpdate_Gameplay(void)
{
    OnUpdate_Player();
    UpdateMusicStream(wind);
}

void OnDraw_Gameplay(void)
{
    ClearBackground(BLACK);

    float mapPixelWidth = currentMap.width * tileSize;
    float mapPixelHeight = currentMap.height * tileSize;

    globalOffset = (Vector2){
        (GetScreenWidth() - mapPixelWidth) * 0.5f,
        (GetScreenHeight() - mapPixelHeight) * 0.5f
    };

    DrawTileMap(&currentMap, mapTilests, tileSize, tileSize, globalOffset);
    OnDraw_Player();
}

void OnUnload_Gameplay(void)
{
    OnUnload_Player();

    for (int i = 0; i < currentMap.mapTilesetCount; i++)
        UnloadTileSet(&mapTilests[i]);

    free(mapTilests);
    mapTilests = NULL;

    UnloadMap(&currentMap);
    UnloadMusicStream(wind);
}