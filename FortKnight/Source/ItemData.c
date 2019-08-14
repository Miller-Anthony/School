//------------------------------------------------------------------------------
//
// File Name:	ItemData.c
// Author(s):	Anthony Miller
// Project:		Knightmare
// Course:		GAM150S19-B
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "ItemData.h"
#include "Objects.h"
#include "Mesh.h"
#include "Animation.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

static ItemPtr table[ItemCount];

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------
static AEVec2 headScales[4] = { { 102.0f,108.3f } ,{ 102.0f,108.3f}, {102.0f,105.0f}, { 102.0f,108.3f} };
static AEVec2 bodyScales[4] = { {  102.3f,60.0f } ,{78.0f,60.0f}, {72.0f,57.0f}, {78.0f,60.0f} };
static AEVec2 legScales[4] = { { 60.0f,45.3f } ,{51.0f,45.0f}, {60.0f,45.3f}, {51.0f,45.0f} };
static AEVec2 swordScales[4] = { { 110.0f,150.0f } ,{130.0f,21.0f}, {120.0f,160.0f}, {130.0f,21.0f} };
static AEVec2 shieldScales[4] = { { 80.0f,80.0f } ,{80.0f,80.0f}, { 80.0f,80.0f}, {80.0f,80.0f} };

static float abrdDurs[4] = { .125f, .125f, .125f, .125f };

static const char* woodSwords[4] = { "Assets/WSF.png", "Assets/WSR.png", "Assets/WSB.png", "Assets/WSL.png" };
static const char* ironSwords[4] = { "Assets/ISF.png", "Assets/ISR.png", "Assets/ISB.png", "Assets/ISL.png" };
static const char* steelSwords[4] = { "Assets/SSF.png", "Assets/SSR.png", "Assets/SSB.png", "Assets/SSL.png" };

static const char* shield[4] = { "Assets/ShieldF.png", "Assets/ShieldR.png", "Assets/ShieldB.png", "Assets/ShieldL.png" };

static const char* clothHelms[4] = { "Assets/Player_H1.png", "Assets/Player_H2.png", "Assets/Player_H3.png", "Assets/Player_H4.png" };
static const char* leatherHelms[4] = { "Assets/LeatherHelmFront.png", "Assets/LeatherHelmRight.png", "Assets/LeatherHelmBack.png", "Assets/LeatherHelmLeft.png" };
static const char* ironHelms[4] = { "Assets/Boss1_H1.png", "Assets/Boss1_H2.png", "Assets/Boss1_H3.png", "Assets/Boss1_H4.png" };
static const char* steelHelms[4] = { "Assets/SteelHelmFront.png", "Assets/SteelHelmRight.png", "Assets/SteelHelmBack.png", "Assets/SteelHelmLeft.png" };

