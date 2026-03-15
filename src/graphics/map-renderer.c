#include "map-renderer.h"
#include "tileset.h"
#include "map/parser.h"

void DrawTileMap(const TileMap *map,
                 const TileSet *tilesets,
                 int tileWidth,
                 int tileHeight,
                 Vector2 offset)
{
    for (int layer_pos = 0; layer_pos < map->layerCount; layer_pos++)
    {
        const Layer* layer = &map->layers[layer_pos];

        for (int y = 0; y < layer->height; y++)
        {
            for (int x = 0; x < layer->width; x++) 
            {
                int index = y * layer->width + x;
                int tileID = layer->data[index];

                if (tileID <= 0) continue;

                int tsIndex = -1;

                for (int t = map->mapTilesetCount - 1; t >= 0; t--)
                {
                    if (tileID >= map->mapTilesets[t].firstGid)
                    {
                        tsIndex = t;
                        break;
                    }
                } 

                if (tsIndex == -1) continue;

                int localID = tileID - map->mapTilesets[tsIndex].firstGid;

                Vector2 position = {
                    offset.x + x * (float)tileWidth,
                    offset.y + y * (float)tileHeight
                };

                DrawTile(tilesets[tsIndex], localID, position, WHITE);
            }
        }
    }
}