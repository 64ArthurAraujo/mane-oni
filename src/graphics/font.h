#pragma once
#include "raylib.h"

extern Font mainFont;

/**
 * Draws text using the mainFont
 */
void DrawTextC(const char *text, Vector2 position, float fontSize, float spacing, Color tint);

void LoadFonts();
void UnloadFonts();

static void AddCodepointRange(Font *font, const char *fontPath, int start, int stop);