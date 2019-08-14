//---------------------------------------------------------
// file:	Input.h
// author:	Akshat Madan
// brief:	Gamepad input using XINPUT
//
// Copyright © 2019 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once

typedef enum BUTTON
{
	Button_A,
	Button_B,
	Button_X,
	Button_Y,
	Button_LBumper,
	Button_RBumper
} BUTTON;

typedef enum SIDE
{
	SIDE_L,
	SIDE_R
} SIDE;

//---------------------------------------------------------
// Public Functions:
//---------------------------------------------------------
void InputUpdate(int id);
void InputInit(int id);
float GetJoystickX(SIDE stick);
float GetJoystickY(SIDE stick);
int GetButton(int ID, BUTTON b);
int GetButtonDown(int id, BUTTON b);
int GetButtonUp(BUTTON b);
int GetTrigger(SIDE trigger);
int GetTriggerDown(SIDE trigger);
int GetTriggerUp(SIDE trigger);
int GetTriggerAnalog(SIDE trigger);
void ControllerVibrate(int id, float a_fLeftMotor, float a_fRightMotor);
int BatteryInfo(int ID);
int GetStartButton(void);
int GetBackButton(void);
int GetDpadButton(int button);
int InputLeft(void);
int InputRight(void);
int InputUp(void);
int InputDown(void);
void PrintBatteryInfo(void);
int ControllerisConnected(int ID);

//---------------------------------------------------------
// Private Functions:
//---------------------------------------------------------
static void UpdateControllerState(int id);