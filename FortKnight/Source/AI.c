/******************************************************************************
filename    AI.c
author      Brayan
DP email    brayan.lopez@digipen.edu
course      GAM150

Brief Description:
This file includes the AI functions of enemies and other beings.

******************************************************************************/

// ---------------------------------------------------------------------------
// includes

#include "stdafx.h"		// Should be included first in every .c file!

#include "AEEngine.h"
#include "AI.h"
#include "Utils.h"  //RandomRange, Square
#include <stdlib.h>
#include "Sound.h"
#include "Input.h"
#include "Camera.h"
#include "OST.h"
/////////////////
#include "ParticleManager.h"
#include "ParticleEmitter.h"
/////////////////

static FMOD_SOUND* swordSound;
float vibrateTime = 0.0f;
extern float vibrateTimeP2;

// Libraries
#ifdef _DEBUG
#pragma comment (lib, "Alpha_Engine_D.lib")
#else
#pragma comment (lib, "Alpha_Engine.lib")
#endif

// ---------------------------------------------------------------------------
// globals

void HumanControlHuman(HumanPtr human)
{
    PlayerPtr player = (PlayerPtr)human;
    InputUpdate(PlayerGetControllerID(player));

#pragma region BUTTONS_INPUT
    if (!HumanGetBool(human, 1, 0, 0, 0, 0, 0))
    {
      if (!HumanGetActionDelay(human))
      {
        if (GetButtonDown(PlayerGetControllerID(player), Button_X)/* || AEInputCheckTriggered(VK_SPACE)*/)
            HumanSetBoolOn(human, 15, 0, 0, 0, 0, 0); //attack
        if (GetButton(PlayerGetControllerID(player), Button_A)/* || AEInputCheckCurr(VK_LCONTROL)*/)
            HumanSetBoolOn(human, 0, 0, 0, 0, 0, HumanGetBool(human, 0, 0, 0, 0, 0, 1) + 1); //block
        else
            HumanSetBoolOff(human, 0, 0, 0, 0, 0, 1); //turn off blocking
      }
    }
    
#pragma endregion BUTTONS_INPUT

#pragma region RIGHT_ANALOG_STICK_INPUT
    if (HumanGetCanDodge(human) && HumanGetNextState(human) != HSstun && HumanGetCurrentState(human) != HSstun)
    {
        if (!HumanGetBool(human, 0, 0, 0, 0, 1, 0))
        {
            //bool shifting = AEInputCheckTriggered(VK_LSHIFT);
            int dodgeTime = 15;

            if (/*AEInputCheckCurr('A') && shifting || */GetJoystickX(SIDE_R) < -0.25f)
            {
                if (/*AEInputCheckCurr('W') || */GetJoystickY(SIDE_R) > 0.25f)
                    HumanSetDodgeDir(human, upleft);
                else if (/*AEInputCheckCurr('S') || */GetJoystickY(SIDE_R) < -0.25f)
                    HumanSetDodgeDir(human, downleft);
                else
                    HumanSetDodgeDir(human, left);

                HumanSetBoolOn(human, 0, 0, 0, 0, dodgeTime, 0);
                HumanSetNextState(human, HSdodge);
            }
            else if (/*AEInputCheckCurr('D') && shifting || */GetJoystickX(SIDE_R) > 0.25f)
            {
                if (/*AEInputCheckCurr('W') || */GetJoystickY(SIDE_R) > 0.25f)
                    HumanSetDodgeDir(human, upright);
                else if (/*AEInputCheckCurr('S') || */GetJoystickY(SIDE_R) < -0.25f)
                    HumanSetDodgeDir(human, downright);
                else
                    HumanSetDodgeDir(human, right);

                HumanSetBoolOn(human, 0, 0, 0, 0, dodgeTime, 0);
                HumanSetNextState(human, HSdodge);
            }
            else if (/*AEInputCheckCurr('W') && shifting || */GetJoystickY(SIDE_R) > 0.25f)
            {
                HumanSetDodgeDir(human, up);
                HumanSetBoolOn(human, 0, 0, 0, 0, dodgeTime, 0);
                HumanSetNextState(human, HSdodge);
            }
            else if (/*AEInputCheckCurr('S') && shifting || */GetJoystickY(SIDE_R) < -0.25f)
            {
                HumanSetDodgeDir(human, down);
                HumanSetBoolOn(human, 0, 0, 0, 0, dodgeTime, 0);
                HumanSetNextState(human, HSdodge);
            }
        }
    }

#pragma endregion RIGHT_ANALOG_STICK_INPUT

#pragma region LEFT_ANALOG_STICK_INPUT

    if (InputRight())
    {
        if (InputUp())
        {
            HumanSetFaceDir(human, upright);
        }
        else if (InputDown())
        {
            HumanSetFaceDir(human, downright);
        }
        else
        {
            HumanSetFaceDir(human, right);
        }
        HumanSetBoolOn(human, 0, 2, 0, 0, 0, 0);
    }
    else if (InputLeft())
    {
        if (InputUp())
        {
            HumanSetFaceDir(human, upleft);
        }
        else if (InputDown())
        {
            HumanSetFaceDir(human, downleft);
        }
        else
        {
            HumanSetFaceDir(human, left);
        }
        HumanSetBoolOn(human, 0, 2, 0, 0, 0, 0);
    }
    else
    {
        if (InputUp())
        {
            HumanSetBoolOn(human, 0, 2, 0, 0, 0, 0);
            HumanSetFaceDir(human, up);
        }
        else if (InputDown())
        {
            HumanSetBoolOn(human, 0, 2, 0, 0, 0, 0);
            HumanSetFaceDir(human, down);
        }
        else if(!HumanGetBool(human,0,0,0,0,1,0)) //if not dodging nor running
        {
            HumanSetNextState(human, HSidle);
            HumanSetBoolOff(human, 0, 1, 0, 0, 0, 0);
        }
    }

#pragma endregion LEFT_ANALOG_STICK_INPUT
}

