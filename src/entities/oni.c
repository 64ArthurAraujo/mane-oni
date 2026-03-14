#include "oni.h"
#include "raylib.h"
#include "entity.h"
#include "player.h"
#include <stdio.h>
#include <math.h>
#include "../graphics/sprite.h"

Entity oni =
    {
        .position = {550.0f, 200.0f},
        .speed = 1.4f,
        .width = 66,
        .height = 66,
};

AnimatedSprite oniSprite = {};

void OnLoad_Oni()
{
    oniSprite.texture = LoadTexture("graphics/oni.png");
    oniSprite.frameCount = 4;
    oniSprite.frameSpeed = 0.12f;
    oniSprite.frameWidth = 65;
    oniSprite.frameHeight = 128;
    oniSprite.direction = DIR_DOWN;
    oniSprite.currentFrame = 0;

    oniSprite.sourceRec = (Rectangle){0, 0, oniSprite.frameWidth, oniSprite.frameHeight};
}

void OnUpdate_Oni(Rectangle roomFloor, Rectangle obstacles[], int obs_count)
{
    Entity player = GetPlayer();
    Vector2 playerPos = player.position;

    Vector2 move = {0};

    bool reachedX = fabsf(playerPos.x - oni.position.x) < player.width * 1.2f;

    if (reachedX)
    {
        if (playerPos.y > oni.position.y)
        {
            move.y += oni.speed;
            oniSprite.direction = DIR_DOWN;
        }
        else
        {
            move.y -= oni.speed;
            oniSprite.direction = DIR_UP;
        }
    }
    else
    {
        if (playerPos.x > oni.position.x)
        {
            move.x += oni.speed;
            oniSprite.direction = DIR_RIGHT;
        }
        else if (playerPos.x < oni.position.x)
        {
            move.x -= oni.speed;
            oniSprite.direction = DIR_LEFT;
        }
    }

    bool isMoving = (move.x != 0 || move.y != 0);

    if (isMoving)
    {
        Vector2 newPos = {oni.position.x + move.x, oni.position.y + move.y};

        if (newPos.x < roomFloor.x)
            newPos.x = roomFloor.x;
        if (newPos.x + oni.width > roomFloor.x + roomFloor.width)
            newPos.x = roomFloor.x + roomFloor.width - oni.width;
        if (newPos.y < roomFloor.y)
            newPos.y = roomFloor.y;
        if (newPos.y + oni.height > roomFloor.y + roomFloor.height)
            newPos.y = roomFloor.y + roomFloor.height - oni.height;

        bool canMove = true;

        Rectangle oniRect = {newPos.x, newPos.y, oni.width, oni.height};

        for (int i = 0; i < obs_count; i++)
        {
            if (CheckCollisionRecs(oniRect, obstacles[i]))
            {
                canMove = false;
                break;
            }
        }

        if (canMove)
        {
            oni.position = newPos;

            oniSprite.frameTimer += GetFrameTime();

            if (oniSprite.frameTimer >= oniSprite.frameSpeed)
            {
                oniSprite.frameTimer = 0;
                oniSprite.currentFrame = (oniSprite.currentFrame + 1) % oniSprite.frameCount;
            }
        }
        else
        {
            oniSprite.currentFrame = 0;
        }
    }
    else
    {
        oniSprite.currentFrame = 0;
    }

    oniSprite.sourceRec.x = oniSprite.currentFrame * oniSprite.frameWidth;
    oniSprite.sourceRec.y = oniSprite.direction * oniSprite.frameHeight;
}

void OnDraw_Oni()
{
    DrawTextureRec(oniSprite.texture,
                   oniSprite.sourceRec,
                   (Vector2){oni.position.x, oni.position.y - (oni.height)},
                   WHITE);

    // Hitbox
    DrawRectangleLines((int)oni.position.x, (int)oni.position.y,
                       oni.width, oni.height, WHITE);
}

void OnUnload_Oni()
{
    UnloadTexture(oniSprite.texture);
}

Entity GetOni()
{
    return oni;
}