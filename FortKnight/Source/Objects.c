// ---------------------------------------------------------------------------
// Project Name		:	Knightmare
// File Name		  :	Objects.c
// Author			    :	Brayan
// Creation Date	:	1/14/2019
// Purpose			  :	Object Declarations and Functions
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// includes

#include "stdafx.h"		// Should be included first in every .c file!

#include "AEEngine.h"
#include "Transform.h"
#include "Sprite.h"
#include "SpriteSource.h"
#include "Objects.h"
#include "Collision.h"
#include "Animation.h"
#include "InventoryWorn.h"
#include "ItemData.h"
#include "AI.h"
#include "Mesh.h"
#include "DT.h"
#include "Animation.h"
#include "Camera.h"
#include "Utils.h"
#include "Input.h"
#include "GameStateManager.h"
#include "Text.H"
#include "OST.h"
#include "GameStateBattleRoyale.h"

#define USING_HUGE_ATTACK_CHEATS  0
#define ARENA_RADIUS_MAX 1500   //width of arena  1920*.78125f
#define ARENA_RADIUS_MIN 750    //height of arena 1080*.69444f
#define FOCUS1 -1299.038106f    //Oval focus 1: -sqrtf(a^2 - b^2) 
#define FOCUS2 1299.038106f     //Oval focus 2: sqrtf(a^2 - b^2) 
#define ITEM_LIST_SIZE MAXOBJECTAMOUNT*2
#define DAMAGE_POPUP_MAX_STRING_LENGTH 32
#define DAMAGE_POPUP_MAX_LIST_SIZE MAXOBJECTAMOUNT*2
extern GameState gameState;
extern float vibrateTime;
extern float vibrateTimeP2;
extern bool isPaused;
bool followKillLeader = false;
// ---------------------------------------------------------------------------

// Libraries
#ifdef _DEBUG
#pragma comment (lib, "Alpha_Engine_D.lib")
#else
#pragma comment (lib, "Alpha_Engine.lib")
#endif

// ---------------------------------------------------------------------------
//private variables

//if huge damage cheat is currently enabled for use
static bool HUGE_DAMAGE_BUFFED = false;

//Stores Sprites/Transforms/SpriteSources for drawing (Item Drawer lists)
static SpritePtr SpriteList[DrawLayerMax][ITEM_LIST_SIZE] = { 0 };
static TransformPtr TransformList[DrawLayerMax][ITEM_LIST_SIZE] = { 0 };
static SpriteSourcePtr SpriteSourceList[DrawLayerMax][ITEM_LIST_SIZE] = { 0 };
static int ItemInUseList[DrawLayerMax][ITEM_LIST_SIZE] = { 0 };
static bool ItemHurtList[DrawLayerMax][ITEM_LIST_SIZE] = { 0 };
//Item Drawer Special Placeholders
static SpritePtr requeueI;
static SpritePtr requeueINext;
static TransformPtr requeueT;
static TransformPtr requeueTNext;
static SpriteSourcePtr requeueSS;
static SpriteSourcePtr requeueSSNext;
static bool requeueHurt;
static bool requeueHurtNext;
//Item Drawer is requeing the Next placeholders
static bool requeueingNext = false;
//Damage Popup Drawer stuff
static TransformPtr DamageTransforms[DAMAGE_POPUP_MAX_LIST_SIZE] = { 0 };
static float DamageReds[DAMAGE_POPUP_MAX_LIST_SIZE] = { 0 };
static float DamageGreens[DAMAGE_POPUP_MAX_LIST_SIZE] = { 0 };
static float DamageBlues[DAMAGE_POPUP_MAX_LIST_SIZE] = { 0 };
static float DamageAlphas[DAMAGE_POPUP_MAX_LIST_SIZE] = { 0 };
static int DamageNums[DAMAGE_POPUP_MAX_LIST_SIZE] = { 0 };
static float DamageAmountOffsets[DAMAGE_POPUP_MAX_LIST_SIZE] = { 0 };
static float DamageActionOffsets[DAMAGE_POPUP_MAX_LIST_SIZE] = { 0 };
static float DamagePopupScales[DAMAGE_POPUP_MAX_LIST_SIZE] = { 0 }; //scales both x and y
static char* DamageAmounts[DAMAGE_POPUP_MAX_LIST_SIZE] = { 0 };
static char* DamageActions[DAMAGE_POPUP_MAX_LIST_SIZE] = { 0 };
static bool DamageSlotFilledList[DAMAGE_POPUP_MAX_LIST_SIZE] = { 0 };
static bool DamageShowNumList[DAMAGE_POPUP_MAX_LIST_SIZE] = { 0 };
//Damage Popup Drawer Sprite
SpritePtr damagePopupSprite;
AEGfxTexture* damageTexture;
AEGfxVertexList* damageMesh;
SpriteSourcePtr damageSS;

#pragma region PRIVATE_STRUCTURES

typedef struct Object //BASE STRUCT FOR ALL GAME OBJECTS
{
	TransformPtr transform; //transform component
	SpritePtr sprite;		    //sprite component
	PhysicsPtr physics;		  //physics component
	ColliderPtr collider;	  //collider component
  AnimationPtr animation; //animation component
  HumanPtr human;         //points to Object's Human structure if it is attached to one
	ObjectType tag;			    //for specifying type of object
  DrawLayer drawLayer;    //for specifying order of drawing objects
	const char* name;		    //name of the object
}Object;

typedef struct Item //Item STRUCTURE [inherits from Object type]
{
	ObjectPtr obj;		            //object pointer
  SpriteSourcePtr idleSS[4];    //front, right, back, left
  SpriteSourcePtr runSS[4];     //front, right, back, left
  SpriteSourcePtr attackSS[4];  //front, right, back, left
  SpriteSourcePtr blockSS[4];   //front, right, back, left
  SpriteSourcePtr dodgeSS[4];   //front, right, back, left
  unsigned runFrames;       //number of frames
  unsigned attackFrames;    //number of frames
  unsigned blockFrames;     //number of frames
  unsigned dodgeFrames;     //number of frames
  AEGfxVertexList* idleMesh;    //1x1
  AEGfxVertexList* animMesh;    //4x2
  float animDurs[4];       //attack, block, run, dodge
  AEVec2 scales[4];        //array of scales for each direction (front, right, back, left)
	ItemType type;		       //item type
	float resistance;	       //% amount of damage protection effectiveness [0-100]
	float damageStatBoost;   //amount to boost human damage by, unless its a trap then its trap attack damage
	float speedStatBoost;    //amount to boost human speed by
	float healthStatBoost;   //amount to boost human health by
	float delay;		         //trap attack delay
	float range;		         //weapon/trap attack range
  Items id;                //item id
  int quality;          //quality level of the item
}Item;

typedef struct Human //HUMAN STRUCTURE FOR ALL HUMANS [inherits from Object type]
{
    ObjectPtr obj;			        //object pointer
    unsigned isAttacking;	  //is currently attacking [timer]
    unsigned isBlocking; 	  //is currently blocking [timer]
    unsigned isRunning;		  //is currently running [timer]
    unsigned isHurt;			  //was hurt in this frame [timer]
    unsigned isDead;			  //is dead [timer]
    unsigned isDodging;		  //is this object performing a dodge in this frame [timer]
    unsigned actionDelay;   //human cant attack during this time [timer]
    unsigned kills;         //number of kills human got this round
    float health;			          //currentHealth
    float previousHealth;			  //health before you got hit
    bool canDodge;              //can this human dodge
    bool killLeader;            //is this human the kill leader?
    bool showHealth;				  //set true to show health bar
    float staminaMax;
    float stamina;
    bool showStamina;
    float attack;			          //attack damage
    float speed;			          //movement speed
    float dodgeSpeed;           //dodging speed
    float blockResist;          //% of damage reduction when blocking
    HumanPtr targets[MAXOBJECTAMOUNT]; //humans this human can attack
    AIFightFunctionPtr fightStyle; //function pointer to AI's fight style
    int attackFocus;               //AI attack focus if fightFocus is AIFightCustom
    int blockFocus;                //AI block focus if fightFocus is AIFightCustom
    int dodgeInRangeFocus;         //AI dodge in range focus if fightFocus is AIFightCustom
    int runFocus;                  //AI run to player focus if fightFocus is AIFightCustom
    int dodgeOutOfRangeFocus;      //AI dodge not in range focus if fightFocus is AIFightCustom
    FaceDir dir;                //direction object is facing
    FaceDir dodgeDir;           //direction object is dodging
    InventoryWornPtr inventory; //inventory full of item slots
    HumanState stateCurr;       //current state
    HumanState stateNext;       //next state
}Human, *HumanPtr;

typedef struct Player //PLAYER STRUCTURE [inherits from Human type]
{
    Human human; //pointer to human structure
    unsigned controllerID;  //id of controller that controls this human
}Player, *PlayerPtr;

typedef struct Enemy //ENEMY STRUCTURE [inherits from Human type]
{
    Human human;		 //human structure
    HumanPtr target; //human this enemy is attacking
}Enemy, *EnemyPtr;

#pragma endregion PRIVATE_STRUCTURES

#pragma region PUBLIC_FUNCTION_DEFINITIONS

#pragma region GETTERS

PhysicsPtr ObjectGetPhysics(ObjectPtr obj)
{
	if (obj)
		return obj->physics;

	return NULL;
}