static const char* clothChests[4] = { "Assets/IdleDefaultBF.png", "Assets/IdleDefaultBR.png", "Assets/IdleDefaultBB.png", "Assets/IdleDefaultBL.png" };
static const char* clothChestsA[4] = { "Assets/DefaultA_F.png", "Assets/DefaultA_R.png", "Assets/DefaultA_B.png", "Assets/DefaultA_L.png" };
static const char* clothChestsR[4] = { "Assets/DefaultBF_Y.png", "Assets/DefaultBR_Y.png", "Assets/DefaultBB_Y.png", "Assets/DefaultBL_N.png" };
static const char* clothChestsB[4] = { "Assets/DefaultA_F.png", "Assets/DefaultA_R.png", "Assets/DefaultA_B.png", "Assets/DefaultA_L.png" };
//static const char* clothChestsB[4] = { "Assets/DefaultB_F.png", "Assets/DefaultB_R.png", "Assets/DefaultB_B.png", "Assets/DefaultB_L.png" };
static const char* leatherChests[4] = { "Assets/IdleLeatherBF.png", "Assets/IdleLeatherBR.png", "Assets/IdleLeatherBB.png", "Assets/IdleLeatherBL.png" };
static const char* leatherChestsA[4] = { "Assets/LeatherA_F.png", "Assets/LeatherA_R.png", "Assets/LeatherA_B.png", "Assets/LeatherA_L.png" };
static const char* leatherChestsR[4] = { "Assets/LeatherBF_Y.png", "Assets/LeatherBR_Y.png", "Assets/LeatherBB_Y.png", "Assets/LeatherBL_N.png" };
static const char* leatherChestsB[4] = { "Assets/LeatherA_F.png", "Assets/LeatherA_R.png", "Assets/LeatherA_B.png", "Assets/LeatherA_L.png" };
//static const char* leatherChestsB[4] = { "Assets/LeatherB_F.png", "Assets/LeatherB_R.png", "Assets/LeatherB_B.png", "Assets/LeatherB_L.png" };
static const char* ironChests[4] = { "Assets/IdleIronBF.png", "Assets/IdleIronBR.png", "Assets/IdleIronBB.png", "Assets/IdleIronBL.png" };
static const char* ironChestsA[4] = { "Assets/IronA_F.png", "Assets/IronA_R.png", "Assets/IronA_B.png", "Assets/IronA_L.png" };
static const char* ironChestsR[4] = { "Assets/IronBF_Y.png", "Assets/IronBR_Y.png", "Assets/IronBB_Y.png", "Assets/IronBL_N.png" };
static const char* ironChestsB[4] = { "Assets/IronA_F.png", "Assets/IronA_R.png", "Assets/IronA_B.png", "Assets/IronA_L.png" };
//static const char* ironChestsB[4] = { "Assets/IronB_F.png", "Assets/IronB_R.png", "Assets/IronB_B.png", "Assets/IronB_L.png" };
static const char* steelChests[4] = { "Assets/IdleSteelBF.png", "Assets/IdleSteelBR.png", "Assets/IdleSteelBB.png", "Assets/IdleSteelBL.png" };
static const char* steelChestsA[4] = { "Assets/SteelA_F.png", "Assets/SteelA_R.png", "Assets/SteelA_B.png", "Assets/SteelA_L.png" };
static const char* steelChestsR[4] = { "Assets/SteelBF_Y.png", "Assets/SteelBR_Y.png", "Assets/SteelBB_Y.png", "Assets/SteelBL_N.png" };
static const char* steelChestsB[4] = { "Assets/SteelA_F.png", "Assets/SteelA_R.png", "Assets/SteelA_B.png", "Assets/SteelA_L.png" };
//static const char* steelChestsB[4] = { "Assets/SteelB_F.png", "Assets/SteelB_R.png", "Assets/SteelB_B.png", "Assets/SteelB_L.png" };

static const char* clothBoots[4] = { "Assets/IdleDefaultLF.png", "Assets/IdleDefaultLR.png", "Assets/IdleDefaultLB.png", "Assets/IdleDefaultLL.png" };
static const char* clothBootsR[4] = { "Assets/DefaultLF.png", "Assets/DefaultLR.png", "Assets/DefaultLB.png", "Assets/DefaultLL.png" };
static const char* leatherBoots[4] = { "Assets/IdleLeatherLF.png", "Assets/IdleLeatherLR.png", "Assets/IdleLeatherLB.png", "Assets/IdleLeatherLL.png" };
static const char* leatherBootsR[4] = { "Assets/LeatherLF.png", "Assets/LeatherLR.png", "Assets/LeatherLB.png", "Assets/LeatherLL.png" };
static const char* ironBoots[4] = { "Assets/IdleIronLF.png", "Assets/IdleIronLR.png", "Assets/IdleIronLB.png", "Assets/IdleIronLL.png" };
static const char* ironBootsR[4] = { "Assets/IronLF.png", "Assets/IronLR.png", "Assets/IronLB.png", "Assets/IronLL.png" };
static const char* steelBoots[4] = { "Assets/IdleSteelLF.png", "Assets/IdleSteelLR.png", "Assets/IdleSteelLB.png", "Assets/IdleSteelLL.png" };
static const char* steelBootsR[4] = { "Assets/SteelLF.png", "Assets/SteelLR.png", "Assets/SteelLB.png", "Assets/SteelLL.png" };

