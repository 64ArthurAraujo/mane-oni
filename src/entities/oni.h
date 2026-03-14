#pragma once
#include "raylib.h"
#include "entity.h"

void OnLoad_Oni();
void OnUpdate_Oni(Rectangle roomFloor, Rectangle obstacles[], int obs_count);
void OnDraw_Oni();
void OnUnload_Oni();

Entity GetOni();