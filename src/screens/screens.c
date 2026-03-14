#include "screens.h"

Screen currentScreen = NONE;

void ChangeScreen(Screen newScreen)
{
    if (newScreen == currentScreen) return;

    switch (currentScreen) 
    {
        case MENU: OnUnload_Menu(); break;
        case GAMEPLAY: OnUnload_Gameplay(); break;
    }

    currentScreen = newScreen;

    switch (currentScreen)
    {
        case MENU: OnLoad_Menu(); break;
        case GAMEPLAY: OnLoad_Gameplay(); break;
    }
}