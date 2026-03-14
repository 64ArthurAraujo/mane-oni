#pragma once
#include "raylib.h"

typedef enum { DIR_DOWN = 0, DIR_LEFT, DIR_RIGHT, DIR_UP } Direction;

typedef struct {
    Texture2D texture;
    Rectangle sourceRec;
    int currentFrame;
    int frameCount;     
    float frameTimer;
    float frameSpeed;      
    Direction direction;
    int frameWidth;
    int frameHeight;
} AnimatedSprite;