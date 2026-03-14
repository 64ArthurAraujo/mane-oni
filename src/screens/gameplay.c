#include "screens.h"
#include "raylib.h"
#include "entities/entity.h"
#include "entities/player.h"
#include "entities/oni.h"

static Music horror;
static Texture2D gameOverImage;

static Rectangle roomFloor = {40, 40, 600, 520};

static bool gameOver = false;
static bool win = false;

void OnLoad_Gameplay(void)
{
    horror = LoadMusicStream("sounds/horor.ogg");
    gameOverImage = LoadTexture("graphics/gameover.png");

    gameOver = false;
    win = false;

    OnLoad_Player();
    OnLoad_Oni();

    PlayMusicStream(horror);
    SetMusicVolume(horror, 0.6f);
}

void OnUpdate_Gameplay(void)
{
    if (!gameOver && !win)
    {
        OnUpdate_Player(roomFloor);
        OnUpdate_Oni(roomFloor);

        if (CheckCollisionRecs(GetEntityHitbox(GetPlayer()), GetEntityHitbox(GetOni())))
        {
            gameOver = true;
            StopMusicStream(horror);
        }
    }

    UpdateMusicStream(horror);
}

void OnDraw_Gameplay(void)
{
    DrawRectangleRec(roomFloor, DARKBROWN);

    OnDraw_Player();
    OnDraw_Oni();

    if (gameOver)
    {
        DrawTexturePro(gameOverImage,
                       (Rectangle){0, 0, (float)gameOverImage.width, (float)gameOverImage.height}, // source = full image
                       (Rectangle){0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()},       // dest   = full window
                       (Vector2){0, 0},                                                            // origin
                       0.0f,                                                                       // rotation
                       WHITE);
    }
}

void OnUnload_Gameplay(void)
{
    UnloadMusicStream(horror);
    OnUnload_Player();
    OnUnload_Oni();
}