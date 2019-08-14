/******************************************************************************
filename    Objects.h
author      Brayan
DP email    brayan.lopez@digipen.edu
course      GAM150

Brief Description:
    This file includes the public interface for gameobjects.
******************************************************************************/
#pragma once

#include "targetver.h" /* required by Windows */
#include <stdbool.h> /* bool */
#include "SpriteSource.h"
#include "Sprite.h"
#include "Physics.h"
#include "Transform.h"
#include "Animation.h"

#define PI4		0.78539816339f	//up-right
#define PI2		1.57079632679f	//up
#define PI3_4	2.35619449019f	//left-up
#define PI5_4	3.92699081699f	//left-down
#define PI3_2	4.71238898038f	//down
#define PI7_4	5.49778714378f	//right-down
#define MAXOBJECTAMOUNT 40

typedef struct Collider Collider;
typedef Collider* ColliderPtr;
typedef enum Items Items;
typedef struct InventoryWorn InventoryWorn;
typedef InventoryWorn* InventoryWornPtr;
typedef struct Object Object;
typedef Object* ObjectPtr;
typedef struct DamagePopup DamagePopup;
typedef DamagePopup* DamagePopupPtr;
typedef struct Item Item;
typedef Item* ItemPtr;
typedef struct Human Human;
typedef Human* HumanPtr;
typedef struct Enemy Enemy;
typedef Enemy* EnemyPtr;
typedef struct Player Player;
typedef Player* PlayerPtr;
typedef void(*AIFightFunctionPtr)(EnemyPtr AI);

#pragma region PUBLIC_STRUCTURES
//first 5 match with inventory slots in ItemData.h
typedef enum ItemType //type of item
{
	Head,
	Body,
	Legs,
	Weapon,
	Shield,
	TrapGround,
	TrapSky
}ItemType;


typedef enum FaceDir //direction facing/dodging
{
	right,
	upright,
	up,
	upleft,
	left,
	downleft,
	down,
	downright,
	FaceDirMAX
}FaceDir;

typedef enum HumanState
{
	HSidle,
  HSstun,
	HSrun,
	HSattack,
	HSblock,
	HSdodge,
  HSknockedback,
	HSMax
}HumanState;

typedef enum ObjectType
{
	ObjTag,
	ItemTag,
	PlayerTag,
	Player2Tag,
	EnemyTag,
	ObjectTypeMAX
}ObjectType;

typedef enum DrawLayer
{
    //DrawBackground,
    DrawSword,
    DrawLegs,
    DrawBody,
    DrawHead,
    //DrawUI,
    DrawLayerMax
}DrawLayer;

typedef enum DamagePopupType
{
    DPHit,
    DPBlock,
    DPParry,
    DPPerfectBlock,
    DPStun,
    DPRegen,
    DPUpgrade,
    DPPlayer1Wins,
    DPPlayer2Wins,
    DPMAX
}DamagePopupType;

#pragma endregion

#pragma region PUBLIC_FUNCTION_DECLARATIONS

