//------------------------------------------------------------------------------
//
// File Name:	WeaponShop.c
// Author(s):	Anthony Miller
// Project:		Knightmare
// Course:		GAM150S19-B
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <AEEngine.h>
#include "WeaponShop.h"
#include "GameStateManager.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

void WeaponShopLoad()
{

}

// Initialize the ...
void WeaponShopInit()
{
}

// Update the ...
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void WeaponShopUpdate(float dt)
{
	/* Tell the compiler that the 'dt' variable is unused. */
	UNREFERENCED_PARAMETER(dt);

	if (AEInputCheckTriggered('1'))
	{
		GameStateManagerSetNextState(GsLevel1);
	}
	else if (AEInputCheckTriggered('2'))
	{
		GameStateManagerSetNextState(GsLevel2);
	}
	else if (AEInputCheckTriggered('3'))
	{
		GameStateManagerSetNextState(GsArmorShop);
	}
	else if (AEInputCheckTriggered('4'))
	{
		GameStateManagerSetNextState(GsRestart);
	}
}

// Shutdown the ...
void WeaponShopShutdown()
{
}

void WeaponShopUnload()
{

}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