TransformPtr ObjectGetTransform(ObjectPtr obj)
{
	if (obj)
		return obj->transform;

	return NULL;
}

SpritePtr ObjectGetSprite(ObjectPtr obj)
{
	if (obj)
		return obj->sprite;

	return NULL;
}

SpriteSourcePtr ObjectGetSpriteSource(ObjectPtr obj)
{
    if (obj)
        return SpriteGetSpriteSource(obj->sprite);

    return NULL;
}

AnimationPtr ObjectGetAnimation(ObjectPtr obj)
{
    if (obj)
    {
        return obj->animation;
    }
    return NULL;
}

ColliderPtr ObjectGetCollider(ObjectPtr obj)
{
	if (obj)
		return obj->collider;

	return NULL;
}

HumanPtr ObjectGetHuman(ObjectPtr obj)
{
    if (obj)
        return obj->human;

    return NULL;
}

ObjectType ObjectGetTag(ObjectPtr obj)
{
	if (obj)
		return obj->tag;

	return 0;
}

DrawLayer ObjectGetDrawLayer(ObjectPtr obj)
{
    if (obj)
        return obj->drawLayer;
    return 0;
}

const char* ObjectGetName(ObjectPtr obj)
{
	if (obj)
		return obj->name;

	return "\0";
}

ItemType ItemGetType(ItemPtr item)
{
	if(item)
		return item->type;

	return 0;
}

float ItemGetResistance(ItemPtr item)
{
	if(item)
		return item->resistance;

	return 0.0f;
}

int HumanGetBool(HumanPtr human,int attacking, int running, int hurt, int dead, int dodging, int blocking)
{
    if (human)
    {
        if (attacking)
            return human->isAttacking;
        else if (running)
            return human->isRunning;
        else if (hurt)
            return human->isHurt;
        else if (dead)
            return human->isDead;
        else if (dodging)
            return human->isDodging;
        else if (blocking)
            return human->isBlocking;
    }
	return 0;
}

int HumanGetActive(HumanPtr human)
{
    if(human)
        return human->isAttacking + human->isRunning + human->isDodging + human->isBlocking;

    return 0;
}

int HumanGetActionDelay(HumanPtr human)
{
    if (human)
        return human->actionDelay;

    return 0;
}

float HumanGetHealth(HumanPtr human)
{
	if (human)
		return human->health;

	return 0.0f;
}

float ObjectGetAttackDamage(HumanPtr human, ItemPtr item)
{
	if (human && item)
		return human->attack + item->damageStatBoost;
	else if (human)
		return human->attack;
	else if (item)
		return item->damageStatBoost;

	return 0.0f;
}

float HumanGetSpeed(HumanPtr human)
{
	if (human)
		return human->speed + ItemGetSpeedBoost((ItemGetByID(WornInventoryGetId(human->inventory, slotLegs))));

	return 0.0f;
}

float HumanGetDodgeSpeed(HumanPtr human)
{
    if (human)
        return human->dodgeSpeed + ItemGetSpeedBoost((ItemGetByID(WornInventoryGetId(human->inventory, slotLegs))));

    return 0;
}

float ItemGetSpeedBoost(ItemPtr item)
{
    if (item)
        return item->speedStatBoost;
    return 0.0f;
}

float ItemGetHealthBoost(ItemPtr item)
{
    if (item)
        return item->healthStatBoost;
    return 0.0f;
}

float HumanGetBlockResist(HumanPtr human)
{
    if (human)
        return human->blockResist + ItemGetByID(DefaultShield)->resistance;

    return 0;
}

FaceDir HumanGetFaceDir(HumanPtr human)
{
	if (human)
		return human->dir;

	return 0;
}

FaceDir HumanGetDodgeDir(HumanPtr human)
{
	if (human)
		return human->dodgeDir;

	return 0;
}

//Gets a facedir with a specified facedir and offset
FaceDir FaceDirGetWithOffset(const FaceDir dir, const int offset)
{
    if (dir + offset > FaceDirMAX)
        return dir + offset - FaceDirMAX;
    else if (dir + offset < right)
        return dir + offset + FaceDirMAX;
    else if (dir + offset == FaceDirMAX)
        return dir - offset;
    else
        return dir + offset;
}

void HumanGetArmors(HumanPtr human, ItemPtr* outHead, ItemPtr* outBody, ItemPtr* outLegs)
{
	if (human)
	{
		if (outHead)
			*outHead = ItemGetByID(WornInventoryGetId(human->inventory, slotHead));
		if (outBody)
			*outBody = ItemGetByID(WornInventoryGetId(human->inventory, slotBody));
		if (outLegs)
			*outLegs = ItemGetByID(WornInventoryGetId(human->inventory, slotLegs));
	}
}

InventoryWornPtr HumanGetInventoryWorn(HumanPtr human)
{
    if (human)
        return human->inventory;

    return NULL;
}

ObjectPtr ObjectGetObject(HumanPtr human, ItemPtr item, PlayerPtr player, EnemyPtr enemy)
{
    if (human)
        return human->obj;
    else if (item)
        return item->obj;
    else if (player)
        return player->human.obj;
    else if (enemy)
        return enemy->human.obj;

	return NULL;
}

HumanPtr HumanGetHuman(PlayerPtr player, EnemyPtr enemy)
{
	if (player)
		return &player->human;
	else if (enemy)
		return &enemy->human;

	return NULL;
}

float ItemGetDelay(ItemPtr item)
{
	if (item)
		return item->delay;

	return 0.0f;
}

ItemPtr HumanGetWeapon(HumanPtr human)
{
    if (human)
        return ItemGetByID(WornInventoryGetId(human->inventory, slotWeapon));

	return NULL;
}

float ItemGetRange(ItemPtr item)
{
	if (item)
		return item->range;

	return 0.0f;
}

HumanPtr EnemyGetTarget(EnemyPtr enemy)
{
    if (enemy)
        return enemy->target;
    return NULL;
}

void HumanGetFightFocuses(HumanPtr human, int* outAttack, int* outBlock, int* outDodgeInRange, int* outRunToTarget, int* outDodgeOutOfRange)
{
    if (human)
    {
        *outAttack = human->attackFocus;
        *outBlock = human->blockFocus;
        *outDodgeInRange = human->dodgeInRangeFocus;
        *outRunToTarget = human->runFocus;
        *outDodgeOutOfRange = human->dodgeOutOfRangeFocus;
    }
}

unsigned HumanGetKillCount(HumanPtr human)
{
    if (human)
        return human->kills;
    return 0;
}

bool HumanGetCanDodge(HumanPtr human)
{
    if (human)
        return human->canDodge;
    return false;
}

unsigned PlayerGetControllerID(PlayerPtr player)
{
    if (player)
        return player->controllerID;
    return 0;
}

HumanState HumanGetNextState(HumanPtr human)
{
    if (human)
        return human->stateNext;
    return 0;
}

HumanState HumanGetCurrentState(HumanPtr human)
{
    if (human)
        return human->stateCurr;
    return 0;
}

const char* HumanGetName(HumanPtr human)
{
	if (human)
		return human->obj->name;
	return 0;
}

bool HumanIsPlayer(HumanPtr human)
{
    if (human)
        return human->obj->tag == PlayerTag || human->obj->tag == Player2Tag;

    return false;
}

//gets the quality of the item
int ItemGetQuality(ItemPtr item)
{
	if (item)
	{
		return item->quality;
	}
	return 0;
}

#pragma endregion

#pragma region SETTERS

void ObjectSetPhysics(PhysicsPtr physics, ObjectPtr obj)
{
    if (obj)
    {
        obj->physics = physics;
    }
}

void ObjectSetTransform(TransformPtr transform, ObjectPtr obj)
{
    if (obj)
        obj->transform = transform;
}

void ObjectSetSprite(SpritePtr sprite, ObjectPtr obj)
{
    if (obj)
    {
        obj->sprite = sprite;
    }
}

void ObjectSetCollider(ObjectPtr obj, ColliderPtr col)
{
	if (obj)
		obj->collider = col;
}

void ObjectSetHuman(ObjectPtr obj, HumanPtr human)
{
    if (obj)
        obj->human = human;
}

void ObjectSetTag(ObjectType tag, ObjectPtr obj)
{
	if (tag)
	{
		if (obj)
			obj->tag = tag;
	}
}

void ObjectSetDrawLayer(ObjectPtr obj, DrawLayer drawLayer)
{
    if (obj)
        obj->drawLayer = drawLayer;
}

void ObjectSetName(const char* name, ObjectPtr obj)
{
	if (name)
	{
		if (obj)
			obj->name = name;
	}
}

void ItemSetType(ItemPtr item, ItemType type)
{
	if (item)
		item->type = type;
}

void ItemSetResistance(ItemPtr item, float resistance)
{
	if (item)
		item->resistance = resistance;
}

void HumanSetBoolOn(HumanPtr human, int attacking, int running, int hurt, int dead, int dodging, int blocking)
{
	if (human)
	{
		if (attacking)
			human->isAttacking = attacking;
		if (running)
			human->isRunning = running;
		if (hurt)
			human->isHurt = hurt;
		if (dead)
			human->isDead = dead;
		if (dodging)
			human->isDodging = dodging;
		if (blocking)
			human->isBlocking = blocking;
	}
}

