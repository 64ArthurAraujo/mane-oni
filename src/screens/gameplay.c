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

static Music horror;

static TileMap currentMap = {0};
static TileSet* mapTilests = NULL;
static int tileSize = 32;

void OnLoad_Gameplay(void)
{
    horror = LoadMusicStream("sounds/horor.ogg");

    currentMap = ParseMap("maps/genkan.lua");
    mapTilests = (TileSet*) malloc(currentMap.mapTilesetCount * sizeof(TileSet));

    // initialize tilesets
    for (int i = 0; i < currentMap.mapTilesetCount; i++)
    {
        char path[256];
        snprintf(path, sizeof(path), "graphics/tilesets/%s.png", currentMap.mapTilesets[i].name);
        mapTilests[i] = LoadTileSet(path, tileSize, tileSize);
    }

    PlayMusicStream(horror);
    SetMusicVolume(horror, 0.4f);
}

void OnUpdate_Gameplay(void)
{
    UpdateMusicStream(horror);
}

void OnDraw_Gameplay(void)
{
    ClearBackground(BLACK);
    DrawTileMap(&currentMap, mapTilests, tileSize, tileSize, (Vector2){0,0});
}

void OnUnload_Gameplay(void)
{
    for (int i = 0; i < currentMap.mapTilesetCount; i++)
        UnloadTileSet(&mapTilests[i]);
    
    free(mapTilests);
    mapTilests = NULL;

    UnloadMap(&currentMap);
    UnloadMusicStream(horror);
}