#pragma region GETTERS
//Object physics component
PhysicsPtr ObjectGetPhysics(ObjectPtr obj);
//Gets transform component
TransformPtr ObjectGetTransform(ObjectPtr obj);
//Gets sprite component
SpritePtr ObjectGetSprite(ObjectPtr obj);
//Gets spritesource from sprite component
SpriteSourcePtr ObjectGetSpriteSource(ObjectPtr obj);
//gets an animation from object
AnimationPtr ObjectGetAnimation(ObjectPtr obj);
//Gets collider from Object
ColliderPtr ObjectGetCollider(ObjectPtr obj);
//Gets human that contains this object
HumanPtr ObjectGetHuman(ObjectPtr obj);
//Gets object tag
ObjectType ObjectGetTag(ObjectPtr obj);
//Gets Object's Draw Layer
DrawLayer ObjectGetDrawLayer(ObjectPtr obj);
//Gets object name
const char* ObjectGetName(ObjectPtr obj);
//Gets ItemType from item
ItemType ItemGetType(ItemPtr item);
//Gets  resistance stat from item
float ItemGetResistance(ItemPtr item);
//Specify a "bool" you want to know about by passing a 1 into that parameter, 0 in all others
int HumanGetBool(HumanPtr human, int attacking, int running, int hurt, int dead, int dodging, int blocking);
//Returns true if the human is performing an action, false otherwise
int HumanGetActive(HumanPtr human);
//Gets the human's action delay timer
int HumanGetActionDelay(HumanPtr human);
//Gets health amount from player
float HumanGetHealth(HumanPtr human);
//gets the amount of gold human has
//int HumanGetGold(HumanPtr human);
//Gets attack damage amount from an object, unless both pointers are valid then it returns sum of attack damages
float ObjectGetAttackDamage(HumanPtr human, ItemPtr item);
//Gets speed amount from human
float HumanGetSpeed(HumanPtr human);
//Gets dodge speed amount from human
float HumanGetDodgeSpeed(HumanPtr human);
//gets an items speed boost stat
float ItemGetSpeedBoost(ItemPtr item);
//gets an item health boost stat
float ItemGetHealthBoost(ItemPtr item);
//Gets BlockResist amount from human
float HumanGetBlockResist(HumanPtr human);
//Gets direction facing from human
FaceDir HumanGetFaceDir(HumanPtr human);
//Gets direction dodging from human
FaceDir HumanGetDodgeDir(HumanPtr human);
//Gets a facedir with a specified facedir and offset
FaceDir FaceDirGetWithOffset(const FaceDir dir, const int offset);
//Specify which (s) you want to get with valid pointers
void HumanGetArmors(HumanPtr human, ItemPtr* outHead, ItemPtr* outBody, ItemPtr* outLegs);
//Returns the inventory worn pointer
InventoryWornPtr HumanGetInventoryWorn(HumanPtr human);
//Gets object struct from one gameobject, specify which with a valid pointer and NULL for the rest
ObjectPtr ObjectGetObject(HumanPtr human, ItemPtr item, PlayerPtr player, EnemyPtr enemy);
//Gets human struct from a gameobject, specify which with a valid pointer and NULL for the rest
HumanPtr HumanGetHuman(PlayerPtr player, EnemyPtr enemy);
//Get activation delay of stage Trap
float ItemGetDelay(ItemPtr Trap);
//Gets an item's range
float ItemGetRange(ItemPtr item);
//Get Currently equipped weapon
ItemPtr HumanGetWeapon(HumanPtr human);
//Get Enemy's target
HumanPtr EnemyGetTarget(EnemyPtr enemy);
//Gets a Human's fight focus stats
void HumanGetFightFocuses(HumanPtr human, int* outAttack, int* outBlock, int* outDodgeInRange, int* outRunToTarget, int* outDodgeOutOfRange);
//gets a human's kill count
unsigned HumanGetKillCount(HumanPtr human);
//gets canDodge from human
bool HumanGetCanDodge(HumanPtr human);
//gets controller id of player
unsigned PlayerGetControllerID(PlayerPtr player);
//gets a human's next state
HumanState HumanGetNextState(HumanPtr human);
//gets a human's current state
HumanState HumanGetCurrentState(HumanPtr human);
//gets human's name
const char* HumanGetName(HumanPtr human);
//gets if the human is a player or not
bool HumanIsPlayer(HumanPtr human);
//gets the quality of the item
int ItemGetQuality(ItemPtr item);

#pragma endregion