bool HumanAttack(HumanPtr human, HumanPtr target)
{
    if (human && target)
    {
        //Start playing the attack animation
        if (HumanGetHealth(target) <= 0)
            return false;
        if (HumanGetBool(human, 1, 0, 0, 0, 0, 0) == 1) //if attack timer is down to 1
        {
            PlayerPtr player = NULL;
            TransformPtr myTrans = ObjectGetTransform(ObjectGetObject(human, NULL, NULL, NULL));
            TransformPtr targetTrans = ObjectGetTransform(ObjectGetObject(target, NULL, NULL, NULL));
            AEVec2* myVec = TransformGetTranslation(myTrans);
            AEVec2* targetVec = TransformGetTranslation(targetTrans);
            FaceDir myFacing = HumanGetFaceDir(human);
            FaceDir targetFacing = HumanGetFaceDir(target);
            FaceDir meToTarget = DirFromVecs(myVec, targetVec); //my dir to target
            FaceDir targetToMe = DirFromVecs(targetVec, myVec); //target's dir to me
            if (HumanIsPlayer(target))/* ObjectGetTag(ObjectGetObject(target, NULL, NULL, NULL)) == PlayerTag*/
                player = (PlayerPtr)human;
            //make sure target is within weapon range and im facing him
            if (ItemIsInRange(HumanGetWeapon(human), myVec, targetVec) && (myFacing == meToTarget ||
                                                  FaceDirGetWithOffset(myFacing,1) == meToTarget ||
                                                  FaceDirGetWithOffset(myFacing,-1) == meToTarget))
            {
                //is target facing me
              bool facingMe = (targetFacing == targetToMe || FaceDirGetWithOffset(targetFacing, 1) == targetToMe ||
                               FaceDirGetWithOffset(targetFacing, -1) == targetToMe);

                //SoundPlay(&swordSound, false);
                if (HumanGetBool(target, 1, 0, 0, 0, 0, 0) && facingMe) //target is also attacking and is facing me
                {
                    HumanSetDodgeDir(human, FaceDirGetWithOffset(HumanGetFaceDir(human),4));
                    HumanSetDodgeDir(target, FaceDirGetWithOffset(HumanGetFaceDir(target),4));
                    HumanSetBoolOn(human , 0, 0, 0, 0, RandomRange(15, 20), 0); //add knockback to me
                    //HumanSetBoolOn(target, 0, 0, 0, 0, RandomRange(15, 20), 0); //add knockback to target
                    HumanSetNextState(human, HSknockedback);
                    HumanSetNextState(target, HSknockedback);
                    HumanSetActionDelay(human, 15); //small delay before i can swing sword again
                    HumanSetActionDelay(target, 0);
                    HumanSetBoolOff(target, 1, 0, 0, 0, 0, 0);
                    DamagePopupQueueForDrawing(1.0f, 1.0f, 1.0f, 1.0f, 0, 200.0f, -100.0f, targetTrans, DPParry, false, 20.0f);
                    playParrySound();
                    //DamagePopupQueueForDrawing(1.0f, .0f, 1.0f, 1.0f, 0, 200.0f, -10.0f, myTrans, DPStun);
                    //CameraShake(10, .25f, false);
                    return false;
                }
                HumanSetDodgeDir(target, FaceDirGetWithOffset(HumanGetFaceDir(target), 4));
                HumanSetBoolOn(target, 0, 0, 0, 0, RandomRange(5, 10), 0); //add knockback to target
                HumanSetDodgeDir(human, FaceDirGetWithOffset(HumanGetFaceDir(human), 4));
                HumanSetBoolOn(human, 0, 0, 0, 0, RandomRange(5, 10), 0); //add knockback to me
                HumanSetNextState(human, HSknockedback);
                HumanSetNextState(target, HSknockedback);
                HumanSetActionDelay(human, 10);
                HumanSetActionDelay(target, 0);
                if (ObjectGetTag(ObjectGetObject(target, NULL, NULL, NULL)) == EnemyTag)
                    EnemyRetarget((EnemyPtr)target, human);
                if (player)//if target is player
                {
                    int id = PlayerGetControllerID(player);
                    CameraShake(10, .25f, false);
                    ControllerVibrate(id, 1.0f, 0.0f);
                    if (id)
                        vibrateTimeP2 = .5f; //player 1
                    else
                        vibrateTime = .5f; //player 2
                }
                int targetBlockingTime = HumanGetBool(target, 0, 0, 0, 0, 0, 1);
                if (targetBlockingTime <= 15 && targetBlockingTime > 0)
                {
                    DamagePopupQueueForDrawing(.0f, .0f, 1.0f, 1.0f, 0, 200.0f, -100.0f, targetTrans, DPPerfectBlock, false, 20.0f); //perf block
                    DamagePopupQueueForDrawing(1.0f, .0f, 1.0f, 1.0f, 0, 200.0f, -10.0f, myTrans, DPStun, false, 20.0f); //stun
                    HumanSetBoolOff(human, 1, 1, 0, 0, 1, 1);
                    HumanSetActionDelay(human, 60);    //stun me
                    HumanSetNextState(human, HSstun); //set next state to stunned
                    playBlockSound();
                    return false; //perfect block
                }
                int damageDealt = (int)HumanGetHealth(target);
                ItemPtr head = NULL, body = NULL, legs = NULL;
                HumanGetArmors(target, &head, &body, &legs);
                float damage = ObjectGetAttackDamage(human, HumanGetWeapon(human));
                bool killed = HumanTakeDamage(target, ArmorReduceDamage(head, body, legs, BlockReduceDamage(target, damage)));
				////////////////////////////////////////////////////////////
				//if (HumanGetFaceDir(human) == right)
				//{
				//	ParticleEmitterCreateEmitter(true, .06f, *TransformGetTranslation(ObjectGetTransform(ObjectGetObject(human, NULL, NULL, NULL))), 0.0f, 0.0f, 20.0f, cTemplateSpark, NULL);
				//}
				//else if (HumanGetFaceDir(human) == left)
				//{
				//	ParticleEmitterCreateEmitter(true, 0.06f, *TransformGetTranslation(ObjectGetTransform(ObjectGetObject(human, NULL, NULL, NULL))), 3.14f, 3.14f, 20.0f, cTemplateSpark, NULL);
				//}
				//else if (HumanGetFaceDir(human) == up)
				//{
				//	ParticleEmitterCreateEmitter(true, .06f, *TransformGetTranslation(ObjectGetTransform(ObjectGetObject(human, NULL, NULL, NULL))), 1.57f, 1.57f, 20.0f, cTemplateSpark, NULL);
				//}
				//else if (HumanGetFaceDir(human) == down)
				//{
				//	ParticleEmitterCreateEmitter(true, .06f, *TransformGetTranslation(ObjectGetTransform(ObjectGetObject(human, NULL, NULL, NULL))), 4.71f, 4.71f, 20.0f, cTemplateSpark, NULL);
				//}
				////////////////////////////////////////////////////////////
                damageDealt -= (int)HumanGetHealth(target);
                if (targetBlockingTime)
                {
                    DamagePopupQueueForDrawing(1.0f, 1.0f, 0.0f, 1.0f, damageDealt, 200.0f, -100.0f, targetTrans, DPBlock, true, 20.0f); //block
                    playBlockSound();
                }
                else
                {
                    DamagePopupQueueForDrawing(1.0f, 0.0f, 0.0f, 1.0f, damageDealt, 200.0f, -100.0f, targetTrans, DPHit, true, 20.0f); //hit
                    playSwingSound();
                }
                return killed;
            }
            return false;
        }
        return false;
    }
    return false;
}

