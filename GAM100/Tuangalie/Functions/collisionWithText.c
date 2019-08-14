/******************************************************************************
	Function: textcollision

Description: Uses the distance between a rectangle and player position,
			 and draws text if collided and when a key is pressed, an
			 action happens.

	  Inputs: textpos         - The position the text is to be drawn

			  fontsize        - The size of the text font

			  rectpos         - rectangle position

			  rectWidthHeight - height and width of rectangle

			  charpos         - player position

			  chardirection   - the direction the player is facing

	  Outputs:  VOID N/A
******************************************************************************/

void textCollisiton(vec2_t textpos, float fontsize, char *font, vec2_t rectpos,
	vec2_t rectWidthHeight, vec2_t charpos, int chardirection)
{
	
	//player distance from collision
	float distance = vec2_distance(rectpos, charpos);

	//draws inviable rectangle
	noFill();
	noStroke();
	fill(0, 0, 0, 255);
	rect(rectpos.x, rectpos.y, rectWidthHeight.x, rectWidthHeight.y);

	//collision
	if (distance <= rectWidthHeight.x / 2)
	{
		//while facing the collision, stop movement towards it
		if (chardirection == 1)
			velocity.x = MINSPEED;

		fill(255, 255, 255, 255);
		textFont(*font, fontsize);

		//text position is getting SUBTRACTED. enter positive number to change height and left/right
		text("Press E To Sleep", rectpos.x - textpos.x, rectpos.y - textpos.y);

		// when pressed, do something
		if (keyPressed(KEY_E))
		{
			//event here
		}
	}
}