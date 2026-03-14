#include "font.h"
#include <stdlib.h> 

Font mainFont;

void LoadFonts() 
{
    // TODO: This is very slow as it opens the font 4 times, look for a way to open only one
    mainFont = LoadFont("fonts/ms_gothic.ttf");

    // Support japanese characters
    AddCodepointRange(&mainFont, "fonts/ms_gothic.ttf", 0x4e00, 0x9fff); // Kanji
    AddCodepointRange(&mainFont, "fonts/ms_gothic.ttf", 0x3040, 0x309f); // Hiragana
    AddCodepointRange(&mainFont, "fonts/ms_gothic.ttf", 0x30A0, 0x30ff); // Katakana
}

void UnloadFonts()
{
    UnloadFont(mainFont);
}

void DrawTextC(const char *text, Vector2 position, float fontSize, float spacing, Color tint) 
{
    DrawTextEx(mainFont, text, position, fontSize, spacing, tint);
}

static void AddCodepointRange(Font *font, const char *fontPath, int start, int stop)
{
    int rangeSize = stop - start + 1;
    int currentRangeSize = font->glyphCount;

    // TODO: Load glyphs from provided vector font (if available),
    // add them to existing font, regenerating font image and texture

    int updatedCodepointCount = currentRangeSize + rangeSize;
    int *updatedCodepoints = (int *)RL_CALLOC(updatedCodepointCount, sizeof(int));

    // Get current codepoint list
    for (int i = 0; i < currentRangeSize; i++)
        updatedCodepoints[i] = font->glyphs[i].value;

    // Add new codepoints to list (provided range)
    for (int i = currentRangeSize; i < updatedCodepointCount; i++)
        updatedCodepoints[i] = start + (i - currentRangeSize);

    UnloadFont(*font);
    *font = LoadFontEx(fontPath, 32, updatedCodepoints, updatedCodepointCount);
    RL_FREE(updatedCodepoints);
}