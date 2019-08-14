//------------------------------------------------------------------------------
//
// File Name:	Player.c
// Author(s):	Anthony Miller
// Project:		Knightmare
// Course:		GAM150S19-B
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Player.h"
#include "Objects.h"
#include "InventoryWorn.h"
#include "Collision.h"
#include "ItemData.h"

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

Player *player;

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

void PlayerCreate()
{
	player = CreatePlayer("player", PlayerTag, 100, 100, 5, 30, 120, 33, true, true);

	AEVec2 translate = { 0.0f,0.0f };
	//AEVec2 humanScale = { 102.3f,60.0f };

	ObjectPtr obj = ObjectGetObject(NULL, NULL, player, NULL);
	TransformPtr trans = ObjectGetTransform(obj);

	AEVec2 scale = { 20, 30 };
	ColliderSetScale(ObjectGetCollider(obj), &scale);

	TransformSetTranslation(trans, &translate);
	//TransformSetScale(trans, &humanScale);
	EquipItem(HumanGetInventoryWorn(HumanGetHuman(player, NULL)), WoodSword);
	EquipItem(HumanGetInventoryWorn(HumanGetHuman(player, NULL)), ClothHelm);
	EquipItem(HumanGetInventoryWorn(HumanGetHuman(player, NULL)), ClothChest);
	EquipItem(HumanGetInventoryWorn(HumanGetHuman(player, NULL)), ClothBoots);
	EquipItem(HumanGetInventoryWorn(HumanGetHuman(player, NULL)), DefaultShield);
}

HumanPtr PlayerGetHuman()
{
	return HumanGetHuman(player, NULL);
}

ObjectPtr PlayerGetObject()
{
	return ObjectGetObject(NULL, NULL, player, NULL);
}

int PlayerGetGold()
{
	return WornInventoryGetGold(HumanGetInventoryWorn(PlayerGetHuman()));
}

void PlayerSetGold(int count)
{
	WornInventorySetGold(HumanGetInventoryWorn(PlayerGetHuman()), count);
}

void PlayerAddGold(int count)
{
	WornInventoryAddGold(HumanGetInventoryWorn(PlayerGetHuman()),  count);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

