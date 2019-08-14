//------------------------------------------------------------------------------
//
// File Name:	ItemData.h
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

#include "Objects.h"

//------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
	/* Assume C declarations for C++ */
#endif

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

    //typedef struct Animation* AnimationPtr;

//------------------------------------------------------------------------------
// Public Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

	typedef enum Items
	{
    Empty,
    DefaultShield,
		WoodSword,
		IronSword,
		SteelSword,
		ClothHelm,
		ClothChest,
		ClothBoots,
		LeatherHelm,
		LeatherChest,
		LeatherBoots,
		IronHelm,
		IronChest,
		IronBoots,
		SteelHelm,
		SteelChest,
		SteelBoots,
		ItemCount
	}Items;

	typedef enum SlotIndex
	{
		slotHead,			//index of head item
		slotBody,			//index of body item
		slotLegs,			//index of legs item
		slotWeapon,			//index of weapon item
		slotShield, //index of shield
		slotGold,
		slotMax
	}SlotIndex;

	typedef struct Slot
	{
		Items IdNum;
		int count;
	}Slot;

	typedef struct Slot * SlotPtr;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

  void ItemTablePopulate();

  ItemPtr ItemGetByID(Items ID);

  SlotPtr CreateSlot();

  void FreeSlot(SlotPtr * slot);



//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------
  
  void UpdateItems();
//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

