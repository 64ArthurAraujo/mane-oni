#include "raylib.h"
#include "resource_dir.h"
#include "entities/entity.h"
#include "entities/player.h"
#include "entities/oni.h"
#include "screens/screens.h"
#include "graphics/tileset.h"
#include "graphics/font.h"
#include "map/parser.h"
#include <math.h>


int main()
{
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	InitWindow(800, 600, "真似鬼");
	InitAudioDevice();

	SetTargetFPS(60);

	SearchAndSetResourceDir("resources");

	LoadFonts();
	ParseMap();

	ChangeScreen(MENU);

	while (!WindowShouldClose())
	{
		/* ON UPDATE */
		switch (currentScreen)
		{
			case MENU: OnUpdate_Menu(); break;
			case GAMEPLAY: OnUpdate_Gameplay(); break;
		}

		/* ON DRAW */
		BeginDrawing();
		{
			switch (currentScreen)
			{
				case MENU: OnDraw_Menu(); break;
				case GAMEPLAY: OnDraw_Gameplay(); break;
			}
		}
		EndDrawing();
	}

	ChangeScreen(NONE);
	UnloadFonts();
	CloseAudioDevice();
	CloseWindow();

	return 0;
}

