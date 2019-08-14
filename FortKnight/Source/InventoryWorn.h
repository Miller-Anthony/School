//------------------------------------------------------------------------------
//
// File Name:	InventoryWorn.h
// Author(s):	Anthony Miller
// Project:		Knightmare
// Course:		GAM150S19-B
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "ItemData.h"

//------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
	/* Assume C declarations for C++ */
#endif

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

	//typedef struct Slot Slot;

//------------------------------------------------------------------------------
// Public Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------
	
	typedef struct InventoryWorn * InventoryWornPtr;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

	InventoryWornPtr createWornInventory(void);

	void WornInventoryFree(InventoryWornPtr * inventory);

	Items WornInventoryGetId(InventoryWornPtr inventory, SlotIndex slot);

	void WornInventorySetId(InventoryWornPtr inventory, Items id);

	int WornInventoryGetCount(InventoryWornPtr inventory, SlotIndex slot);

	void WornInventorySetCount(InventoryWornPtr inventory, SlotIndex slot, int count);

	Items EquipItem(InventoryWornPtr inventory, Items id);

	Items RemoveItem(InventoryWornPtr inventory, SlotIndex slot);

	int WornInventoryGetGold(InventoryWornPtr inventory);

	void WornInventorySetGold(InventoryWornPtr inventory, int count);

	void WornInventoryAddGold(InventoryWornPtr inventory, int count);

//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

