#include "screens.h"
#include "raylib.h"
#include "entities/entity.h"
#include "entities/player.h"
#include "entities/oni.h"

static Music horror;
static Texture2D gameOverImage;

static Rectangle roomFloor = {0, 0, 520, 520};

static bool gameOver = false;
static bool win = false;

Rectangle obstacles[] = {
    {180, 180, 120, 30},
    {500, 380, 80, 100},
    {250, 450, 200, 30}
};

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

    // Calculate the middle of the screen for the map
    int middleX = (GetScreenWidth() / 2) - (roomFloor.width / 2);
    int middleY = (GetScreenHeight() / 2) - (roomFloor.height / 2);

    roomFloor.x = middleX;
    roomFloor.y = middleY;
}

void OnUpdate_Gameplay(void)
{
    if (!gameOver && !win)
    {
        OnUpdate_Player(roomFloor, obstacles, 3);
        OnUpdate_Oni(roomFloor, obstacles, 3);

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
    ClearBackground(BLACK);
    DrawRectangleRec(roomFloor, DARKBROWN);

    for (int i = 0; i < 3; i++)
    {
        DrawRectangleRec(obstacles[i], BROWN);
        DrawRectangleLinesEx(obstacles[i], 4, DARKBROWN);
    }

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