void HumanSetBoolOff(HumanPtr human, int attacking, int running, int hurt, int dead, int dodging, int blocking)
{
	if (human)
	{
		if (attacking)
			human->isAttacking = 0;
		if (running)
			human->isRunning = 0;
		if (hurt)
			human->isHurt = 0;
		if (dead)
			human->isDead = 0;
		if (dodging)
			human->isDodging = 0;
		if (blocking)
			human->isBlocking = 0;

	}
}

void HumanSetBool(HumanPtr human, int attacking, int running, int hurt, int dead, int dodging, int blocking)
{
	if (human)
	{
		if (attacking)
			human->isAttacking = attacking;
		else
			human->isAttacking = 0;
		if (running)
			human->isRunning = running;
		else
			human->isRunning = 0;
		if (hurt)
			human->isHurt = hurt;
		else
			human->isHurt = 0;
		if (dead)
			human->isDead = dead;
		else
			human->isDead = 0;
		if (dodging)
			human->isDodging = dodging;
		else
			human->isDodging = 0;
		if (blocking)
			human->isBlocking = blocking;
		else
			human->isBlocking = 0;
	}
}

void HumanSubBool(HumanPtr human, int attacking, int running, int hurt, int dead, int dodging, int blocking)
{
    if (human)
    {
        human->isAttacking -= attacking;
        human->isRunning -= running;
        human->isHurt -= hurt;
        human->isDead -= dead;
        human->isDodging -= dodging;
        human->isBlocking -= blocking;
    }
}

void HumanAddBool(HumanPtr human, int attacking, int running, int hurt, int dead, int dodging, int blocking)
{
    if (human)
    {
        human->isAttacking += attacking;
        human->isRunning += running;
        human->isHurt += hurt;
        human->isDead += dead;
        human->isDodging += dodging;
        human->isBlocking += blocking;
    }
}

void HumanSetActionDelay(HumanPtr human, int actionDelay)
{
    if (human)
        human->actionDelay = actionDelay;
}

void HumanSetHealth(HumanPtr human, float health)
{
	if (human)
	{
		human->health = health;
	}
}

void HumanSetPreviousHealth(HumanPtr human, float previousHealth)
{
	human->previousHealth = previousHealth;
}

//set if you are displaying the humans health or not
void HumanSetShowHealth(HumanPtr human, bool value)
{
	human->showHealth = value;
}
//set if you are displaying the humans stamina or not
void HumanSetShowStamina(HumanPtr human, bool value)
{
	human->showStamina = value;
}

void ObjectSetAttackDamage(HumanPtr human, ItemPtr item, float attackDamage)
{
	if (human)
		human->attack = attackDamage;
	if (item)
		item->damageStatBoost = attackDamage;
}

void HumanSetSpeed(HumanPtr human, float speed)
{
	if (human)
		human->speed = speed;
}

void HumanSetDodgeSpeed(HumanPtr human, float dodgeSpeed)
{
    if (human)
        human->dodgeSpeed = dodgeSpeed;
}

int HumanSetFaceDir(HumanPtr human, FaceDir direction)
{
    if (human)
    {
        human->dir = direction;
        ItemPtr head = ItemGetByID(WornInventoryGetId(human->inventory, slotHead));
        ItemPtr body = ItemGetByID(WornInventoryGetId(human->inventory, slotBody));
        ItemPtr legs = ItemGetByID(WornInventoryGetId(human->inventory, slotLegs));
        ItemPtr sword = ItemGetByID(WornInventoryGetId(human->inventory, slotWeapon));
        ItemPtr shield = ItemGetByID(WornInventoryGetId(human->inventory, slotShield));
        int index = 0; //frbl
        float rotation = 0.0f; //rotation of everything except sword
        float swordRot = 0.0f; //rotation of sword
        switch (direction)
        {
        case right:
            index = 1;
            if(sword)
                ObjectSetDrawLayer(sword->obj, DrawBody);
            if(shield)
                ObjectSetDrawLayer(shield->obj, DrawBody);
            if (human->isAttacking)
              swordRot = PI4;
            break;
        case upright:
          index = 2;
          if (sword)
            ObjectSetDrawLayer(sword->obj, DrawLegs);
          if (shield)
            ObjectSetDrawLayer(shield->obj, DrawLegs);
          if (human->isAttacking)
            swordRot = -PI4;
          break;
        case up:
            index = 2;
            if(sword)
                ObjectSetDrawLayer(sword->obj, DrawLegs);
            if (shield)
                ObjectSetDrawLayer(shield->obj, DrawLegs);
            if (human->isAttacking)
              swordRot = PI2;
            break;
        case downright:
          index = 0;
          if (sword)
            ObjectSetDrawLayer(sword->obj, DrawBody);
          if (shield)
            ObjectSetDrawLayer(shield->obj, DrawBody);
          if (human->isAttacking)
            swordRot = PI2;
          break;
        case down:
            index = 0;
            if(sword)
                ObjectSetDrawLayer(sword->obj, DrawBody);
            if(shield)
                ObjectSetDrawLayer(shield->obj, DrawBody);
            if (human->isAttacking)
              swordRot = PI4;
            break;
        case upleft:
            index = 2;
            if(sword)
                ObjectSetDrawLayer(sword->obj, DrawLegs);
            if (shield)
                ObjectSetDrawLayer(shield->obj, DrawLegs);
            if (human->isAttacking)
              swordRot = PI2;
            break;
        case left:
            index = 3;
            if(sword)
                ObjectSetDrawLayer(sword->obj, DrawSword);
            if (shield)
                ObjectSetDrawLayer(shield->obj, DrawSword);
            if (human->isAttacking)
              swordRot = -PI4;
            break;
        case downleft:
            index = 0;
            if(sword)
                ObjectSetDrawLayer(sword->obj, DrawBody);
            if (shield)
                ObjectSetDrawLayer(shield->obj, DrawBody);
            if (human->isAttacking)
              swordRot = -PI4;
            break;
        case FaceDirMAX:
            rotation = PI2;
            index = 0;
            if(sword)
                ObjectSetDrawLayer(sword->obj, DrawBody);
            if (shield)
                ObjectSetDrawLayer(shield->obj, DrawLegs);
            break;
        }
        if (head)
        {
            TransformSetRotation(head->obj->transform, rotation);
            TransformSetScale(head->obj->transform, &head->scales[index]);
        }
        if (body)
        {
            TransformSetRotation(body->obj->transform, rotation);
            TransformSetScale(body->obj->transform, &body->scales[index]);
        }
        if (legs)
        {
            TransformSetRotation(legs->obj->transform, rotation);
            TransformSetScale(legs->obj->transform, &legs->scales[index]);
        }
        if (sword)
        {
            TransformSetRotation(sword->obj->transform, swordRot);
            TransformSetScale(sword->obj->transform, &sword->scales[index]);
        }
        if (shield)
        {
            TransformSetRotation(shield->obj->transform, rotation);
            TransformSetScale(shield->obj->transform, &shield->scales[index]);
        }
        //TransformSetScale(human->obj->transform, &body->scales[index]);

        switch (human->stateNext)
        {
        case HSknockedback:
          /*fallthrough*/
        case HSidle:
            if(head)
                AnimationSetSpriteSource(head->obj->animation, head->idleSS[index]);
            if(body)
                AnimationSetSpriteSource(body->obj->animation, body->idleSS[index]);
            if(legs)
                AnimationSetSpriteSource(legs->obj->animation, legs->idleSS[index]);
            if(sword)
                AnimationSetSpriteSource(sword->obj->animation, sword->idleSS[index]);
            if(shield)
                AnimationSetSpriteSource(shield->obj->animation, shield->idleSS[index]);
            break;
        case HSattack:
            if(head)
                AnimationSetSpriteSource(head->obj->animation,   head->attackSS[index]);
            if(body)
                AnimationSetSpriteSource(body->obj->animation,   body->attackSS[index]);
            if(legs)
                AnimationSetSpriteSource(legs->obj->animation,   legs->attackSS[index]);
            if(sword)
                AnimationSetSpriteSource(sword->obj->animation, sword->attackSS[index]);
            if (shield)
                AnimationSetSpriteSource(shield->obj->animation, shield->attackSS[index]);
            break;
        case HSblock:
            if(head)
                AnimationSetSpriteSource(head->obj->animation,   head->blockSS[index]);
            if(body)
                AnimationSetSpriteSource(body->obj->animation,   body->blockSS[index]);
            if(legs)
                AnimationSetSpriteSource(legs->obj->animation,   legs->blockSS[index]);
            if(sword)
                AnimationSetSpriteSource(sword->obj->animation, sword->blockSS[index]);
            if (shield)
                AnimationSetSpriteSource(shield->obj->animation, shield->blockSS[index]);
            break;
        case HSrun:
            if(head)
                AnimationSetSpriteSource(head->obj->animation,   head->runSS[index]);
            if(body)
                AnimationSetSpriteSource(body->obj->animation,   body->runSS[index]);
            if(legs)
                AnimationSetSpriteSource(legs->obj->animation,   legs->runSS[index]);
            if(sword)
                AnimationSetSpriteSource(sword->obj->animation, sword->runSS[index]);
            if (shield)
                AnimationSetSpriteSource(shield->obj->animation, shield->runSS[index]);
            break;
        case HSdodge:
            if(head)
                AnimationSetSpriteSource(head->obj->animation,  head->dodgeSS[index]);
            if(body)
                AnimationSetSpriteSource(body->obj->animation,  body->dodgeSS[index]);
            if(legs)
                AnimationSetSpriteSource(legs->obj->animation,  legs->dodgeSS[index]);
            if(sword)
                AnimationSetSpriteSource(sword->obj->animation,sword->dodgeSS[index]);
            if (shield)
                AnimationSetSpriteSource(shield->obj->animation, shield->dodgeSS[index]);
            break;
        }

        human->stateCurr = human->stateNext;
        return index;
    }
    return 0;
}

