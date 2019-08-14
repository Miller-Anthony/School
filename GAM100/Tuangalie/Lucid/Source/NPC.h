//---------------------------------------------------------
// file:	InputManager.h
// author:	Justin Chambers
// brief:	Custom input functions
// Course: GAM100F18
// Copyright © 2018 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once
#include "PlayerManager.h"
//---------------------------------------------------------
// Private Consts:
//---------------------------------------------------------

//---------------------------------------------------------
// Private Structures:
//---------------------------------------------------------

//---------------------------------------------------------
// Public Variables:
//---------------------------------------------------------

//---------------------------------------------------------
// Public Functions:
//---------------------------------------------------------
void npc_updown_movement(int* y, int offset, int max, int min, bool *hitmax);
void npc_leftright_movement(int* x, int offset, int max, int min, bool *hitmax);
void rotateTriangle(vec2_t *p1, vec2_t *p2, vec2_t *p3, float rotation);
int checkDetection(vec2_t p1, vec2_t p2, vec2_t p3, PLAYER player);