#pragma region SETTERS
//Attaches physics component to object
void ObjectSetPhysics(PhysicsPtr physics, ObjectPtr obj);
//Attaches transform component to object
void ObjectSetTransform(TransformPtr transform, ObjectPtr obj);
//Attaches sprite component to object
void ObjectSetSprite(SpritePtr sprite, ObjectPtr obj);
//Attaches collider component to object
void ObjectSetCollider(ObjectPtr obj, ColliderPtr col);
//Sets an object's Human object pointer
void ObjectSetHuman(ObjectPtr obj, HumanPtr human);
//Set an object's tag
void ObjectSetTag(ObjectType tag, ObjectPtr obj);
//Sets an object's Draw Layer
void ObjectSetDrawLayer(ObjectPtr obj, DrawLayer drawLayer);
//Set an object's name
void ObjectSetName(const char* tag, ObjectPtr obj);
//Sets an item type to an item
void ItemSetType(ItemPtr item, ItemType type);
//Sets resistance to an item (for armors)
void ItemSetResistance(ItemPtr item, float resistance);
//Sets specific values to "bools", pass in a 0 for those you dont want changed
void HumanSetBoolOn(HumanPtr human, int attacking, int running, int hurt, int dead, int dodging, int blocking);
//Specify which "bools" to turn off by passing in a value > 0, 0 for those you dont want changed
void HumanSetBoolOff(HumanPtr human, int attacking, int running, int hurt, int dead, int dodging, int blocking);
//Sets all "bools" to specific values
void HumanSetBool(HumanPtr human, int attacking, int running, int hurt, int dead, int dodging, int blocking);
//Lowers all "bools" by amount specified
void HumanSubBool(HumanPtr human, int attacking, int running, int hurt, int dead, int dodging, int blocking);
//Adds to all "bools" by amount specified
void HumanAddBool(HumanPtr human, int attacking, int running, int hurt, int dead, int dodging, int blocking);
//Sets a human's action delay timer
void HumanSetActionDelay(HumanPtr human, int actionDelay);
//Sets a human's health
void HumanSetHealth(HumanPtr human, float health);
//Set the previous health stat (used for the read bar after you get hurt)
void HumanSetPreviousHealth(HumanPtr human, float previousHealth);
//Set it you are displaying the hmans health or not
void HumanSetShowHealth(HumanPtr human, bool value);
//set if you are displaying the humans stamina or not
void HumanSetShowStamina(HumanPtr human, bool value);
//Sets a human's gold
//void HumanSetGold(HumanPtr human, unsigned int gold);
//Specify which gameobjects to set an attack damage to by passing in valid pointers, pass in a NULL for the rest
void ObjectSetAttackDamage(HumanPtr human, ItemPtr item, float attackDamage);
//Sets a human's speed
void HumanSetSpeed(HumanPtr human, float speed);
//Sets a human's dodging speed
void HumanSetDodgeSpeed(HumanPtr human, float dodgeSpeed);
//Sets facing direction of a human. returns an index of a 4-direction facing (frbl)
int HumanSetFaceDir(HumanPtr human, FaceDir direction);
//Sets dodge direction of a human
void HumanSetDodgeDir(HumanPtr human, FaceDir direction);
//Pass in indexes of Items table of armors to give to Human
void HumanSetArmors(HumanPtr human, Items head, Items body, Items legs);
//Sets a Human's inventory
void HumanSetInventoryWorn(HumanPtr human, InventoryWornPtr inventory);
//Sets a human's currently equipped weapon by passing in an index of a weapon from the Items table
void HumanSetWeapon(HumanPtr human, Items weapon);
//Set Trap activation delay
void ItemSetDelay(ItemPtr Trap, float delay);
//Sets and item's range
void ItemSetRange(ItemPtr item, float range);
//sets a human's targets to targets
void HumanSetTargets(HumanPtr human, HumanPtr targets[MAXOBJECTAMOUNT]);
//adds a target to human's targets, does nothing if targets is full
void HumanAddTarget(HumanPtr human, HumanPtr target);
//removes a target from a human's targets
void HumanRemoveTarget(HumanPtr human, HumanPtr target);
//retargets an enemy to another target, returns target count
int EnemyRetarget(EnemyPtr enemy, HumanPtr target);
//removes all targets from human
void HumanResetTargets(HumanPtr human);
//sets a human's fight focuses
void HumanSetFightFocuses(HumanPtr human, int attack, int block, int dodgeInRange, int dodgeOutOfRange, int runToTarget);
//sets a human's next state
void HumanSetNextState(HumanPtr human, HumanState HSstate);
//sets human's name
void HumanSetName(HumanPtr human, const char* name);
//set a human's kill leader state
void HumanSetKillLeader(HumanPtr human, bool killLeader);
//sets a player's controller id
void PlayerSetControllerID(PlayerPtr player, unsigned id);
#pragma endregion

