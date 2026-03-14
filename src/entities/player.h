#pragma once
#include "entity.h"

void OnLoad_Player();
void OnUpdate_Player(Rectangle roomFloor);
void OnDraw_Player();
void OnUnload_Player();

Entity GetPlayer();