float ArmorReduceDamage(ItemPtr head, ItemPtr body, ItemPtr legs, float damage)
{
    //AESysPrintf("Damage before Armor Reduction: %f\n", damage);
    float endDamage = damage;

    if (head)
        endDamage -= damage * (ItemGetResistance(head) * .01f);
    if (body)
        endDamage -= damage * (ItemGetResistance(body) * .01f);
    if (legs)
        endDamage -= damage * (ItemGetResistance(legs) * .01f);

    //AESysPrintf("Damage after Armor Reduction: %f\n", endDamage);
    return endDamage;
}

float BlockReduceDamage(HumanPtr human, float damage)
{
    if (HumanGetBool(human, 0, 0, 0, 0, 0, 1))
    {
        //AESysPrintf("\nDamage before Block Reduction: %f\n", damage);
        damage = damage - (damage * (HumanGetBlockResist(human) * .01f));
        //AESysPrintf("Damage after Block Reduction: %f\n", damage);
        return damage;
    }

    return damage;
}

bool HumanTakeDamage(HumanPtr human, float damage)
{
    //AESysPrintf("Human took this much damage: %f\n", damage);
    HumanSetBoolOn(human, 0, 0, 30, 0, 0, 0); //show human is hurt
    HumanSetHealth(human, HumanGetHealth(human) - damage);
    if (HumanGetHealth(human) <= 0)
    {
        HumanSetBool(human, 0, 0, 0, 1, 0, 0);
        return true;
    }
    return false;
}

