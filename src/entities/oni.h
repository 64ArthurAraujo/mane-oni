#pragma once
#include "raylib.h"
#include "entity.h"

void OnLoad_Oni();
void OnUpdate_Oni(Rectangle roomFloor);
void OnDraw_Oni();
void OnUnload_Oni();

Entity GetOni();