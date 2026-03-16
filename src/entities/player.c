#include "raylib.h"
#include "player.h"
#include "oni.h"
#include "entity.h"
#include "graphics/sprite.h"
#include "util/tilemap-utils.h"
#include "raymath.h"
#include <math.h>

extern TileMap currentMap;
extern int tileSize;
extern int collisionLayerIndex;
extern Vector2 globalOffset;

Entity player = {
    .position = {0, 0},
    .speed = {2.7f},
    .width = 32,
    .height = 32,
};

AnimatedSprite playerSprite = {};

bool playerMoving = false;
Vector2 targetPos = {0};

float SnapToTile(float value);
Vector2 SnapVector2ToTile(Vector2 v);
bool CanMoveTo(Vector2 newPos);

void OnLoad_Player()
{
    player.position = SnapVector2ToTile((Vector2){300.f, 300.f});

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
    float moveSpeed = 120.0f * GetFrameTime();

    if (!playerMoving)
    {
        Vector2 move = {0};

        if (IsKeyDown(KEY_D))
        {
            move.x = tileSize;
            playerSprite.direction = DIR_RIGHT;
        }
        else if (IsKeyDown(KEY_A))
        {
            move.x = -tileSize;
            playerSprite.direction = DIR_LEFT;
        }
        else if (IsKeyDown(KEY_S))
        {
            move.y = tileSize;
            playerSprite.direction = DIR_DOWN;
        }
        else if (IsKeyDown(KEY_W))
        {
            move.y = -tileSize;
            playerSprite.direction = DIR_UP;
        }

        if (move.x != 0 || move.y != 0)
        {
            Vector2 newPos = {
                player.position.x + move.x,
                player.position.y + move.y};

            if (CanMoveTo(newPos))
            {
                targetPos = newPos;
                playerMoving = true;
            }
        }
    }

    if (playerMoving)
    {
        Vector2 dir = Vector2Subtract(targetPos, player.position);
        float dist = Vector2Length(dir);

        if (dist <= moveSpeed)
        {
            player.position = targetPos;
            playerMoving = false;
        }
        else
        {
            dir = Vector2Normalize(dir);
            player.position.x += dir.x * moveSpeed;
            player.position.y += dir.y * moveSpeed;
        }

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
    Vector2 hitboxPos = {
        player.position.x + globalOffset.x,
        player.position.y + globalOffset.y};

    Vector2 spritePos = {
        hitboxPos.x,
        hitboxPos.y - (player.height / 2)};

    DrawTextureRec(
        playerSprite.texture,
        playerSprite.sourceRec,
        spritePos,
        WHITE);

    DrawRectangleLines(
        (int)hitboxPos.x,
        (int)hitboxPos.y,
        player.width,
        player.height,
        WHITE);
}

void OnUnload_Player()
{
    UnloadTexture(playerSprite.texture);
}

Entity GetPlayer()
{
    return player;
}

bool CanMoveTo(Vector2 newPos)
{
    float left = newPos.x;
    float right = newPos.x + player.width - 1;
    float top = newPos.y;
    float bottom = newPos.y + player.height - 1;

    if (!isWalkableAt(&currentMap, (Vector2){left, top}, collisionLayerIndex, tileSize))
        return false;

    if (!isWalkableAt(&currentMap, (Vector2){right, top}, collisionLayerIndex, tileSize))
        return false;

    if (!isWalkableAt(&currentMap, (Vector2){left, bottom}, collisionLayerIndex, tileSize))
        return false;

    if (!isWalkableAt(&currentMap, (Vector2){right, bottom}, collisionLayerIndex, tileSize))
        return false;

    return true;
}

float SnapToTile(float value)
{
    return ((int)(value / tileSize)) * tileSize;
}

Vector2 SnapVector2ToTile(Vector2 v)
{
    return (Vector2){
        SnapToTile(v.x),
        SnapToTile(v.y)};
}