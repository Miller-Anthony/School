//---------------------------------------------------------
// file:	Input.c
// author:	Akshat Madan
// brief:	Gamepad support using XINPUT
//
// Copyright © 2019 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "stdafx.h"
#include <stdio.h>
#include <math.h>
#include <Windows.h>
#include <xinput.h>
#include "Input.h"
#include "AEEngine.h"
#pragma comment(lib, "XInput.lib")

//---------------------------------------------------------
// Private Consts:
//---------------------------------------------------------
static const float DEADZONE_X = 0.08f;
static const float DEADZONE_Y = 0.08f;
static const int TRIG_THRESH = 75;
//---------------------------------------------------------
// Private Variables:
//---------------------------------------------------------
static XINPUT_STATE state;
static DWORD state_result;
static int connected = 0;
/* 
 * Index - Button Name
 * 0 - A
 * 1 - B
 * 2 - X
 * 3 - Y
 * 4 - Left Bumper
 * 5 - Right Bumper
 * 6 - Left Trig Value
 * 7 - Right Trig Value
 */
static int buttonsActive[8], buttonsPressed[8], buttonsReleased[8] = { 0 };
static int buttonsActive1[8], buttonsPressed1[8], buttonsReleased1[8] = { 0 };

static int startTemp = 0;
static int startActive = 0;
//---------------------------------------------------------
// Set whether to return trigger values as on/off or 0-255

/*************************************************************************\
   Function:  GetTrigger
Description:  Get the value of either trigger in the current mode
	 Inputs:  Which side trigger
	Outputs:  Integer of trigger pressed
	 Author:  Akshat Madan
\*************************************************************************/
int GetTrigger(SIDE trigger)
{
	if (connected)
		return buttonsActive[trigger + 6] > TRIG_THRESH;
	return 0;
}

/*************************************************************************\
   Function:  GetTriggerDown
Description:  Get the value of either trigger FULLY DOWN in the current mode
	 Inputs:  Which side trigger
	Outputs:  Integer of trigger pressed
	 Author:  Akshat Madan
\*************************************************************************/
int GetTriggerDown(SIDE trigger)
{
	if (connected)
		return buttonsPressed[trigger + 6];
	return 0;
}

/*************************************************************************\
   Function:  GetTriggerUp
Description:  Get the value of either trigger FULLY UP in the current mode
	 Inputs:  Which side trigger
	Outputs:  Integer of trigger pressed
	 Author:  Akshat Madan
\*************************************************************************/
int GetTriggerUp(SIDE trigger)
{
	if (connected)
		return buttonsReleased[trigger + 6];
	return 0;
}
/*************************************************************************\
   Function:  GetTriggerAnalog
Description:  Get the value of either trigger midvalue in the current mode
	 Inputs:  Which side trigger
	Outputs:  Integer of trigger pressed
	 Author:  Akshat Madan
\*************************************************************************/
int GetTriggerAnalog(SIDE trigger)
{
	if(connected)
		return buttonsActive[trigger + 6];
	return 0;
}

/*************************************************************************\
   Function:  GetButton
Description:  Get whether a given button is pressed or not
	 Inputs:  Which button
	Outputs:  Integer of trigger pressed
	 Author:  Akshat Madan
\*************************************************************************/
int GetButton(int ID, BUTTON b)
{
	/* If the controller is not connected, return 0 */
	if (!connected)
		return 0;

  if (ID == 0)
  {
      /* Check the bit that matches the requested button and return its state */
      if (b <= 6 && b >= 0)
          return buttonsActive[b];
      return 0;
  }
  else
  {
      /* Check the bit that matches the requested button and return its state */
      if (b <= 6 && b >= 0)
          return buttonsActive1[b];
      return 0;
  }
}

