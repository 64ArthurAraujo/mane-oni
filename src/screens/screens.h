#pragma once
#include "raylib.h"

typedef enum
{
    NONE = -1,
    MENU = 0,
    GAMEPLAY,
} Screen;

extern Screen currentScreen;

void ChangeScreen(Screen newScreen);

// Menu
void OnLoad_Menu(void);
void OnUpdate_Menu(void);
void OnDraw_Menu(void);
void OnUnload_Menu(void);

// Gameplay
void OnLoad_Gameplay(void);
void OnUpdate_Gameplay(void);
void OnDraw_Gameplay(void);
void OnUnload_Gameplay(void);