void HumanSetDodgeDir(HumanPtr human, FaceDir direction)
{
	if (human)
		human->dodgeDir = direction;
}

void HumanSetArmors(HumanPtr human, Items head, Items body, Items legs)
{
	if (human)
	{
        WornInventorySetId(human->inventory, head);
        WornInventorySetId(human->inventory, body);
        WornInventorySetId(human->inventory, legs);
	}
}

void HumanSetInventoryWorn(HumanPtr human, InventoryWornPtr inventory)
{
    if (human)
        human->inventory = inventory;
}

void HumanSetWeapon(HumanPtr human, Items weapon)
{
	if (human)
      WornInventorySetId(human->inventory, weapon);
}

void ItemSetDelay(ItemPtr item, float delay)
{
	if (item)
		item->delay = delay;
}

void ItemSetRange(ItemPtr item, float range)
{
	if (item)
		item->range = range;
}

void HumanSetTargets(HumanPtr human, HumanPtr targets[MAXOBJECTAMOUNT])
{
	if (human && targets)
	{
      for (int i = 0; i < MAXOBJECTAMOUNT; ++i)
      {
          if(targets[i] != human)
            human->targets[i] = targets[i];
      }
	}
}

void HumanAddTarget(HumanPtr human, HumanPtr target)
{
    if (!human)
      return;

    for (int i = 0; i < MAXOBJECTAMOUNT; ++i)
    {
        if (!human->targets[i])
        {
            human->targets[i] = target;
            return;
        }
    }
}

void HumanRemoveTarget(HumanPtr human, HumanPtr target)
{
    if (human)
    {
        for (int i = 0; i < MAXOBJECTAMOUNT; ++i)
        {
            if (human->targets[i] == target)
            {
                human->targets[i] = NULL;
                return;
            }
        }
    }
}

int EnemyRetarget(EnemyPtr enemy, HumanPtr target)
{
    if (enemy)
    {
        if (target)
        {
            enemy->target = target;
            return -1; //-1 means target was set manually
        }
        HumanPtr targets[MAXOBJECTAMOUNT] = { NULL };
        int targetCount = 0;
        for (int i = 0; i < MAXOBJECTAMOUNT; ++i)
        {
            if (enemy->human.targets[i])
            {
                if (enemy->human.targets[i]->isDead)
                    enemy->human.targets[i] = NULL;
                else
                {
                    targets[targetCount] = enemy->human.targets[i];
                    ++targetCount;
                }
            }
        }
        enemy->target = targets[RandomRange(0, targetCount)];
        return targetCount;
    }
    return 0;
}

void HumanResetTargets(HumanPtr human)
{
    if (human)
    {
        for (int i = 0; i < MAXOBJECTAMOUNT; ++i)
        {
            human->targets[i] = NULL;
        }
    }
}

void HumanSetFightFocuses(HumanPtr human, int attack, int block, int dodgeInRange, int dodgeOutOfRange, int runToTarget)
{
    if (human)
    {
        human->attackFocus = attack;
        human->blockFocus = block;
        human->dodgeInRangeFocus = dodgeInRange;
        human->dodgeOutOfRangeFocus = dodgeOutOfRange;
        human->runFocus = runToTarget;
    }
}

void HumanSetNextState(HumanPtr human, HumanState HSstate)
{
    if (human)
        human->stateNext = HSstate;
}

void HumanSetName(HumanPtr human, const char* name)
{
	if (human)
		human->obj->name = name;
}

void HumanSetKillLeader(HumanPtr human, bool killLeader)
{
    if (human)
        human->killLeader = killLeader;
}

void PlayerSetControllerID(PlayerPtr player, unsigned id)
{
    if (player)
        player->controllerID = id;
}

#pragma endregion

#pragma region OBJECT_HANDLING

//Creates an object with a name, tag, physics, sprite, animation, and transform
//You will need to set SpriteSource and Mesh manually
ObjectPtr CreateObject(const char* name, ObjectType tag)
{
	ObjectPtr object = (ObjectPtr)calloc(1, sizeof(Object));

	if (object)
	{
		object->transform = TransformCreate(0.0f, 0.0f);
    AEMtx33Identity(TransformGetMatrix(object->transform));
		object->sprite = SpriteCreate(name);
		object->physics = PhysicsCreate();
		object->name = name;
		object->tag = tag;
		//object->collider = ColliderCreate();
    object->animation = AnimationCreate(object->sprite);

		//if (object->collider && object->transform)
		//{
		//	ColliderSetParent(object->collider, object);
		//	ColliderSetTransform(object->collider, TransformCreate(0.0f, 0.0f));
		//}
	}

	return object;
}

//Frees Object and attached transform ,sprite, animation, and physics
void FreeObject(ObjectPtr* obj)
{
	if (obj)
	{
      if ((*obj)->transform)
      {
          TransformFree(&(*obj)->transform);
          (*obj)->transform = NULL;
      }
      if ((*obj)->sprite)
      {
          SpriteFree(&(*obj)->sprite);
          (*obj)->sprite = NULL;
      }
      if ((*obj)->physics)
      {
          PhysicsFree(&(*obj)->physics);
          (*obj)->physics = NULL;
      }
      if ((*obj)->animation)
      {
          AnimationFree(&(*obj)->animation);
          (*obj)->animation = NULL;
      }
      if ((*obj)->collider)
      {
          ColliderDelete(&(*obj)->collider);
          (*obj)->collider = NULL;
      }
    
		free(*obj);
		*obj = NULL;
	}
}

//Creates an item with everything it will ever need, ever
ItemPtr CreateItem(const char* name, ObjectType tag, float damageResistance, float damageBoost, float healthBoost, float speedBoost, float delay, float range,
    ItemType type, AEVec2 scales[4], const char* frblIdle[4], AEGfxVertexList * mesh1x1, DrawLayer drawLayer, unsigned idleFrames, unsigned runFrames, unsigned attackFrames,
    unsigned blockFrames, unsigned dodgeFrames, AEGfxVertexList* mesh4x2, float abrdDurs[4], const char* frblRun[4], const char* frblAttack[4], const char* frblDodge[4],
    const char* frblBlock[4], Items id, int quality)
{
	ItemPtr item = (ItemPtr)calloc(1, sizeof(Item));

	if (item)
	{
		item->obj = CreateObject(name, tag);
		item->resistance = damageResistance;
    item->damageStatBoost = damageBoost;
    item->healthStatBoost = healthBoost;
    item->speedStatBoost = speedBoost;
    item->delay = delay;
    item->range = range;
		item->type = type;
    item->id = id;
	item->quality = quality;

    for (int i = 0; i < 4; ++i)
    {
        if (idleFrames == 1)
            item->idleSS[i] = SpriteSourceCreate(1, 1, AEGfxTextureLoad(frblIdle[i]));
        else if(idleFrames == 8)
            item->idleSS[i] = SpriteSourceCreate(4, 2, AEGfxTextureLoad(frblIdle[i]));
        if(attackFrames==1)
            item->attackSS[i] = SpriteSourceCreate(1, 1, AEGfxTextureLoad(frblAttack[i]));
        else if(attackFrames==8)
            item->attackSS[i] = SpriteSourceCreate(4, 2, AEGfxTextureLoad(frblAttack[i]));
        if(runFrames==1)
            item->runSS[i] = SpriteSourceCreate(1, 1, AEGfxTextureLoad(frblRun[i]));
        else if(runFrames==8)
            item->runSS[i] = SpriteSourceCreate(4, 2, AEGfxTextureLoad(frblRun[i]));
        if(blockFrames==1)
            item->blockSS[i] = SpriteSourceCreate(1, 1, AEGfxTextureLoad(frblBlock[i]));
        else if(blockFrames==8)
            item->blockSS[i] = SpriteSourceCreate(4, 2, AEGfxTextureLoad(frblBlock[i]));
        if(dodgeFrames==1)
            item->dodgeSS[i] = SpriteSourceCreate(1, 1, AEGfxTextureLoad(frblDodge[i]));
        else if(dodgeFrames==8)
            item->dodgeSS[i] = SpriteSourceCreate(4, 2, AEGfxTextureLoad(frblDodge[i]));
        item->scales[i] = scales[i];
        item->animDurs[i] = abrdDurs[i];
    }

    item->attackFrames = attackFrames;
    item->blockFrames = blockFrames;
    item->dodgeFrames = dodgeFrames;
    item->runFrames = runFrames;

    TransformSetScale(item->obj->transform, &item->scales[0]);
    SpriteSetSpriteSource(item->obj->sprite, item->idleSS[0]);
    SpriteSetMesh(item->obj->sprite, mesh1x1);
    item->idleMesh = mesh1x1;
    item->animMesh = mesh4x2;
    item->obj->drawLayer = drawLayer;
	}

	return item;
}