/*************************************************************************\
   Function:  GetButtonDown
Description:  Get whether a given button is pressed or not
	 Inputs:  Which button
	Outputs:  Integer of trigger pressed
	 Author:  Akshat Madan
\*************************************************************************/
int GetButtonDown(int id, BUTTON b)
{
	/* If the controller is not connected, return 0 */
	if (!connected)
		return 0;

	if (id == 0)
	{
		/* Check the bit that matches the requested button and return its state */
		if (b <= 6 && b >= 0)
			return buttonsPressed[b];
	}
	else if (id == 1)
	{
			/* Check the bit that matches the requested button and return its state */
			if (b <= 6 && b >= 0)
				return buttonsPressed1[b];
	}

	return 0;
}
/*************************************************************************\
   Function:  GetButtonUp
Description:  Get whether a given button is pressed or not
	 Inputs:  Which button
	Outputs:  Integer of trigger pressed
	 Author:  Akshat Madan
\*************************************************************************/
int GetButtonUp(BUTTON b)
{
	/* If the controller is not connected, return 0 */
	if (!connected)
		return 0;

	/* Check the bit that matches the requested button and return its state */
	if (b <= 6 && b >= 0)
		return buttonsReleased[b];
	return 0;
}

/*************************************************************************\
   Function:  GetJoystickX
Description:  Get the x-value of either joystick
	 Inputs:  Which side joystick
	Outputs:  Integer of joystick X
	 Author:  Akshat Madan
\*************************************************************************/
float GetJoystickX(SIDE stick) {
	if (connected) {
		/*
		 * Put the X value of the correct stick into a range of -1 to 1.
		 * Do this by dividing by the max value (32767), then clamping that at -1 minimum,
		 * as the minimum regular value (-32768) will result slightly lower than -1
		 */
		float normX = (float)(!stick ? fmax(-1.0f, (float)state.Gamepad.sThumbLX / 32767) : fmax(-1.0f, (float)state.Gamepad.sThumbRX / 32767));
		/*
		 * If the value is outside the deadzone, adjust it so the range starts at the end
		 * of the deadzone instead of the center, otherwise it is in the deadzone, so set the value to 0
		 */
		float xVal = (float)(fabs(normX) < DEADZONE_X ? 0 : (fabs(normX) - DEADZONE_X) * (normX / fabs(normX)));
		/* Scale the new value between -1 and 1 */
		xVal *= 1 / (1 - DEADZONE_X);

		/* Return the scaled value */
		return xVal;
	}
	return 0;
}

/*************************************************************************\
   Function:  GetJoystickY
Description:  Get the y-value of either joystick
	 Inputs:  Which side joystick
	Outputs:  Integer of joystick Y
	 Author:  Akshat Madan
\*************************************************************************/
float GetJoystickY(SIDE stick)
{
	if (connected)
	{
		/*
		 * Put the Y value of the correct stick into a range of -1 to 1.
		 * Do this by dividing by the max value (32767), then clamping that at -1 minimum,
		 * as the minimum regular value (-32768) will result slightly lower than -1
		 */
		float normY = (float)(!stick ? fmax(-1, (float)state.Gamepad.sThumbLY / 32767) : fmax(-1, (float)state.Gamepad.sThumbRY / 32767));
		/*
		 * If the value is outside the deadzone, adjust it so the range starts at the end
		 * of the deadzone instead of the center, otherwise it is in the deadzone, so set the value to 0
		 */
		float yVal = (float)(fabs(normY) < DEADZONE_Y ? 0 : (fabs(normY) - DEADZONE_Y) * (normY / fabs(normY)));
		/* Scale the new value between -1 and 1 */
		yVal *= 1 / (1 - DEADZONE_Y);

		/* Return the scaled value */
		return yVal;
	}
	return 0;
}

/*************************************************************************\
   Function:  GetStartButton
Description:  Check to see if the Start button is pressed
	 Inputs:  None
	Outputs:  Integer boolean
	 Author:  Akshat Madan
\*************************************************************************/
int GetStartButton(void)
{
	UpdateControllerState(0);
	startTemp = 0;

	if (connected)
	{
		startTemp = state.Gamepad.wButtons & XINPUT_GAMEPAD_START;
		if (startTemp && !startActive)
		{
			startActive = startTemp;
			return 1;
		}
		else if (!startTemp && startActive)
		{
			startActive = 0;
			return 0;
		}
		else
			return 0;
	}
	else
	{
		return 0;
	}
}

