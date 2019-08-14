//------------------------------------------------------------------------------
//
// File Name:	ScoreSystem.h
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 6
// Course:		CS230S19
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

typedef enum
{
	SsiInvalid = -1,
	SsiScore,
	SsiHighScore,
	SsiWaveCount,
	SsiMax,
} ScoreSystemId;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Initialize the Score system.
// (NOTE: All private variables must be initialized to 0.)
// (NOTE: There should be separate values for Score, High Score, and Wave.)
void ScoreSystemInit();

// Restart the Score system after updating the high score.
// (HINT: The high score value should be updated before zeroing out the score and wave variables.
void ScoreSystemRestart();

// Get the specified score system value.
// (Hint: Check to make sure that ssid is between SsiInvalid and SsiMax (non-inclusive).)
// Params:
//	 ssid = The score system value to be returned.
// Returns:
//	 If "ssid" is a valid index,
//	   then return the value associated with that index,
//	   else return 0.
int ScoreSystemGetValue(ScoreSystemId ssid);

// Increase the game score by score value.
// Params:
//	 scoreValue = The amount to be added to the game score.
void ScoreSystemIncreaseScore(unsigned int scoreValue);

// Increase the wave count by 1.
void ScoreSystemIncreaseWaveCount();

//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

