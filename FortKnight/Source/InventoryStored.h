//------------------------------------------------------------------------------
//
// File Name:	InventoryStored.h
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

//------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
	/* Assume C declarations for C++ */
#endif

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

  typedef struct Slot * StoredInventoryPtr;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

  StoredInventoryPtr createStoredSlot(void);

  void StoredInventoryFree(StoredInventoryPtr * inventory);

  int StoredInventoryGetId(StoredInventoryPtr inventory);

  void StoredInventorySetId(StoredInventoryPtr inventory, int id);

  int StoredInventoryGetCount(StoredInventoryPtr inventory);

  void StoredInventorySetCount(StoredInventoryPtr inventory, int count);

//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