void AIFight(EnemyPtr AI, const int attackWithinRange, const int blockWithinRange, const int dodgeWithinRange, const int runToPlayer, const int dodgeNotInRange)
{
    HumanPtr player = EnemyGetTarget(AI);
    HumanPtr meHum = HumanGetHuman(NULL, AI);
    if (HumanGetCurrentState(meHum)==HSstun || HumanGetNextState(meHum)==HSstun)
        return;
    if (HumanGetActionDelay(meHum))
      return;
    AEVec2* playerPos = TransformGetTranslation(ObjectGetTransform(ObjectGetObject(player, NULL, NULL, NULL)));
    AEVec2* me = TransformGetTranslation(ObjectGetTransform(ObjectGetObject(meHum, NULL, NULL, AI)));
    ItemPtr weapon = HumanGetWeapon(meHum);

    int actWithinRange[3] = { 0 };          //attack: 0, block: 1, dodge: 2
    actWithinRange[0] = attackWithinRange;
    actWithinRange[1] = blockWithinRange;
    actWithinRange[2] = dodgeWithinRange;
    int withinRangeTotal = actWithinRange[0] + actWithinRange[1] + actWithinRange[2];
    int actNotInRange[2] = { 0 };                             //run: 0, dodge: 1
    actNotInRange[0] = runToPlayer;
    actNotInRange[1] = dodgeNotInRange;
    int notInRangeTotal = actNotInRange[0] + actNotInRange[1];

    if (!HumanGetActive(meHum))
    {
        if (ItemIsInRange(weapon, playerPos, me))   //within range
        {
            int withinRangeAction = RandomRange(1, withinRangeTotal) - actWithinRange[0];
            if (withinRangeAction <= 0)
                withinRangeAction = 1;
            if (actWithinRange[0] >= withinRangeAction)
            {
                HumanFaceHuman(meHum, player);
                HumanSetNextState(meHum, HSattack);
                HumanSetBoolOn(meHum, 20, 0, 0, 0, 0, 0); //attack
                return;
            }
            withinRangeAction -= actWithinRange[1];
            if (actWithinRange[1] >= withinRangeAction)
            {
                HumanFaceHuman(meHum, player);
                HumanSetNextState(meHum, HSblock);
                HumanBlock(meHum);                     //block
                return;
            }
            else
            {
                HumanSetDodgeDir(meHum, RandomRange(0, FaceDirMAX - 1));
                HumanSetNextState(meHum, HSdodge);
                HumanSetBoolOn(meHum, 0, 0, 0, 0, RandomRange(20, 45), 0); //dodge
            }

        }
        else                                                          //not within range
        {
            int notInRangeAction = RandomRange(1, notInRangeTotal) - actNotInRange[0];
            if (notInRangeAction <= 0)
                notInRangeAction = 1;
            if (actNotInRange[0] >= notInRangeAction)
            {
                HumanFaceHuman(meHum, player);
                HumanSetNextState(meHum, HSrun);
                HumanSetBoolOn(meHum, 0, RandomRange(1, 10), 0, 0, 0, 0); //run
            }
            else
            {
                HumanSetDodgeDir(meHum, RandomRange(0, FaceDirMAX - 1));
                HumanSetNextState(meHum, HSdodge);
                HumanSetBoolOn(meHum, 0, 0, 0, 0, RandomRange(10, 45), 0); //dodge
            }
        }
    }
}

