/******************************************************************************
   Function: playerMovement

Description: Controls player movement depending on the friction of the material
             as well as the max speed, and acceleration
             
     Inputs: velocityX        - the x-axis velocity of the player
            
             velocityY        - the y-axis velocity of the player
             
             playerPosisionX  - the x-axis position of the player
             
             playerPosisionY  - the y-axis position of the player
             
             materialMaxSpeed - what the players max velocity will be set as
             
             acceleration     - how fast the player speeds up to the max velocity
             
             friction         - the slow down rate of the players velocity 
             
             direction        - PASS IN AN INT OF 1 or -1, the direction of the player
      
    Outputs: N/A
******************************************************************************/
void playerMovement(float *velocityX, float *velocityY, float *playerPosisionX, float *playerPosisionY, 
					const int materialMaxSpeed, const float acceleration, const float friction, int *direction)
{
	int MINSPEED = 0;
	float playerPosisionPreX;
	float playerPosisionPreY;


	//move right
	if (keyIsDown(KEY_D))
	{
		*velocityY = 1.1;

		// flips sprite to correct direction
		*direction = 1;

		//sets last position to the current
		playerPosisionPreX = *playerPosisionX;
		playerPosisionPreY = *playerPosisionY;

		// sets to min speed
		if (*velocityX < MINSPEED)
			*velocityX = MINSPEED;

		// adds to the player position by the velocity
		*playerPosisionX += *velocityX * (1.5 / 30.0) * *direction;

		// sets velocity to max speed 
		if (*velocityX >= materialMaxSpeed)
			*velocityX = materialMaxSpeed;

		// increases play velocity while pressed
		else if (*velocityX < materialMaxSpeed)
		{
			*velocityX *= acceleration;
		}
	}
	// move left
	else if (keyIsDown(KEY_A))
	{
		*velocityY = 1.1;

		// flips sprite to correct direction
		*direction = -1;

		//sets last position to the current
		playerPosisionPreX = *playerPosisionX;
		playerPosisionPreY = *playerPosisionY;

		// sets to min speed
		if (*velocityX < MINSPEED)
			*velocityX = MINSPEED;

		// adds to the player position by the velocity
		*playerPosisionX += *velocityX * (1.5 / 30.0) * *direction;

		// sets velocity to max speed 
		if (*velocityX >= materialMaxSpeed)
			*velocityX = materialMaxSpeed;

		// increases play velocity while pressed
		else if (*velocityX < materialMaxSpeed)
			*velocityX *= acceleration;
	}
	else
	{
		//decrease velocity until the MINSPEED
		if (abs(*velocityX) > MINSPEED)
			*velocityX *= friction;

		//makes sure you dont have negative velocity
		else if (abs(*velocityX) <= MINSPEED)
			*velocityX = 1.1;

		if (*velocityX <= 1.15)
			*playerPosisionX = *playerPosisionX;
		//30 is frame rate, decreases in the direction you are going
		else
			*playerPosisionX += *velocityX * (1.0 / 30.0) * *direction;
	}

	//move down
	if (keyIsDown(KEY_S))
	{
		*velocityX = 1.1;

		// flips sprite to correct direction
		*direction = 1;

		//sets last position to the current
		playerPosisionPreX = *playerPosisionX;
		playerPosisionPreY = *playerPosisionY;

		// sets to min speed
		if (*velocityY < MINSPEED)
			*velocityY = MINSPEED;

		// adds to the player position by the velocity
		*playerPosisionY += *velocityY * (1.5 / 30.0) * *direction;

		// sets velocity to max speed 
		if (*velocityY >= materialMaxSpeed)
			*velocityY = materialMaxSpeed;

		// increases play velocity while pressed
		else if (*velocityY < materialMaxSpeed)
			*velocityY *= acceleration;
	}
	// move up
	else if (keyIsDown(KEY_W))
	{

		*velocityX = 1.1;

		// flips sprite to correct direction
		*direction = -1;

		//sets last position to the current
		playerPosisionPreX = *playerPosisionX;
		playerPosisionPreY = *playerPosisionY;

		// sets to min speed
		if (*velocityY < MINSPEED)
			*velocityY = MINSPEED;

		// adds to the player position by the velocity
		*playerPosisionY += *velocityY * (1.5 / 30.0) * *direction;

		// sets velocity to max speed 
		if (*velocityY >= materialMaxSpeed)
			*velocityY = materialMaxSpeed;

		// increases play velocity while pressed
		else if (*velocityY < materialMaxSpeed)
			*velocityY *= acceleration;
	}
	//while no keys pressed
	else
	{
		//decrease velocity until the MINSPEED
		if (abs(*velocityY) > MINSPEED)
			*velocityY *= friction;
		//makes sure you dont have negative velocity
		else if (abs(*velocityY) <= MINSPEED)
			*velocityY = 1.1;

		if (*velocityY <= 1.15)
			*playerPosisionY = *playerPosisionY;
		//30 is frame rate, decreases in the direction you are going
		else
			*playerPosisionY += *velocityY * (1.0 / 30.0) * *direction;
	}
}