//------------------------------------------------------------------------------
//
// File Name:	InventoryWorn.c
// Author(s):	Anthony Miller
// Project:		Knightmare
// Course:		GAM150S19-B
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "InventoryWorn.h"
#include "ItemData.h"
#include "Player.h"


//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct InventoryWorn
{
	SlotPtr inventory[slotMax];
}InventoryWorn;

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

/*************************************************************************/
/*!

	\brief
		Makes an inventory to be attached to a human.

	\return
		An inventory able to store equiped items by ID.
*/
/*************************************************************************/
InventoryWornPtr createWornInventory(void)
{
		//allocate memory for the inventory and its slots
	InventoryWornPtr holder = calloc(1, sizeof(InventoryWorn));

	//if inventory was successfully allocated
	if (holder)
	{
		int i;
		for (i = slotHead; i < slotMax; i++)
		{
			//create a slot for each inventory space
			holder->inventory[i] = CreateSlot();
		}
	}

	return holder;
}

/*************************************************************************/
/*!

	\brief
		Free the memory of the passed in inventory.

	\param inventory
		inventory to be freed.
*/
/*************************************************************************/
void WornInventoryFree(InventoryWornPtr * inventory)
{
	//if a valid inventory was passed in
	if (inventory)
	{
		int i;
		for (i = slotHead; i < slotMax; i++)
		{
			//free each inventory slot
			FreeSlot(&((*inventory)->inventory[i]));
		}
		//free the inventory
		free(*inventory);
		*inventory = NULL;
	}
}

/*************************************************************************/
/*!

	\brief
		Get the id of the currently equiped item of the given slot.

	\param inventory
		inventory being looked at.

	\param slot
		The inventory slot to be looked at.

	\return
		The item that is in the given slot
*/
/*************************************************************************/
Items WornInventoryGetId(InventoryWornPtr inventory, SlotIndex slot)
{
	if (inventory)
	{
		return inventory->inventory[slot]->IdNum;
	}
  return 0;
}

/*************************************************************************/
/*!

	\brief
		Set what item is in a slot for a given inventory.

	\param inventory
		inventory being modified.

	\param id
		the ID of the item being set.

*/
/*************************************************************************/
void WornInventorySetId(InventoryWornPtr worn, Items id)
{
	if (worn)
	{
		worn->inventory[ItemGetType(ItemGetByID(id))]->IdNum = id;
	}
}

/*************************************************************************/
/*!

	\brief
		get the amount of items in a given inventory slot.

	\param inventory
		inventory being looked at.

	\param slot
		The inventory slot being looked at.

	\return
		The amount of items in the slot (unique items return 0)
*/
/*************************************************************************/
int WornInventoryGetCount(InventoryWornPtr inventory, SlotIndex slot)
{
	if (inventory)
	{
		return inventory->inventory[slot]->count;
	}
  return 0;
}

/*************************************************************************/
/*!

	\brief
		set the number of items equipped in the given slot.

	\param inventory
		inventory being looked at.

	\param slot
		The inventory slot being looked at.

	\param count
		the amount of items in the slot.

*/
/*************************************************************************/
void WornInventorySetCount(InventoryWornPtr inventory, SlotIndex slot, int count)
{
	if (inventory)
	{
		inventory->inventory[slot]->count = count;
	}
}

/*************************************************************************/
/*!

	\brief
		equip an item to the passed in inventory.
	
	\param inventory
		inventory being modified.

	\param id
		the ID of the item being equiped.

    \return
		The item that was previously in the modified slot.
		Retruns empty if the inventory is not valid.
*/
/*************************************************************************/
Items EquipItem(InventoryWornPtr inventory, Items id)
{
	if (inventory)
	{
		//get old item in the slot
		Items holder = WornInventoryGetId(inventory, ItemGetType(ItemGetByID(id)));
		//put the new item in the slot
		WornInventorySetId(inventory, id);
		//return the old item to where the new item came from
		return holder;
	}
	return Empty;
}

/*************************************************************************/
/*!

	\brief
		remove an item from the passed in inventory leaving an empty slot.

	\param inventory
		inventory being modified.

	\param slot
		the slot of the item being removed.

	\return
		The item that was previously in the modified slot
		Retruns empty if the inventory is not valid.
*/
/*************************************************************************/
Items RemoveItem(InventoryWornPtr inventory, SlotIndex slot)
{
	if (inventory)
	{
		//get old item in the slot
		Items holder = WornInventoryGetId(inventory, slot);
		//put the new item in the slot
    inventory->inventory[slot]->IdNum = Empty;
		//WornInventorySetId(inventory, Empty);
		//return the old item to where the new item came from
		return holder;
	}
	return Empty;
}

int WornInventoryGetGold(InventoryWornPtr inventory)
{
	return inventory->inventory[slotGold]->count;
}

void WornInventorySetGold(InventoryWornPtr inventory, int count)
{
	inventory->inventory[slotGold]->count = count;
}

void WornInventoryAddGold(InventoryWornPtr inventory, int count)
{
	inventory->inventory[slotGold]->count += count;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

