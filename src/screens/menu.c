#include "screens.h"
#include "raylib.h"
#include "graphics/font.h"
#include <stdio.h>

typedef struct
{
    Sound select;
    Sound accept;
} MenuAudio;

typedef enum
{
    NEW_GAME = 1,
    CONTINUE,
    SHUTDOWN
} SelectedButton;

static Rectangle newGameButton = {0};
static Rectangle continueButton = {0};
static Rectangle shutdownButton = {0};

static SelectedButton selected = NEW_GAME;
static Rectangle selectedButtonRec = {0};

MenuAudio audio = {0};

void selectedDec();
void selectedInc();

void OnLoad_Menu(void)
{
    audio.select = LoadSound("sounds/select.ogg");
    audio.accept = LoadSound("sounds/accept.ogg");

    newGameButton = (Rectangle){(GetScreenWidth() / 2) - 120, GetScreenHeight() / 2 - 60, 240, 40};
    continueButton = (Rectangle){(GetScreenWidth() / 2) - 120, GetScreenHeight() / 2, 240, 40};
    shutdownButton = (Rectangle){(GetScreenWidth() / 2) - 120, GetScreenHeight() / 2 + 60, 240, 40};
}

void OnUpdate_Menu(void)
{
    if (IsKeyPressed(KEY_UP))
    {
        selectedInc();
        PlaySound(audio.select);
    }
    else if (IsKeyPressed(KEY_DOWN))
    {
        selectedDec();
        PlaySound(audio.select);
    }

    switch (selected)
    {
    case NEW_GAME:
        selectedButtonRec = newGameButton;
        break;
    case CONTINUE:
        selectedButtonRec = continueButton;
        break;
    case SHUTDOWN:
        selectedButtonRec = shutdownButton;
        break;
    }

    if (IsKeyPressed(KEY_ENTER))
    {
        switch (selected)
        {
        case NEW_GAME:
            PlaySound(audio.accept);
            ChangeScreen(GAMEPLAY);
            break;
        case CONTINUE:
            
            break;
        case SHUTDOWN:
            PlaySound(audio.accept);
            CloseWindow();
            break;
        }
    }
}

void OnDraw_Menu(void)
{
    ClearBackground(BLACK);

    DrawTextC(">", (Vector2){selectedButtonRec.x - 32, selectedButtonRec.y}, 32, 2, WHITE);

    DrawTextC("ニュウーゲーム", (Vector2){newGameButton.x, newGameButton.y}, 32, 2, WHITE);
    DrawTextC("つずく", (Vector2){continueButton.x, continueButton.y}, 32, 2, GRAY);
    DrawTextC("シャットダウン", (Vector2){shutdownButton.x, shutdownButton.y}, 32, 2, WHITE);
}

void OnUnload_Menu(void)
{
    UnloadSound(audio.select);
}

void selectedDec()
{
    selected = selected + 1;
    if (selected > 3)
        selected = 1;
}

void selectedInc()
{
    selected = selected - 1;
    if (selected == 0)
        selected = 3;
}