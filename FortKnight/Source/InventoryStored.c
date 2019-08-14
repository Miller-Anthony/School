//------------------------------------------------------------------------------
//
// File Name:	InventoryStored.c
// Author(s):	Anthony Miller
// Project:		Knightmare
// Course:		GAM150S19-B
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "InventoryStored.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct Slot
{
  int IdNum;
  int count;
}Slot;

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

StoredInventoryPtr createStoredSlot(void)
{
  StoredInventoryPtr holder = calloc(4, sizeof(Slot));
  return holder;
}


void StoredInventoryFree(StoredInventoryPtr * inventory)
{
  int count = 4;
  do
  {
    count--;
    free(*(inventory + count));
    *(inventory + count) = NULL;
  } while (count);
}

int StoredInventoryGetId(StoredInventoryPtr inventory)
{
  if (inventory)
  {
    return inventory->IdNum;
  }
  return 0;
}

void StoredInventorySetId(StoredInventoryPtr inventory, int id)
{
  if (inventory)
  {
    inventory->IdNum = id;
  }
}

int StoredInventoryGetCount(StoredInventoryPtr inventory)
{
  if (inventory)
  {
    return inventory->count;
  }
  return 0;
}

void StoredInventorySetCount(StoredInventoryPtr inventory, int count)
{
  if (inventory)
  {
    inventory->count = count;
  }
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

