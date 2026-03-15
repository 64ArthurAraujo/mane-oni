#include "parser.h"
#include "raylib.h"
#include "resource_dir.h"
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

void ParseMap()
{
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    char *luaText = LoadFileText("maps/genkan.lua");

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

    lua_getfield(L, -1, "width");
    int width = lua_tointeger(L, -1);
    lua_pop(L, 1);

    lua_getfield(L, -1, "height");
    int height = lua_tointeger(L, -1);
    lua_pop(L, 1);

    map.height = height;
    map.width = width;
}