#pragma region OBJECT_HANDLING

//Creates an object with a name, tag, physics, sprite, and transform, You will need to set SpriteSource and Mesh manually
ObjectPtr CreateObject(const char* name, ObjectType tag);
//Frees Object and attached transform ,sprite, and physics
void FreeObject(ObjectPtr* obj);
//Creates an item with everything it will ever need
ItemPtr CreateItem(const char* name, ObjectType tag, float damageResistance, float damageBoost, float healthBoost, float speedBoost, float delay, float range,
    ItemType type, AEVec2 scales[4], const char* frblIdle[4], AEGfxVertexList * mesh1x1, DrawLayer drawLayer, unsigned idleFrames, unsigned runFrames, unsigned attackFrames,
    unsigned blockFrames, unsigned dodgeFrames, AEGfxVertexList* mesh4x2, float abrdDurs[4], const char* frblRun[4], const char* frblAttack[4], const char* frblDodge[4],
    const char* frblBlock[4], Items id, int quality);
//Creates a human with health, attack, speed, and Object
HumanPtr CreateHuman(const char* name, ObjectType tag, float health, float stamina, float attack, float speed, float dodgeSpeed, float blockResist, bool showHealth, bool showStamina);
//Frees a human by freeing the base human, Object
void FreeHuman(HumanPtr* human);
//Creates an empty player with Object, health,attack,speed
PlayerPtr CreatePlayer(const char* name, ObjectType tag, float health, float stamina, float attack, float speed, float dodgeSpeed, float blockResist, bool showHealth, bool showStamina);
void FreePlayer(PlayerPtr* player);
//Creates an empty enemy with health,attack,speed
EnemyPtr CreateEnemy(const char* name, ObjectType tag, float health, float stamina, float attack, float speed, float dodgeSpeed, float blockResist, AIFightFunctionPtr fightStyle,
    int blockFocus, int attackFocus, int dodgeinRangeFocus, int dodgeNotInRangeFocus, int runFocus, bool showHealth, bool showStamina);
    //frees an enemy by freeing the enemy, base human and transform, and physics
void FreeEnemy(EnemyPtr* enemy);

#pragma endregion

#pragma region OBJECT_DRAWING

// Draw any visible components attached to the game object.
void DrawObject(ObjectPtr Object);

#pragma region AMERICA

// Draw the humans health bar
void HumanDrawHealth(HumanPtr human);

// Draw the humans stamina bar
void HumanDrawStamina(HumanPtr human);

#pragma endregion

#pragma region ITEM_DRAWER

//Dynamically allocates memory for Item Drawer
void InitItemDrawer();
//Resets everything in ItemDrawer back to default so no items get drawn to screen (DOES NOT FREE)
void ResetItemDrawer();
//Frees up all memory used by Item Drawer
void FreeItemDrawer();
//Queues an item up for drawing
void ItemQueueForDrawing(SpritePtr item, TransformPtr transform, SpriteSourcePtr spriteSource, DrawLayer layer, bool hurt);
//Draws all the items that are queued up to be drawn
void DrawItemsInQueue();

#pragma endregion

#pragma region DAMAGE_POPUP_DRAWER

//call only level load
void InitDamagePopupDrawer();
//call on level shutdown and unload, but never after DamagePopupsFree()
void ResetDamagePopupDrawer();
//call whenever an attack that made contact occured
void DamagePopupQueueForDrawing(float r, float g, float b, float a, int damage, float damageAmountYOffset, float damageActionOffset, TransformPtr position, DamagePopupType dptype, bool showNum, float scale);
//call on update after DrawItemsInQueue()
void DamagePopupsDraw();
//call on level unload after ResetDamagePopupDrawer()
void DamagePopupsFree();

#pragma endregion

#pragma endregion
//Updates Human and attached Physics, Transform, Head, Body, Legs
//returns if human got "yoinked"-Spice
bool UpdateHuman(HumanPtr human);
#pragma endregion