/*************************************************************************\
   Function:  GetBackButton
Description:  Check to see if the Back button is pressed
	 Inputs:  None
	Outputs:  Integer boolean
	 Author:  Akshat Madan
\*************************************************************************/
int GetBackButton(void)
{
	if (connected)
	{
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK)
			return 1;
		else
			return 0;
	}
	else
	{
		return 0;
	}
}

/*************************************************************************\
   Function:  GetDpadButton
Description:  Check to see if the Dpad is pressed
	 Inputs:  Which DPAD button to check
	Outputs:  Integer boolean
	 Author:  Akshat Madan
\*************************************************************************/
int GetDpadButton(int button)
{
	/*
	 * 0 - DPAD UP
	 * 1 - DPAD RIGHT
	 * 2 - DPAD DOWN
	 * 3 - DPAD LEFT
	 */

	int returnVal = 0;

	if (connected)
	{
		if(button == 0)
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
				returnVal = 1;
		if(button == 1)
			if(state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
				returnVal = 1;
		if (button == 2)
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
				returnVal = 1;
		if (button == 3)
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
				returnVal = 1;
	}

	return returnVal;
}

/*************************************************************************\
   Function:  InputInit
Description:  Initialize the input system
	 Inputs:  None
	Outputs:  None
	 Author:  Akshat Madan
\*************************************************************************/
void InputInit(int id)
{
	/* Check if the controller is connected, and read the initial state */
	UpdateControllerState(id);
	/* Check the return flag from reading the state */
	if (state_result == ERROR_SUCCESS)
		/* If there was no error, set the controller connected flag to true */
		connected = 1;
	else
	{
		/* If there was an error, the controller is not connected, set the flag accordingly */
		connected = 0;
		puts("No controller detected!\n");
	}
}

/*************************************************************************\
   Function:  InputUpdate
Description:  Update the input system
	 Inputs:  None
	Outputs:  None
	 Author:  Akshat Madan
\*************************************************************************/
void InputUpdate(int id)
{
	if (connected)
	{
		UpdateControllerState(id);
	}
}

/*************************************************************************\
   Function:  ControllerVibrate
Description:  Controls the vibration motors of the specified controller
	 Inputs:  Controller ID, Left Motor, Right Motor
	Outputs:  None
	 Author:  Akshat Madan
\*************************************************************************/
void ControllerVibrate(int id, float a_fLeftMotor, float a_fRightMotor)
{
	XINPUT_VIBRATION VibrationState;

	// Zero memory
	ZeroMemory(&VibrationState, sizeof(XINPUT_VIBRATION));

	// Calculate vibration values
	int iLeftMotor = (int)(a_fLeftMotor * 65535.0f);
	int iRightMotor = (int)(a_fRightMotor * 65535.0f);

	// Set vibration values
	VibrationState.wLeftMotorSpeed = (WORD)iLeftMotor;
	VibrationState.wRightMotorSpeed = (WORD)iRightMotor;

	// Set the vibration state
	XInputSetState(id, &VibrationState);
}

/*************************************************************************\
   Function:  BatteryInfo
Description:  Controller 0s battery info
	 Inputs:  None
	Outputs:  Battery info enum
	 Author:  Akshat Madan
\*************************************************************************/
int BatteryInfo(int ID)
{
	/*
	 * 0 - Disconnected
	 * 1 - Wired Controller
	 * 2 - Empty Battery
	 * 3 - Low Battery
	 * 4 - Medium Battery
	 * 5 - High Battery
	 */

	XINPUT_BATTERY_INFORMATION BatteryInformation;
	XInputGetBatteryInformation(ID, BATTERY_DEVTYPE_GAMEPAD, &BatteryInformation);

	if (BatteryInformation.BatteryType == BATTERY_TYPE_DISCONNECTED)
		return 0;
	else if (BatteryInformation.BatteryType == BATTERY_TYPE_WIRED)
		return 1;
	else if (BatteryInformation.BatteryLevel == BATTERY_LEVEL_EMPTY)
		return 2;
	else if (BatteryInformation.BatteryLevel == BATTERY_LEVEL_LOW)
		return 3;
	else if (BatteryInformation.BatteryLevel == BATTERY_LEVEL_MEDIUM)
		return 4;
	else if (BatteryInformation.BatteryLevel == BATTERY_LEVEL_FULL)
		return 5;
	else
		return 0;
}

/*************************************************************************\
   Function:  InputLeft
Description:  Checks if Input Left is met.
	 Inputs:  None
	Outputs:  Int, true or false
	 Author:  Akshat Madan
\*************************************************************************/
int InputLeft(void)
{
	return GetJoystickX(SIDE_L) < -0.25f || GetDpadButton(3) || AEInputCheckCurr('A');
}

/*************************************************************************\
   Function:  InputRight
Description:  Checks if Input Right is met.
	 Inputs:  None
	Outputs:  Int, true or false
	 Author:  Akshat Madan
\*************************************************************************/
int InputRight(void)
{
	return GetJoystickX(SIDE_L) > 0.25f || GetDpadButton(1) || AEInputCheckCurr('D');
}

/*************************************************************************\
   Function:  InputUp
Description:  Checks if Input Up is met.
	 Inputs:  None
	Outputs:  Int, true or false
	 Author:  Akshat Madan
\*************************************************************************/
int InputUp(void)
{
	return GetJoystickY(SIDE_L) > 0.25f || GetDpadButton(0) || AEInputCheckCurr('W');
}

/*************************************************************************\
   Function:  InputDown
Description:  Checks if Input Down is met.
	 Inputs:  None
	Outputs:  Int, true or false
	 Author:  Akshat Madan
\*************************************************************************/
int InputDown(void)
{
	return GetJoystickY(SIDE_L) < -0.25f || GetDpadButton(2) || AEInputCheckCurr('S');
}

/*************************************************************************\
   Function:  PrintBatteryInfo
Description:  Prints battery info to AESys Console
	 Inputs:  None
	Outputs:  None
	 Author:  Akshat Madan
\*************************************************************************/
void PrintBatteryInfo(void)
{
	int info = BatteryInfo(0);

	if (info == 0)
		AESysPrintf("Controller Disconnected");
	else if (info == 1)
		AESysPrintf("Wired Controller Connected");
	else if (info == 2)
		AESysPrintf("Empty Battery");
	else if (info == 3)
		AESysPrintf("Low Battery");
	else if (info == 4)
		AESysPrintf("Medium Battery");
	else if (info == 5)
		AESysPrintf("Full Battery");
	else
		AESysPrintf("Controller Disconnected");

	if (GetTriggerDown(SIDE_R) || GetButtonDown(0, 2))
	{
		AESysPrintf("Light Attack!\n");
		ControllerVibrate(0, 0.0f, 0.5f);
	}
	if (GetTriggerUp(SIDE_R) || GetButtonUp(2))
		ControllerVibrate(0, 0.0f, 0.0f);

	if (GetTriggerDown(SIDE_L) || GetButtonDown(0, 1))
	{
		AESysPrintf("Block!\n");
		ControllerVibrate(0, 0.0f, 0.5f);
	}
	if (GetTriggerUp(SIDE_L) || GetButtonUp(1))
		ControllerVibrate(0, 0.0f, 0.0f);

	if (GetButtonDown(0, 5) || GetButtonDown(0, 3))
	{
		AESysPrintf("Heavy Attack!\n");
		ControllerVibrate(0, 0.5f, 0.0f);
	}
	if (GetButtonUp(5) || GetButtonUp(3))
		ControllerVibrate(0, 0.0f, 0.0f);

	if (GetButtonDown(0, 4) || GetButtonDown(0, 0))
	{
		AESysPrintf("Portion Dranked!\n");
		ControllerVibrate(0, 0.0f, 0.5f);
	}
	if (GetButtonUp(4) || GetButtonUp(0))
		ControllerVibrate(0, 0.0f, 0.0f);
}

int ControllerisConnected(int ID)
{
	state_result = XInputGetState(ID, &state);

	/* Check if there were any errors */
	if (state_result != ERROR_SUCCESS)
		return 0;
	else
		return 1;
}
//---------------------------------------------------------
// Private Functions:
//---------------------------------------------------------

/*************************************************************************\
   Function:  UpdateControllerState
Description:  Update the state of the specified controller
	 Inputs:  Controller ID
	Outputs:  None
	 Author:  Akshat Madan
\*************************************************************************/
static void UpdateControllerState(int id)
{
	int temp[8] = { 0 };
	int i;
	/* Read the state of controller ID 0, and store it in our state variable. Store the return code in state_result */
	state_result = XInputGetState(id, &state);

	/* Check if there were any errors */
	if (state_result != ERROR_SUCCESS)
	{
		/* If there was an error, the controller is not connected, set our flag accordingly */
		connected = 0;
	}
	else
	{
		if (id == 0)
		{
			temp[0] = state.Gamepad.wButtons & XINPUT_GAMEPAD_A;
			temp[1] = state.Gamepad.wButtons & XINPUT_GAMEPAD_B;
			temp[2] = state.Gamepad.wButtons & XINPUT_GAMEPAD_X;
			temp[3] = state.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
			temp[4] = state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER;
			temp[5] = state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER;
			temp[6] = state.Gamepad.bLeftTrigger;
			temp[7] = state.Gamepad.bRightTrigger;

			for (i = 0; i < 6; ++i)
			{
				if (temp[i] && !buttonsActive[i])
					buttonsPressed[i] = 1;
				else
					buttonsPressed[i] = 0;

				if (!temp[i] && buttonsActive[i])
					buttonsReleased[i] = 1;
				else
					buttonsReleased[i] = 0;

				buttonsActive[i] = temp[i];
			}

			/* Update states for left trigger */
			if (temp[6] > TRIG_THRESH && buttonsActive[6] < TRIG_THRESH)
				buttonsPressed[6] = 1;
			else
				buttonsPressed[6] = 0;
			if (temp[6] < TRIG_THRESH && buttonsActive[4] > TRIG_THRESH)
				buttonsReleased[6] = 1;
			else
				buttonsReleased[6] = 0;
			buttonsActive[6] = temp[6];

			/* Update states for right trigger*/
			if (temp[7] > TRIG_THRESH && buttonsActive[7] < TRIG_THRESH)
				buttonsPressed[7] = 1;
			else
				buttonsPressed[7] = 0;
			if (temp[7] < TRIG_THRESH && buttonsActive[7] > TRIG_THRESH)
				buttonsReleased[7] = 1;
			else
				buttonsReleased[7] = 0;
			buttonsActive[7] = temp[7];
		}

		if (id == 1)
		{
			temp[0] = state.Gamepad.wButtons & XINPUT_GAMEPAD_A;
			temp[1] = state.Gamepad.wButtons & XINPUT_GAMEPAD_B;
			temp[2] = state.Gamepad.wButtons & XINPUT_GAMEPAD_X;
			temp[3] = state.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
			temp[4] = state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER;
			temp[5] = state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER;
			temp[6] = state.Gamepad.bLeftTrigger;
			temp[7] = state.Gamepad.bRightTrigger;

			for (i = 0; i < 6; ++i)
			{
				if (temp[i] && !buttonsActive1[i])
					buttonsPressed1[i] = 1;
				else
					buttonsPressed1[i] = 0;

				if (!temp[i] && buttonsActive1[i])
					buttonsReleased1[i] = 1;
				else
					buttonsReleased1[i] = 0;

				buttonsActive1[i] = temp[i];
			}

			/* Update states for left trigger */
			if (temp[6] > TRIG_THRESH && buttonsActive1[6] < TRIG_THRESH)
				buttonsPressed1[6] = 1;
			else
				buttonsPressed1[6] = 0;
			if (temp[6] < TRIG_THRESH && buttonsActive1[4] > TRIG_THRESH)
				buttonsReleased1[6] = 1;
			else
				buttonsReleased1[6] = 0;
			buttonsActive1[6] = temp[6];

			/* Update states for right trigger*/
			if (temp[7] > TRIG_THRESH && buttonsActive1[7] < TRIG_THRESH)
				buttonsPressed1[7] = 1;
			else
				buttonsPressed[7] = 0;
			if (temp[7] < TRIG_THRESH && buttonsActive1[7] > TRIG_THRESH)
				buttonsReleased1[7] = 1;
			else
				buttonsReleased1[7] = 0;
			buttonsActive1[7] = temp[7];
		}
	}
}