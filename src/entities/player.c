#include "raylib.h"
#include "player.h"
#include "oni.h"
#include "entity.h"
#include "../graphics/sprite.h"

Entity player =
    {
        .position = {300.f, 300.f},
        .speed = {2.5f},
        .width = 32,
        .height = 32,
};

AnimatedSprite playerSprite = {};

void OnLoad_Player()
{
    playerSprite.texture = LoadTexture("graphics/hiroshi.png");
    playerSprite.frameCount = 4;
    playerSprite.frameSpeed = 0.12f;
    playerSprite.frameWidth = 32;
    playerSprite.frameHeight = 48;
    playerSprite.direction = DIR_DOWN;
    playerSprite.currentFrame = 0;

    playerSprite.sourceRec = (Rectangle){0, 0, playerSprite.frameWidth, playerSprite.frameHeight};
}

void OnUpdate_Player(Rectangle roomFloor)
{
    Vector2 move = {0};

    if (IsKeyDown(KEY_D))
    {
        move.x += player.speed;
        playerSprite.direction = DIR_RIGHT;
    }
    else if (IsKeyDown(KEY_A))
    {
        move.x -= player.speed;
        playerSprite.direction = DIR_LEFT;
    }
    else if (IsKeyDown(KEY_S))
    {
        move.y += player.speed;
        playerSprite.direction = DIR_DOWN;
    }
    else if (IsKeyDown(KEY_W))
    {
        move.y -= player.speed;
        playerSprite.direction = DIR_UP;
    }

    bool isMoving = (move.x != 0 || move.y != 0);

    if (isMoving)
    {
        Vector2 newPos = {player.position.x + move.x, player.position.y + move.y};

        if (newPos.x < roomFloor.x)
            newPos.x = roomFloor.x;
        if (newPos.x + player.width > roomFloor.x + roomFloor.width)
            newPos.x = roomFloor.x + roomFloor.width - player.width;
        if (newPos.y < roomFloor.y)
            newPos.y = roomFloor.y;
        if (newPos.y + player.height > roomFloor.y + roomFloor.height)
            newPos.y = roomFloor.y + roomFloor.height - player.height;

        player.position = newPos;

        playerSprite.frameTimer += GetFrameTime();

        if (playerSprite.frameTimer >= playerSprite.frameSpeed)
        {
            playerSprite.frameTimer = 0;
            playerSprite.currentFrame = (playerSprite.currentFrame + 1) % playerSprite.frameCount;
        }
    }
    else
    {
        playerSprite.currentFrame = 0;
    }

    playerSprite.sourceRec.x = playerSprite.currentFrame * playerSprite.frameWidth;
    playerSprite.sourceRec.y = playerSprite.direction * playerSprite.frameHeight;
}

void OnDraw_Player()
{
    DrawTextureRec(playerSprite.texture,
                   playerSprite.sourceRec,
                   (Vector2){player.position.x, player.position.y - (player.height / 2)},
                   WHITE);

    // Hitbox              
    DrawRectangleLines((int)player.position.x, (int)player.position.y,
                       player.width, player.height, WHITE);
}

void OnUnload_Player()
{
    UnloadTexture(playerSprite.texture);
}

Entity GetPlayer() 
{
    return player;
}