//Creates a human with health, attack, speed, and Object
HumanPtr CreateHuman(const char* name, ObjectType tag,float health, float stamina, float attack, float speed, float dodgeSpeed, float blockResist, bool showHealth, bool showStamina)
{
	HumanPtr human = (HumanPtr)calloc(1, sizeof(Human));

	if (human)
	{
		human->obj = CreateObject(name, tag);
    human->obj->collider = ColliderCreate();
    human->obj->human = human;
		human->health = health;
		human->previousHealth = health;
		human->showHealth = showHealth;
		human->staminaMax = stamina;
		human->stamina = stamina;
		human->showStamina = showStamina;
		human->attack = attack;
		human->speed = speed;
		human->blockResist = blockResist;
		human->dodgeSpeed = dodgeSpeed;
		human->inventory = createWornInventory();
    //human->healthBar = CreateObject("Healthbar", ObjTag);
    if (human->obj->collider && human->obj->transform)
    {
      ColliderSetParent(human->obj->collider, human->obj);
      ColliderSetTransform(human->obj->collider, TransformCreate(0.0f, 0.0f));
    }
	}

	return human;
}

//Frees a human by freeing the base human, Object
void FreeHuman(HumanPtr* human)
{
	if (human)
	{
		if ((*human)->obj)
		{
        FreeObject(&(*human)->obj);
        (*human)->obj = NULL;
		}
    //if ((*human)->healthBar)
    //{
    //    FreeObject(&(*human)->healthBar);
    //    (*human)->healthBar = NULL;
    //}
    for (int i = 0; i < MAXOBJECTAMOUNT; ++i)
    {
        (*human)->targets[i] = NULL;
    }
		free(*human);
		*human = NULL;
	}
}

//Creates an empty player
PlayerPtr CreatePlayer(const char* name, ObjectType tag, float health, float stamina, float attack, float speed, float dodgeSpeed, float blockResist, bool showHealth, bool showStamina)
{
	PlayerPtr player = (PlayerPtr)calloc(1, sizeof(Player));

	if (player)
	{
    player->human.obj = CreateObject(name, tag);
    player->human.obj->collider = ColliderCreate();
    player->human.obj->human = &player->human;
    player->human.health = health;
    player->human.previousHealth = health;
    player->human.showHealth = showHealth;
    player->human.staminaMax = stamina;
    player->human.stamina = stamina;
    player->human.showStamina = showStamina;
    player->human.attack = attack;
    player->human.speed = speed;
    player->human.blockResist = blockResist;
    player->human.dodgeSpeed = dodgeSpeed;
    player->human.inventory = createWornInventory();
    player->controllerID = 0;
    if (player->human.obj->collider && player->human.obj->transform)
    {
      ColliderSetParent(player->human.obj->collider, player->human.obj);
      ColliderSetTransform(player->human.obj->collider, TransformCreate(0.0f, 0.0f));
    }
	}

	return player;
}

//Frees a player
void FreePlayer(PlayerPtr* player)
{
	if (player)
	{
		free(*player);
		*player = NULL;
	}
}

//Creates an enemy with everything it will need except armor and weapon
EnemyPtr CreateEnemy(const char* name, ObjectType tag, float health, float stamina, float attack, float speed, float dodgeSpeed, float blockResist, AIFightFunctionPtr fightStyle,
    int blockFocus, int attackFocus, int dodgeinRangeFocus, int dodgeNotInRangeFocus, int runFocus, bool showHealth, bool showStamina)
{
	EnemyPtr enemy = (EnemyPtr)calloc(1, sizeof(Enemy));

	if (enemy)
	{
    //enemy->human = *CreateHuman(name, tag, health, attack, speed, dodgeSpeed, blockResist);
    enemy->human.obj = CreateObject(name, tag);
    enemy->human.obj->collider = ColliderCreate();
    enemy->human.obj->human = &enemy->human;
    enemy->human.health = health;
    enemy->human.showHealth = showHealth;
    enemy->human.staminaMax = stamina;
    enemy->human.stamina = stamina;
	  enemy->human.previousHealth = health;
    enemy->human.attack = attack;
    enemy->human.speed = speed;
    enemy->human.blockResist = blockResist;
    enemy->human.dodgeSpeed = dodgeSpeed;
    enemy->human.inventory = createWornInventory();
    enemy->human.attackFocus = attackFocus;
    enemy->human.blockFocus = blockFocus;
    enemy->human.dodgeInRangeFocus = dodgeinRangeFocus;
    enemy->human.dodgeOutOfRangeFocus = dodgeNotInRangeFocus;
    enemy->human.fightStyle = fightStyle;
    enemy->human.runFocus = runFocus;
    enemy->human.showHealth = showHealth;
    enemy->human.showStamina = showStamina;

    if (enemy->human.obj->collider && enemy->human.obj->transform)
    {
      ColliderSetParent(enemy->human.obj->collider, enemy->human.obj);
      ColliderSetTransform(enemy->human.obj->collider, TransformCreate(0.0f, 0.0f));
    }
	}

	return enemy;
}

//frees an enemy
void FreeEnemy(EnemyPtr* enemy)
{
	if (enemy)
	{
    for (int i = 0; i < MAXOBJECTAMOUNT; ++i)
    {
        (*enemy)->human.targets[i] = NULL;
    }
    if ((*enemy)->human.obj)
    {
        FreeObject(&(*enemy)->human.obj);
        (*enemy)->human.obj = NULL;
    }
		free(*enemy);
		*enemy = NULL;
	}
}

//create a damage indicator popup
//DamagePopupPtr CreateDamagePopup(const char* pngFile)
//{
//    
//}

#pragma endregion

#pragma region OBJECT_DRAWING

// Draw any visible components attached to the game object.
void DrawObject(ObjectPtr Object)
{
	if (Object)
		SpriteDraw(Object->sprite, Object->transform);
}

#pragma region AMERICA

// Draw the humans health bar
void HumanDrawHealth(HumanPtr human)
{
    if (!human)
        return;
	if (!strcmp(human->obj->name, "player"))
	{
		DrawEmptyRect(-700, 490, 401, 21);

		if (human->health <= human->previousHealth)
		{
			human->previousHealth = human->previousHealth - 0.10f;
			DrawRedRect(-700 - (200 - (human->previousHealth * 2)), 490, human->previousHealth * 4, 20);
		}

		DrawFilledRect(-700 - (200 - (human->health * 2)), 490, human->health * 4, 20);
	}
	else
	{
		DrawEmptyRect(500, 490, 401, 21);

		if (human->health <= human->previousHealth)
		{
			human->previousHealth = human->previousHealth - 0.10f;
			DrawRedRect(500 - (200 - (human->previousHealth * 2)), 490, human->previousHealth * 4, 20);
		}
		DrawFilledRect(500 - (200 - (human->health * 2)), 490, human->health * 4, 20);
	}
}

// Draw the humans stamina bar
void HumanDrawStamina(HumanPtr human)
{
    if (!human)
        return;

	// If it is the player
	if (!strcmp(human->obj->name, "player"))
	{
		//draw the stamina bar container
		DrawEmptyRect(-700, 450, 401, 21);

		//if stamina is no full
		if (human->stamina < human->staminaMax)
		{
			//make the bar lighter
			AEGfxSetBlendMode(AE_GFX_BM_ADD);
		}
		//draw how much stamina the player has
		DrawBlueRect(-700 - (200 - (human->stamina * 2)), 450, human->stamina * 4, 20);
	}
	else
	{
		DrawEmptyRect(500, 450, 401, 21);
		if (human->stamina < human->staminaMax)
		{
			AEGfxSetBlendMode(AE_GFX_BM_ADD);
		}
		DrawBlueRect(500 - (200 - (human->stamina * 2)), 450, human->stamina * 4, 20);
	}
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
}

#pragma endregion

#pragma region ITEM_DRAWER

void InitItemDrawer()
{
    requeueI = SpriteCreate("");
    requeueINext = SpriteCreate("");
    requeueT = TransformCreate(0.0f, 0.0f);
    requeueTNext = TransformCreate(0.0f, 0.0f);
    requeueSS = SpriteSourceCreate(1, 1, NULL);
    requeueSSNext = SpriteSourceCreate(1, 1, NULL);
    for (int i = 0; i < DrawLayerMax; ++i)
    {
        for (int j = 0; j < ITEM_LIST_SIZE; ++j)
        {
            TransformList[i][j] = TransformCreate(0.0f, 0.0f);
            SpriteSourceList[i][j] = SpriteSourceCreate(1, 1, NULL);
            SpriteList[i][j] = SpriteCreate("");
        }
    }
}

//Resets everything in ItemDrawer back to default so no items get drawn to screen (DOES NOT FREE)
void ResetItemDrawer()
{
    SpriteZero(requeueI);
    SpriteZero(requeueINext);
    TransformZero(requeueT);
    TransformZero(requeueTNext);
    SpriteSourceZero(requeueSS);
    SpriteSourceZero(requeueSSNext);
    for (int i = 0; i < DrawLayerMax; ++i)
    {
        for (int j = 0; j < ITEM_LIST_SIZE; ++j)
        {
            SpriteZero(SpriteList[i][j]);
            TransformZero(TransformList[i][j]);
            SpriteSourceZero(SpriteSourceList[i][j]);
        }
    }
}

