#include "parser.h"
#include "raylib.h"
#include "resource_dir.h"
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <stdlib.h>
#include <string.h>
#include "util/string.h"

bool get_field_bool(lua_State *L, char *field);
const char* get_field_string(lua_State *L, char *field);
int get_field_int(lua_State *L, char *field);

TileMap ParseMap(char* path)
{
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    char *luaText = LoadFileText(path);

    if (!luaText)
    {
        perror("Failed to load the map");
        CloseWindow();
    }

    if (luaL_dostring(L, luaText) != LUA_OK)
    {
        printf("Lua error: %s\n", lua_tostring(L, -1));
        CloseWindow();
    }

    TileMap map = {0};

    int width = get_field_int(L, "width");
    int height = get_field_int(L, "height");

    lua_getfield(L, -1, "tilesets");
    int tileset_count = lua_rawlen(L, -1);

    MapTileset *mapTilesets = malloc(sizeof(MapTileset) * tileset_count);

    for (int i = 1; i <= tileset_count; i++)
    {
        lua_rawgeti(L, -1, i);
        
        const char* name = get_field_string(L, "name"); 
        int firstgid = get_field_int(L, "firstgid");

        // the name is considered to be the same as images saved in "graphics/tilesets"
        mapTilesets[i-1].name = strdup(name);
        mapTilesets[i-1].firstGid = firstgid;

        lua_pop(L, 1);
    }

    lua_pop(L, 1);

    lua_getfield(L, -1, "layers"); // push layers table
    int layer_count = lua_rawlen(L, -1);

    Layer *layers = malloc(sizeof(Layer) * layer_count);

    // Lua start indexing at 1 instead of 0
    for (int i = 1; i <= layer_count; i++)
    {
        lua_rawgeti(L, -1, i);

        int id = get_field_int(L, "id");
        const char *name = get_field_string(L, "name");
        bool visible = get_field_bool(L, "visible");

        // parse data
        lua_getfield(L, -1, "data");
        int data_count = lua_rawlen(L, -1);

        int *data = malloc (sizeof(int) * data_count);

        for (int j = 1; j <= data_count; j++)
        {
            lua_rawgeti(L, -1, j);
            data[j-1] = lua_tointeger(L, -1);
            lua_pop(L, 1);
        }

        layers[i-1].id = id;
        layers[i-1].name = strdup(name);
        // consider all layers to match the maps proportions
        layers[i-1].width = width;
        layers[i-1].height = height;
        layers[i-1].data = data;
        layers[i-1].visible = visible;

        lua_pop(L, 1);
        lua_pop(L, 1);
    }

    lua_pop(L, 1);

    lua_close(L);
    UnloadFileText(luaText);

    map.height = height;
    map.width = width;

    map.mapTilesetCount = tileset_count;
    map.mapTilesets = mapTilesets;

    map.layerCount = layer_count;
    map.layers = layers;

    return map;
}

bool get_field_bool(lua_State *L, char *field)
{
    lua_getfield(L, -1, field);
    bool value = lua_toboolean(L, -1);
    lua_pop(L, 1); 

    return value;
}

const char* get_field_string(lua_State *L, char *field)
{
    lua_getfield(L, -1, field);
    const char* value = lua_tostring(L, -1);
    lua_pop(L, 1); 

    return value;
}

int get_field_int(lua_State *L, char *field)
{
    lua_getfield(L, -1, field);
    int value = lua_tointeger(L, -1);
    lua_pop(L, 1); 

    return value;
}

void UnloadMap(TileMap *map)
{
    for (int i = 0; i < map->mapTilesetCount; i++)
        free(map->mapTilesets[i].name);

    free(map->mapTilesets);

    for (int i = 0; i < map->layerCount; i++)
    {
        free(map->layers[i].name);
        free(map->layers[i].data);
    }

    free(map->layers);
}