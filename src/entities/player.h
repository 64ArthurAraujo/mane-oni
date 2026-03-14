#pragma once
#include "entity.h"

void OnLoad_Player();
void OnUpdate_Player(Rectangle roomFloor, Rectangle obstacles[], int obs_count);
void OnDraw_Player();
void OnUnload_Player();

Entity GetPlayer();