//Frees up all memory used by Item Drawer
void FreeItemDrawer()
{
    SpriteFree(&requeueI);
    SpriteFree(&requeueINext);
    TransformFree(&requeueT);
    TransformFree(&requeueTNext);
    SpriteSourceFree(&requeueSS);
    SpriteSourceFree(&requeueSSNext);
    for (int i = 0; i < DrawLayerMax; ++i)
    {
        for (int j = 0; j < ITEM_LIST_SIZE; ++j)
        {
            TransformFree(&TransformList[i][j]);
            SpriteSourceFree(&SpriteSourceList[i][j]);
            SpriteFree(&SpriteList[i][j]);
        }
    }
}

//Queues up items for drawing, and sorts the queue
void ItemQueueForDrawing(SpritePtr item, TransformPtr transform, SpriteSourcePtr spriteSource, DrawLayer layer, bool hurt)
{
    if (item && transform)
    {
        for (int i = 0; i < ITEM_LIST_SIZE; ++i)
        {
            if (!ItemInUseList[layer][i]) //if empty slot in list
            {
                SpriteCopy(item, SpriteList[layer][i]);
                TransformCopy(transform,TransformList[layer][i]);
                SpriteSourceCopy(spriteSource, SpriteSourceList[layer][i]);
                ItemHurtList[layer][i] = hurt;
                ++ItemInUseList[layer][i];
                requeueingNext = false;
                return;
            }
            //if Y Pos of item  > item in this slot
            if (ItemInUseList[layer][i]&&
                TransformGetValueFromVec(transform, TransformPos, TransformY) >
                TransformGetValueFromVec(TransformList[layer][i], TransformPos, TransformY))
            {
                if (!requeueingNext)
                {
                    //requeue the item in this slot and place current into its place
                    TransformCopy(TransformList[layer][i], requeueT);             //copy transform from list to queue
                    SpriteSourceCopy(SpriteSourceList[layer][i], requeueSS);      //copy spritesource from list to queue
                    SpriteCopy(SpriteList[layer][i], requeueI);                   //copy item from list into queue
                    requeueHurt = ItemHurtList[layer][i];                         //copy hurt from list into queue

                    TransformCopy(transform, TransformList[layer][i]);            //copy transform into slot
                    SpriteSourceCopy(spriteSource, SpriteSourceList[layer][i]);   //copy spritesource into slot
                    SpriteCopy(item, SpriteList[layer][i]);                       //copy item into slot
                    ItemHurtList[layer][i] = hurt;                                //copy hurt into slot

                    requeueingNext = true;
                    ItemQueueForDrawing(requeueI, requeueT, requeueSS, layer, requeueHurt);    //requeue other item for drawing
                    return;
                }
                else
                {
                    //requeue the item in this slot and place current into its place
                    TransformCopy(TransformList[layer][i], requeueTNext);             //copy transform from list to queue next
                    SpriteSourceCopy(SpriteSourceList[layer][i], requeueSSNext);      //copy spritesource from list to queue next
                    SpriteCopy(SpriteList[layer][i], requeueINext);                   //copy item from list into queue next
                    requeueHurtNext = ItemHurtList[layer][i];                         //copy hurt from list into queue next

                    TransformCopy(transform, TransformList[layer][i]);            //copy transform into slot
                    SpriteSourceCopy(spriteSource, SpriteSourceList[layer][i]);   //copy spritesource into slot
                    SpriteCopy(item, SpriteList[layer][i]);                       //copy item into slot
                    ItemHurtList[layer][i] = hurt;                                //copy hurt into slot

                    requeueingNext = false;
                    ItemQueueForDrawing(requeueINext, requeueTNext, requeueSSNext, layer, requeueHurtNext);    //requeue other item for drawing
                    return;
                }
            }
        }
    }
}

//Draws all items in queue
void DrawItemsInQueue()
{
    for (int i = 0; i < DrawLayerMax; ++i)
    {
        for (int j = 0; j < ITEM_LIST_SIZE; ++j)
        {
            if (ItemInUseList[i][j])
            {
                ItemHurtList[i][j] ? AEGfxSetTintColor(.75f, 0.0f, 0.0f, 1.0f): AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
                SpriteDrawWithSpriteSource(SpriteList[i][j], TransformList[i][j], SpriteSourceList[i][j]);
                ItemInUseList[i][j] = 0;
            }
        }
    }
}

#pragma endregion

#pragma region DAMAGE_POPUP_DRAWER

//call only level load
void InitDamagePopupDrawer()
{
    damagePopupSprite = SpriteCreate("Damage Popup");
    damageTexture = AEGfxTextureLoad("Assets/Text_White.png");
    damageMesh = MeshCreateQuad(.5f, .5f, 1.0f / 16, 1.0f / 6, "Damage Popup Mesh");
    damageSS = SpriteSourceCreate(16, 6, damageTexture);
    SpriteSetMesh(damagePopupSprite, damageMesh);
    SpriteSetSpriteSource(damagePopupSprite, damageSS);
    AEVec2 popupScale;
    popupScale.x = 20.0f;
    popupScale.y = 20.0f;

    for (int i = 0; i < DAMAGE_POPUP_MAX_LIST_SIZE; ++i)
    {
        DamageTransforms[i] = TransformCreate(0.0f, 0.0f);
        DamagePopupScales[i] = 20.0f;
        TransformSetScale(DamageTransforms[i], &popupScale);
        DamageAmounts[i] = malloc(sizeof(char)* 32);
        /*DamageAmounts[i] = calloc(1, DAMAGE_POPUP_MAX_STRING_LENGTH);*/
    }
}

//call on level shutdown and unload, but never after DamagePopupsFree()
void ResetDamagePopupDrawer()
{
    for (int i = 0; i < DAMAGE_POPUP_MAX_LIST_SIZE; ++i)
    {
        DamageSlotFilledList[i] = false;
        DamageReds[i] = 0;
        DamageGreens[i] = 0;
        DamageBlues[i] = 0;
        DamageAlphas[i] = 0;
        DamageNums[i] = 0;
        DamageAmountOffsets[i] = 0;
        DamageActionOffsets[i] = 0;
        TransformZero(DamageTransforms[i]);
        DamagePopupScales[i] = 20.0f;
    }
}

//call whenever an attack that made contact occured
void DamagePopupQueueForDrawing(float r, float g, float b, float a, int damage, float damageAmountYOffset, float damageActionOffset, TransformPtr position ,DamagePopupType dptype, bool showNum, float scale)
{
    if (a > 0.0f)
    {
        for (int i = 0; i < DAMAGE_POPUP_MAX_LIST_SIZE; ++i)
        {
            if (DamageSlotFilledList[i])
            {
                if (DamageAlphas[i] <= 0.0f)
                {
                    DamageSlotFilledList[i] = false;
                }
            }
            else
            {
              AEVec2 pos;
              if (position)
                pos = *TransformGetTranslation(position);
                switch (dptype)
                {
                case DPHit:
                    DamageActions[i] = "Hit";
                    break;
                case DPBlock:
                    DamageActions[i] = "Blocked";
                    break;
                case DPParry:
                    DamageActions[i] = "Parried";
                    break;
                case DPPerfectBlock:
                    DamageActions[i] = "Perfect Block";
                    break;
                case DPStun:
                    DamageActions[i] = "Stunned";
                    break;
                case DPRegen:
                    DamageActions[i] = "Regened";
                    break;
                case DPUpgrade:
                    DamageActions[i] = "Upgrade";
                    break;
                case DPPlayer1Wins:
                    DamageActions[i] = "Player 1 Wins";
                    CameraGetPosition(&pos.x, &pos.y);
                    pos.x -= (AEGfxGetWinMaxX() - AEGfxGetWinMinX()) / 4;
                    break;
                case DPPlayer2Wins:
                    DamageActions[i] = "Player 2 Wins";
                    CameraGetPosition(&pos.x, &pos.y);
                    pos.x -= (AEGfxGetWinMaxX() - AEGfxGetWinMinX()) / 4;
                    break;
                default:
                    return; //function likely called with garbage
                }
                DamageSlotFilledList[i] = true;
                DamageReds[i] = r;
                DamageGreens[i] = g;
                DamageBlues[i] = b;
                DamageAlphas[i] = a;
                DamageNums[i] = damage;
                DamageAmountOffsets[i] = damageAmountYOffset;
                DamageActionOffsets[i] = damageActionOffset;
                _itoa_s(damage, DamageAmounts[i], 32,10);
                DamageShowNumList[i] = showNum;
                DamagePopupScales[i] = scale;
                TransformSetTranslation(DamageTransforms[i], &pos);
                return;
            }
        }
    }
}