static AEGfxVertexList* Mesh1x1;
static AEGfxVertexList* Mesh4x2;
//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

void CreateItemsMesh();

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

void ItemTablePopulate()
{
	CreateItemsMesh();

  table[DefaultShield] = CreateItem("Default Shield", ItemTag, 50.0f, .0f, .0f, .0f, .0f, .0f, Shield, shieldScales, shield, Mesh1x1, DrawBody, 1, 1, 1, 1, 1, Mesh1x1, abrdDurs, shield, shield, shield, shield, DefaultShield, 1);

	table[WoodSword] = CreateItem("Wood Sword", ItemTag, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 145.0f, Weapon, swordScales, woodSwords, Mesh1x1, DrawBody, 1,1,1,1,1,Mesh1x1,abrdDurs,woodSwords,woodSwords,woodSwords,woodSwords, WoodSword, 1);
	table[IronSword] = CreateItem("Iron Sword", ItemTag, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 165.0f, Weapon, swordScales, ironSwords, Mesh1x1, DrawBody, 1,1,1,1,1,Mesh1x1,abrdDurs,ironSwords,ironSwords,ironSwords,ironSwords, IronSword, 2);
	table[SteelSword] = CreateItem("Steel Sword", ItemTag, 0.0f, 15.0f, 0.0f, 0.0f, 0.0f, 180.0f, Weapon, swordScales, steelSwords, Mesh1x1, DrawBody, 1,1,1,1,1,Mesh1x1,abrdDurs,steelSwords,steelSwords,steelSwords,steelSwords, SteelSword, 3);

	table[ClothHelm] = CreateItem("Cloth Helm", ItemTag, 5.0f, 0.0f, 2.0f, 0.0f, 0.0f, 1.0f, Head, headScales, clothHelms, Mesh1x1, DrawHead,1,1,1,1,1, Mesh1x1,abrdDurs,clothHelms,clothHelms,clothHelms,clothHelms,ClothHelm, 1);
	table[ClothChest] = CreateItem("Cloth Chest", ItemTag, 5.0f, 0.0f, 2.5f, 0.0f, 0.0f, 1.0f, Body, bodyScales, clothChests, Mesh4x2, DrawBody,8,8,8,8,8,Mesh4x2,abrdDurs,clothChestsR,clothChestsA,clothChests,clothChestsB,ClothChest, 1);
	table[ClothBoots] = CreateItem("Cloth Boots", ItemTag, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, Legs, legScales, clothBoots, Mesh4x2, DrawLegs,8,8,8,8,8,Mesh4x2,abrdDurs,clothBootsR,clothBoots,clothBoots,clothBoots,ClothBoots, 1);

	table[LeatherHelm] = CreateItem("Leather Helm", ItemTag, 10.0f, 0.0f, 3.0f, 0.0f, 0.0f, 1.0f, Head, headScales, leatherHelms, Mesh1x1,DrawHead,1,1,1,1,1,Mesh4x2,abrdDurs,leatherHelms,leatherHelms,leatherHelms,leatherHelms,LeatherHelm, 2);
	table[LeatherChest] = CreateItem("Leather Chest", ItemTag, 10.0f, 0.0f, 5.0f, 0.0f, 0.0f, 1.0f, Body, bodyScales, leatherChests, Mesh4x2, DrawBody,8,8,8,8,8,Mesh4x2,abrdDurs,leatherChestsR,leatherChestsA,leatherChests,leatherChestsB,LeatherChest, 2);
	table[LeatherBoots] = CreateItem("Leather Boots", ItemTag, 10.0f, 0.0f, 0.0f, 5.0f, 0.0f, 1.0f, Legs, legScales, leatherBoots, Mesh4x2, DrawLegs,8,8,8,8,8,Mesh4x2,abrdDurs,leatherBootsR,leatherBoots,leatherBoots,leatherBoots,LeatherBoots, 2);

	table[IronHelm] = CreateItem("Iron Helm", ItemTag, 15.0f, 0.0f, 5.0f, 0.0f, 0.0f, 1.0f, Head, headScales, ironHelms, Mesh1x1, DrawHead,1,1,1,1,1,Mesh4x2,abrdDurs,ironHelms,ironHelms,ironHelms,ironHelms,IronHelm, 3);
	table[IronChest] = CreateItem("Iron Chest", ItemTag, 15.0f, 0.0f, 10.0f, 0.0f, 0.0f, 1.0f, Body, bodyScales, ironChests, Mesh4x2, DrawBody,8,8,8,8,8,Mesh4x2,abrdDurs,ironChestsR,ironChestsA,ironChests,ironChestsB,IronChest, 3);
	table[IronBoots] = CreateItem("Iron Boots", ItemTag, 15.0f, 0.0f, 0.0f, 10.0f, 0.0f, 1.0f, Legs, legScales, ironBoots, Mesh4x2, DrawLegs,8,8,8,8,8,Mesh4x2,abrdDurs,ironBootsR,ironBoots,ironBoots,ironBoots,IronBoots, 3);

	table[SteelHelm] = CreateItem("Steel Helm", ItemTag, 20.0f, 0.0f, 7.0f, 0.0f, 0.0f, 1.0f, Head, headScales, steelHelms, Mesh1x1, DrawHead,1,1,1,1,1,Mesh4x2,abrdDurs,steelHelms,steelHelms,steelHelms,steelHelms,SteelHelm, 4);
	table[SteelChest] = CreateItem("Steel Chest", ItemTag, 20.0f, 0.0f, 15.0f, 0.0f, 0.0f, 1.0f, Body, bodyScales, steelChests, Mesh4x2, DrawBody,8,8,8,8,8,Mesh4x2,abrdDurs,steelChestsR,steelChestsA,steelChests,steelChestsB,SteelChest, 4);
	table[SteelBoots] = CreateItem("Steel Boots", ItemTag, 20.0f, 0.0f, 0.0f, 15.0f, 0.0f, 1.0f, Legs, legScales, steelBoots, Mesh4x2, DrawLegs,8,8,8,8,8,Mesh4x2,abrdDurs,steelBootsR,steelBoots,steelBoots,steelBoots,SteelBoots, 4);

  for (int i = 0; i < ItemCount; ++i)
  {
      SpriteSourcePtr ss = ObjectGetSpriteSource(ObjectGetObject(NULL, table[i], NULL, NULL));
      AnimationPlay(ObjectGetAnimation(ObjectGetObject(NULL, table[i], NULL, NULL)),SpriteSourceGetFrameCount(ss),abrdDurs[0],NULL,true);
  }
}

ItemPtr ItemGetByID(Items ID)
{
	return table[ID];
}

SlotPtr CreateSlot()
{
	SlotPtr holder = calloc(1, sizeof(Slot));
	return holder;
}

void FreeSlot(SlotPtr * slot)
{
	if (slot)
	{
		free(*slot);
		*slot = NULL;
	}
}

void UpdateItems()
{
    for (int i = 0; i < ItemCount; ++i)
    {
        AnimationUpdate(ObjectGetAnimation(ObjectGetObject(NULL, table[i], NULL, NULL)));
    }
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

void CreateItemsMesh()
{
	Mesh1x1 = MeshCreateQuad(0.5f, 0.5f, 1.0f, 1.0f, "Mesh1x1");
  Mesh4x2 = MeshCreateQuad(0.5f, 0.5f, 1.0f / 4, 1.0f / 2, "Mesh4x2");
}