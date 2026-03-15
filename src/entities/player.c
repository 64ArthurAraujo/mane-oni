#include "raylib.h"
#include "player.h"
#include "oni.h"
#include "entity.h"
#include "graphics/sprite.h"
#include "util/tilemap-utils.h"

extern TileMap currentMap;
extern int tileSize;
extern int collisionLayerIndex;
extern Vector2 globalOffset;

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

void OnUpdate_Player()
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

        Rectangle nextHitboxPos = {newPos.x, newPos.y, player.width, player.height};

        Vector2 corners[4] = {
            {nextHitboxPos.x, nextHitboxPos.y},
            {nextHitboxPos.x + nextHitboxPos.width, nextHitboxPos.y},
            {nextHitboxPos.x, nextHitboxPos.y + nextHitboxPos.height},
            {nextHitboxPos.x + nextHitboxPos.width, nextHitboxPos.y + nextHitboxPos.height}};

        bool canMove = true;

        for (int i = 0; i < 4; i++)
        {
            if (!isWalkableAt(&currentMap, corners[i], collisionLayerIndex, tileSize))
            {
                canMove = false;
                break;
            }
        }

        if (canMove)
        {
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
    Vector2 hitboxPos = {
        player.position.x + globalOffset.x,
        player.position.y + globalOffset.y};

    Vector2 spritePos = {
        hitboxPos.x,
        hitboxPos.y - (player.height / 2)};

    DrawTextureRec(playerSprite.texture,
                   playerSprite.sourceRec,
                   spritePos,
                   WHITE);

    DrawRectangleLines((int)hitboxPos.x, (int)hitboxPos.y,
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