//call on update after DrawItemsInQueue()
void DamagePopupsDraw()
{
    for (int i = 0; i < DAMAGE_POPUP_MAX_LIST_SIZE; ++i)
    {
        if (DamageSlotFilledList[i])
        {
            AEGfxSetTintColor(DamageReds[i], DamageGreens[i], DamageBlues[i], DamageAlphas[i]);

            AEVec2 textScale;
            textScale.x = DamagePopupScales[i];
            textScale.y = DamagePopupScales[i];
            AEVec2 originalPos = *TransformGetTranslation(DamageTransforms[i]);
            AEVec2 adjPos;
            adjPos.x = originalPos.x;
            adjPos.y = originalPos.y + DamageAmountOffsets[i];

            TransformSetScale(DamageTransforms[i], &textScale);   //scale text

            if (DamageShowNumList[i])
            {
                TransformSetTranslation(DamageTransforms[i], &adjPos); //place damage number
                SpriteSetText(damagePopupSprite, DamageAmounts[i]);     //damage amount text
                SpriteDraw(damagePopupSprite, DamageTransforms[i]);    //draw damage number
            }

            adjPos.y = originalPos.y + DamageActionOffsets[i];
            TransformSetTranslation(DamageTransforms[i], &adjPos); //place damage string
            SpriteSetText(damagePopupSprite, DamageActions[i]);    //damage string text
            SpriteDraw(damagePopupSprite, DamageTransforms[i]);    //draw damage string

            TransformSetTranslation(DamageTransforms[i], &originalPos);
            //post-draw updates
            ++DamageAmountOffsets[i];
            DamageAlphas[i] -= .01f;
        }
    }
    AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
}

//call on level unload after ResetDamagePopupDrawer()
void DamagePopupsFree()
{
    SpriteFree(&damagePopupSprite);
    AEGfxTextureUnload(damageTexture);
    AEGfxMeshFree(damageMesh);
    SpriteSourceFree(&damageSS);

    for (int i = 0; i < DAMAGE_POPUP_MAX_LIST_SIZE; ++i)
    {
        TransformFree(&DamageTransforms[i]);
        free(DamageAmounts[i]);
        DamageAmounts[i] = NULL;
    }
}

#pragma endregion

#pragma endregion

