/******************************************************************************
filename    AI.h
author      Brayan
DP email    brayan.lopez@digipen.edu
course      GAM150

Brief Description:
This file includes the AI function prototypes of enemies and other beings.

******************************************************************************/
#pragma once

/* disable warnings for single-line comments, since Microsoft's stdlib, etc use those extensively */
#pragma warning(push)
#pragma warning(disable : 4001)

#include "targetver.h" /* required by Windows */
#include "AEGraphics.h" /*VertexList, Texture*/
#include "Objects.h"

typedef void(*AIFightFunctionPtr)(EnemyPtr AI);

//controls the human passed in with controller/keyboard input
void HumanControlHuman(HumanPtr human);
//human attacks and does multiple checks to see if hit was successful, if successful then applies damage to target based on target's armor and human's total attack
//returns if attack killed target
bool HumanAttack(HumanPtr human, HumanPtr target);
//calculates how much damage a hit will do after armor stats have been taken into account
float ArmorReduceDamage(ItemPtr head, ItemPtr body, ItemPtr legs, float damage);
//checks if human is blocking and reduces damage by human's block resistance
float BlockReduceDamage(HumanPtr human, float damage);
//applies damage directly to human
bool HumanTakeDamage(HumanPtr human, float damage);
//AI for an enemy
void AIFight(EnemyPtr AI, const int attackWithinRange, const int blockWithinRange, const int dodgeWithinRange, const int runToPlayer, const int dodgeNotInRange);
//AI for an enemy that likes blocking
void AIFightBlockFocus(EnemyPtr AI);
//AI for an enemy that likes attacking
void AIFightAttackFocus(EnemyPtr AI);
//AI for an enemy that likes dodging
void AIFightDodgeFocus(EnemyPtr AI);
//AI for a a random boi
void AIFightRandom(EnemyPtr AI);
//AI with custom and specified focus
void AIFIghtCustom(EnemyPtr AI);
//checks if an item's range (squared) is >= distance between things 1 and 2 (squared)
int ItemIsInRange(ItemPtr item, AEVec2* thing1, AEVec2* thing2);
//applies human run speed to facing direction
void HumanRun(HumanPtr human);
//call if the human isDodging, applies dodge force to human in direction of human's dodgeDir
void HumanDodge(HumanPtr guy);
//applies force to human towards direction
void HumanMove(HumanPtr human, float force, FaceDir direction);
//makes human block attacks
void HumanBlock(HumanPtr human);
//turns human to look at other human
void HumanFaceHuman(HumanPtr human, HumanPtr target);
//gets direction an object (from) would need to face to be facing other object (to)
FaceDir DirFromVecs(AEVec2* from, AEVec2* to);
//Gets closest direction to angle for facing objects to other objects
FaceDir DirFromAngle(float angle);