void AIFightBlockFocus(EnemyPtr AI)
{
    AIFight(AI, 5, 10, 5, 8, 2);
}

void AIFightAttackFocus(EnemyPtr AI)
{
    AIFight(AI, 10, 10, 5, 15, 8);
}

void AIFightDodgeFocus(EnemyPtr AI)
{
    AIFight(AI, 5, 8, 7, 5, 5);
}

void AIFightRandom(EnemyPtr AI)
{
    AIFight(AI, RandomRange(1, 10), RandomRange(5, 10), RandomRange(1, 10), RandomRange(3, 10), RandomRange(1, 10));
}

void AIFIghtCustom(EnemyPtr AI)
{
    HumanPtr human = HumanGetHuman(NULL, AI);
    int withinRange[3] = { 0 };
    int outOfRange[2] = { 0 };
    HumanGetFightFocuses(human, &withinRange[0], &withinRange[1], &withinRange[2], &outOfRange[0], &outOfRange[1]);
    AIFight(AI, withinRange[0], withinRange[1], withinRange[2], outOfRange[0], outOfRange[1]);
}

int ItemIsInRange(ItemPtr item, AEVec2* thing1, AEVec2* thing2)
{
    if(item && thing1 && thing2)
        return Square(ItemGetRange(item)) >= AEVec2SquareDistance(thing1, thing2);
    return 0;
}