//Dont even trip, this beeg boi works just fine
//returns if human got "Yoinked" - Spice
bool UpdateHuman(HumanPtr human)
{
    if (human)
    {
        TransformPtr trans = ObjectGetTransform(human->obj);
        PhysicsPtr phys = ObjectGetPhysics(human->obj);
        AEVec2 scale;
        AEVec2* pos = NULL;
        AEVec2 offset = { 0, 60 };
        AEVec2 headPos;
        AEVec2 legPos;
        AEVec2 swordPos;
        AEVec2 shieldPos;
        AEVec2 shieldOffsets[4] = { { -25, -20 }, {40, 0}, {25, -10}, {-40,0} };
        AEVec2 swordOffsets[4] = { { -34,-30 }, {40, -20}, {10, -15}, {-35,-20} };
        //AEVec2 swordOffsetsA[4] = { { -5,-35 }, {80, -20}, {-10, -5}, {-80,-15} };
        AEVec2 swordOffsetsA[4] = { { -20,-30 }, {65, 15}, {0, 0}, {-55,5} };
        ItemPtr head = 0;
        ItemPtr body = 0;
        ItemPtr legs = 0;
        ItemPtr sword = 0;
        ItemPtr shield = ItemGetByID(DefaultShield);
        EnemyPtr enemy = 0;
        PlayerPtr player = NULL;
        bool showSword = true;
        int frblIndex;
        int controllerID = 0;
        sword = HumanGetWeapon(human);
        HumanGetArmors(human, &head, &body, &legs);
        if (!isPaused)
        {
            if (human->obj->tag == EnemyTag)
                enemy = (EnemyPtr)human;
            else if (HumanIsPlayer(human))
            {
                player = (PlayerPtr)human;
                controllerID = PlayerGetControllerID(player);
            }
            if (!human->isDead)
            {
                if (human->stamina < human->staminaMax)
                {
                    human->stamina += .5f;
                }
                else
                    human->canDodge = true;
                if (human->isHurt)
                {
                    AEGfxSetTintColor(1.0f, 0.0f, 0.0f, 1.0f);
                    --(human->isHurt);
                }
                if (human->actionDelay)
                {
                    if(human->stateNext != HSstun)
                        human->stateNext = HSidle;
                    --(human->actionDelay);
                    if (!human->actionDelay)
                        human->stateNext = HSidle;
                }
                    if (player)
                        HumanControlHuman(human);
                    else if (human->obj->tag == EnemyTag && human->fightStyle)
                    {
                        human->fightStyle(enemy);
                    }
                    if (human->stateNext != HSstun && human->stateCurr != HSstun)
                    {
                      if (human->isAttacking)
                      {
                        swordOffsets[0] = swordOffsetsA[0];
                        swordOffsets[1] = swordOffsetsA[1];
                        swordOffsets[2] = swordOffsetsA[2];
                        swordOffsets[3] = swordOffsetsA[3];
                        human->stateNext = HSattack;
                        if (human->isAttacking != 1)
                          human->actionDelay = 1;
                        AEVec2 zero = { 0 };
                        PhysicsSetVelocity(phys, &zero);
                        human->isRunning = 0;
                        human->isBlocking = 0;
                        human->isDodging = 0;
                        if (enemy)
                        {
                          if (HumanAttack(human, enemy->target))
                          {
                            if (gameState.current == GsBattleRoyale)
                              QueueKill(HumanGetName(human), HumanGetName(enemy->target));
                            ++human->kills;
                            ItemPtr tHead = NULL;
                            ItemPtr tBody = NULL;
                            ItemPtr tLegs = NULL;
                            ItemPtr tSword = HumanGetWeapon(enemy->target);
                            float gainedHealth = 0;
                            HumanGetArmors(enemy->target, &tHead, &tBody, &tLegs);
                            if (tHead && head && tHead->id > head->id)
                            {
                              head = tHead;
                              RemoveItem(enemy->target->inventory, slotHead);
                              gainedHealth += ItemGetHealthBoost(head);
                            }
                            if (tBody && body && tBody->id > body->id)
                            {
                              body = tBody;
                              RemoveItem(enemy->target->inventory, slotBody);
                              gainedHealth += ItemGetHealthBoost(body);
                            }
                            if (tLegs && legs && tLegs->id > legs->id)
                            {
                              legs = tLegs;
                              RemoveItem(enemy->target->inventory, slotLegs);
                              gainedHealth += ItemGetHealthBoost(legs);
                            }
                            if (tSword && sword && tSword->id > sword->id)
                            {
                              sword = tSword;
                              RemoveItem(enemy->target->inventory, slotWeapon);
                              gainedHealth += ItemGetHealthBoost(sword);
                            }

                            if (gainedHealth + human->health > 100.0f)
                              gainedHealth = 100.0f - human->health;
                            human->health += gainedHealth;
                            if (gainedHealth >= 1.0f)            //lime green
                              DamagePopupQueueForDrawing(.196f, .803f, .196f, 1.0f, (int)gainedHealth, 100.0f, -50.0f, human->obj->transform, DPRegen, true, 23.0f);
                            HumanSetArmors(human, head->id, body->id, legs->id);
                            HumanSetWeapon(human, sword->id);
                          }
                        }
                        else
                        {
#if USING_HUGE_ATTACK_CHEATS
                          if (GetButton(0, Button_Y))
                          {
                            human->attack = 150.0f;
                          }
                          else
                          {
                            human->attack = 10.0f;
                          }

#endif
                          if (gameState.current == GsBattleRoyale)
                          {
                            for (int i = 0; i < MAXOBJECTAMOUNT; ++i)
                            {
                              if (human->targets[i] && HumanAttack(human, human->targets[i]))
                              {
                                QueueKill("You", HumanGetName(human->targets[i]));
                                ++human->kills;
                                ItemPtr tHead = NULL;
                                ItemPtr tBody = NULL;
                                ItemPtr tLegs = NULL;
                                ItemPtr tSword = HumanGetWeapon(human->targets[i]);
                                float gainedHealth = 0;
                                HumanGetArmors(human->targets[i], &tHead, &tBody, &tLegs);
                                if (tHead && head && tHead->id > head->id)
                                {
                                  head = tHead;
                                  RemoveItem(human->targets[i]->inventory, slotHead);
                                  gainedHealth += ItemGetHealthBoost(head);
                                }
                                if (tBody && body && tBody->id > body->id)
                                {
                                  body = tBody;
                                  RemoveItem(human->targets[i]->inventory, slotBody);
                                  gainedHealth += ItemGetHealthBoost(body);
                                }
                                if (tLegs && legs && tLegs->id > legs->id)
                                {
                                  legs = tLegs;
                                  RemoveItem(human->targets[i]->inventory, slotLegs);
                                  gainedHealth += ItemGetHealthBoost(legs);
                                }
                                if (tSword && sword && tSword->id > sword->id)
                                {
                                  sword = tSword;
                                  RemoveItem(human->targets[i]->inventory, slotWeapon);
                                  gainedHealth += ItemGetHealthBoost(sword);
                                }
                                if (gainedHealth + human->health > 100.0f)
                                  gainedHealth = 100.0f - human->health; //i think this is right
                                human->health += gainedHealth;
                                if (gainedHealth >= 1.0f)            //lime green
                                  DamagePopupQueueForDrawing(.196f, .803f, .196f, 1.0f, (int)gainedHealth, 100.0f, -50.0f, human->obj->transform, DPRegen, true, 23.0f);
                                HumanSetArmors(human, head->id, body->id, legs->id);
                                HumanSetWeapon(human, sword->id);
                              }
                            }
                          }
                          else
                            HumanAttack(human, human->targets[0]);
                        }
                        if (human->isAttacking)
                          --(human->isAttacking);
                      }
                      else if (human->isDodging || human->stateNext == HSdodge)
                      {

                        if (human->stateCurr == HSdodge && human->stamina > .0f && human->canDodge)
                        {
                          if (human->stamina >= 100.0f)
                            playDashSound();
                          human->stamina -= 100.0f / 15; //higher # in denom = longer dodge
                          if (human->stamina <= 0.0f)
                          {
                            human->isDodging = 0;
                            human->stateNext = HSidle;
                            human->canDodge = false;
                            human->actionDelay = 0;
                          }
                        }
                        human->isRunning = 0;
                        human->isBlocking = 0;
                        HumanDodge(human);

                        if (player)
                        {
                          if (controllerID)
                          {
                            if (vibrateTimeP2 <= 0)
                              ControllerVibrate(controllerID, 0.5f, 0.5f); //1
                          }
                          else
                          {
                            if (vibrateTime <= 0)
                              ControllerVibrate(controllerID, 0.5f, 0.5f); //0
                          }

                        }
                        if (human->isDodging && human->stateCurr != HSdodge)
                          --(human->isDodging);
                        if (!human->isDodging)
                        {
                          /*human->actionDelay = 30;*/
                          human->stateNext = HSidle;
                          if (player)
                          {
                            if (controllerID) //id 0: Player 1, id 1: Player 2
                            {
                              if (vibrateTimeP2 <= 0)
                                ControllerVibrate(controllerID, 0.0f, 0.0f); //1
                            }
                            else
                            {
                              if (vibrateTime <= 0)
                                ControllerVibrate(controllerID, 0.0f, 0.0f); //0
                            }
                          }
                        }
                        
                      }
                      else if (human->isBlocking)
                      {
                        showSword = false;
                        human->stateNext = HSblock;
                        AEVec2 zero = { 0 };
                        PhysicsSetVelocity(phys, &zero);
                        human->isRunning = 0;
                        //showSword = human->dir == right || human->dir == left;
                        //HumanBlock(human);
                        if (human->obj->tag == EnemyTag)
                        {
                          if (human->isBlocking >= 40 && RandomRange(1, 10) > 9)
                          {
                            human->isBlocking = 0;
                            human->stateNext = HSidle;
                          }
                          else
                            ++(human->isBlocking);
                        }
                        AEGfxSetBackgroundColor(0, 0, 1);
                      }
                      else if (human->isRunning)
                      {
                        human->stateNext = HSrun;
                        HumanRun(human);
                        --(human->isRunning);
                      }

                      else if (!human->isRunning) //fixes some buggies
                      {
                        //human->stateNext = HSidle;
                        AEVec2 zero = { 0 };
                        PhysicsSetVelocity(phys, &zero);
                      }
                    }
                    else //stunned
                    {
                      showSword = false;
                      HumanSetBoolOff(human, 1, 1, 0, 0, 1, 1);
                      AEVec2 zero = { 0 };
                      PhysicsSetVelocity(phys, &zero);
                    }

                PhysicsUpdate(phys, trans, dt * 10);
                scale = *TransformGetScale(trans);
                pos = TransformGetTranslation(trans);
                if (AEVec2Length(pos) >= ARENA_RADIUS_MIN) //FREAKING OVAL COLLISION BOIS LESSS GOOOOOOOOOOOOOOOO
                {
                    AEVec2 focus1 = { FOCUS1, 0 };
                    AEVec2 focus2 = { FOCUS2, 0 };
                    float d1 = AEVec2Distance(pos, &focus1); // sqrt gets called ouchie
                    float d2 = AEVec2Distance(pos, &focus2); // sqrt called again... I want to cry... Freaking Erich made an oval
                    float distanceOutside = d1 + d2 - 2 * ARENA_RADIUS_MAX;
                    if (distanceOutside > 0) //if outside or on edge
                    {
                        //start of collision resolution, i actually dont know what im doing but Spice wants me to implement something idk how to do
                        
                        AEVec2* end = TransformGetTranslation(trans);

                        if (end->x < 0)
                        {
                            end->x += distanceOutside;
                        }
                        else
                            end->x -=  distanceOutside;
                        if (end->y < 0)
                        {
                            end->y +=  distanceOutside;
                        }
                        else
                            end->y -=  distanceOutside;

                        //end of a half-baked idea... I mean collision resolution
                        //edit: holy crap yall, I cant beleive this works!!! Means I can go home now :)
                    }
                }

                if (!enemy) //if its a player
                {
					          followKillLeader = false;

                    if (human->isDodging)
                        CameraSmoothToPosition(pos->x, pos->y, 10.5f, false); //move camera fast to player
                    else
                      CameraSmoothToPosition(pos->x, pos->y, 1.5f, false);   //move camera to player
                }
                else //its an enemy
                {
                    if (!enemy->target || enemy->target->isDead)
                        EnemyRetarget(enemy,NULL);
                    if (human->killLeader && followKillLeader)
                        CameraSmoothToPosition(pos->x, pos->y, 1.5f, false);   //move camera to kill leader (enemy)
                }

                headPos.x = pos->x - offset.x;
                headPos.y = pos->y + offset.y;

                legPos.x = pos->x + .7f*offset.x;
                legPos.y = pos->y - .7f*offset.y;

                frblIndex = HumanSetFaceDir(human, human->dir); //fixes a buggy that renders same weapon the same way in each instance of weapon

                swordPos.x = pos->x + swordOffsets[frblIndex].x;
                swordPos.y = pos->y + swordOffsets[frblIndex].y;

                shieldPos.x = pos->x + shieldOffsets[frblIndex].x;
                shieldPos.y = pos->y + shieldOffsets[frblIndex].y;
            }
            else //he dead
            {
                human->stateNext = HSidle;
                if(gameState.current != GsLevel1)
                    ColliderDelete(&human->obj->collider);
                ++human->isDead;
                if (human->isDead >= (1 / dt) * 5)
                {
                    FreeHuman(&human);
                    human = NULL;
                    return true;
                }
                pos = TransformGetTranslation(trans);
                headPos.x = pos->x - offset.y;
                headPos.y = pos->y + offset.x;

                legPos.x = pos->x + .7f*offset.y;
                legPos.y = pos->y - .7f*offset.x;

                HumanSetBoolOff(human, 1, 1, 1, 0, 1, 1);
                scale = *TransformGetScale(trans);
                pos = TransformGetTranslation(trans);
				        if (player)
				        {
					          followKillLeader = true;
					          CameraSmoothToPosition(0.0f, 0.0f, 0.25f, true);
				        }

                frblIndex = HumanSetFaceDir(human, FaceDirMAX); //fixes a buggy that renders same weapon the same way in each instance of weapon
                swordPos.x = pos->x + swordOffsets[frblIndex].x;
                swordPos.y = pos->y + swordOffsets[frblIndex].y;
                shieldPos.x = pos->x + shieldOffsets[frblIndex].x;
                shieldPos.y = pos->y + shieldOffsets[frblIndex].y;
            }
        }
        else //game is paused
        {
            pos = TransformGetTranslation(trans);
            headPos.x = pos->x - offset.x;
            headPos.y = pos->y + offset.y;

            legPos.x = pos->x + .7f*offset.x;
            legPos.y = pos->y - .7f*offset.y;
            frblIndex = HumanSetFaceDir(human, human->dir);
            swordPos.x = pos->x + swordOffsets[frblIndex].x;
            swordPos.y = pos->y + swordOffsets[frblIndex].y;
            shieldPos.x = pos->x + shieldOffsets[frblIndex].x;
            shieldPos.y = pos->y + shieldOffsets[frblIndex].y;
        }

        TransformGetMatrix(trans); //update matrix
		    human->health = AEClamp(human->health, 0, 100);
        if (legs)
        {
            TransformSetTranslation(legs->obj->transform, &legPos);
            ItemQueueForDrawing(legs->obj->sprite, legs->obj->transform, ObjectGetSpriteSource(legs->obj),legs->obj->drawLayer, human->isHurt);
        }
        if (body)
        {
            TransformSetTranslation(body->obj->transform, pos);
            ItemQueueForDrawing(body->obj->sprite, body->obj->transform,ObjectGetSpriteSource(body->obj),body->obj->drawLayer, human->isHurt);
        }
        if (head)
        {
            TransformSetTranslation(head->obj->transform, &headPos);
            ItemQueueForDrawing(head->obj->sprite, head->obj->transform,ObjectGetSpriteSource(head->obj),head->obj->drawLayer, human->isHurt);
        }
        if (sword && showSword)
        {
            TransformSetTranslation(sword->obj->transform, &swordPos);
            ItemQueueForDrawing(sword->obj->sprite, sword->obj->transform,ObjectGetSpriteSource(sword->obj),sword->obj->drawLayer,false);
        }
        if (shield&&human->isBlocking)
        {
            TransformSetTranslation(shield->obj->transform, &shieldPos);
            ItemQueueForDrawing(shield->obj->sprite, shield->obj->transform, ObjectGetSpriteSource(shield->obj), shield->obj->drawLayer, false);
        }
        return false;
    }
    return false;
}

#pragma endregion