void HumanRun(HumanPtr human)
{
    HumanMove(human, HumanGetSpeed(human), HumanGetFaceDir(human));
}

void HumanDodge(HumanPtr human)
{
    HumanMove(human, HumanGetDodgeSpeed(human), HumanGetDodgeDir(human));
}

void HumanMove(HumanPtr human, float force, FaceDir direction)
{
    PhysicsPtr physics = ObjectGetPhysics(ObjectGetObject(human, NULL, NULL, NULL));
    if (physics)
    {
        AEVec2* vel = PhysicsGetVelocity(physics);

        switch (direction)
        {
        case upleft:
            vel->y = 1;
            vel->x = -1;
            AEVec2Normalize(vel, vel);
            AEVec2Scale(vel, vel, force);
            break;

        case upright:
            vel->x = 1;
            vel->y = 1;
            AEVec2Normalize(vel, vel);
            AEVec2Scale(vel, vel, force);
            break;

        case left:
            force *= -1;
            //fallthrough
        case right:
            vel->x = force;
            vel->y = 0.0f;
            break;

        case down:
            force *= -1;
            //fallthrough
        case up:
            vel->y = force;
            vel->x = 0.0f;
            break;

        case downleft:
            vel->x = -1;
            vel->y = -1;
            AEVec2Normalize(vel, vel);
            AEVec2Scale(vel, vel, force);
            break;

        case downright:
            vel->x = 1;
            vel->y = -1;
            AEVec2Normalize(vel, vel);
            AEVec2Scale(vel, vel, force);
            break;

        case FaceDirMAX:
            vel->x = 0;//force;
            vel->y = 0;//force;
            break;
        }
    }
}

void HumanBlock(HumanPtr human)
{
    //if (ObjectGetTag(ObjectGetObject(human, NULL, NULL, NULL)) == EnemyTag)
    //{
    //    HumanSetBoolOn(human, 0, 0, 0, 0, 0, 1);
    //    return;
    //}
    HumanSetBoolOn(human, 0, 0, 0, 0, 0, 1);
}

void HumanFaceHuman(HumanPtr human, HumanPtr target)
{
    if (human && target)
    {

        AEVec2* targetPos = TransformGetTranslation(ObjectGetTransform(ObjectGetObject(target, NULL, NULL, NULL)));
        AEVec2* enemyPos = TransformGetTranslation(ObjectGetTransform(ObjectGetObject(human, NULL, NULL, NULL)));

        HumanSetFaceDir(human, DirFromVecs(enemyPos,targetPos)); //face the target
    }
}

FaceDir DirFromVecs(AEVec2* from, AEVec2* to)
{
    AEVec2 faceVec = { 0.0f,0.0f };
    AEVec2Sub(&faceVec, to, from);

    float faceAng = AEVec2AngleFromVec2(&faceVec);
    return DirFromAngle(faceAng);
}

FaceDir DirFromAngle(float angle)
{
    float min = 10;
    float angles[8] = { PI * 2, PI4, PI2, PI3_4, PI, PI5_4, PI3_2, PI7_4 };
    FaceDir desiredDir = 0;
    if (angle < 0)
        angle += 2 * PI;

    for (int i = 0; i < FaceDirMAX; i++)
    {
        if (fabsf(angle - angles[i]) < min)
        {
            min = fabsf(angle - angles[i]);
            desiredDir = i;
        }
    }

    return desiredDir;
}
