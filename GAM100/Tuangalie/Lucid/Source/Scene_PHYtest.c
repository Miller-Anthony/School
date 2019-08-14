//---------------------------------------------------------
// file:	Scene_PHYtest.c
// author:	Tristan Bouchard
// brief:	Level Select scene functions
// Course: GAM100F18
// Copyright © 2018 DigiPen, All rights reserved.
//---------------------------------------------------------
#pragma once

//All code in this file done by Tristan Bouchard

#include "C_Processing.h"
#include "Scene_PHYtest.h"
#include "SceneManager.h"
#include "windows.h"
#include "Scene_PHYtest.h"
#include <stdlib.h>
#include <math.h>

void ScenePHYtestInit()
{
	setFrameRate(60);
	size(1920, 1080);
	background(100, 40, 200);
	fadeLoad();
}

void ScenePHYtestUpdate()
{
	background(255, 0, 255);
	fadein();
	fadeout();
}


//================================================================FUNCTIONS===============================================================

//MOVE PLAYER
void enableMOVEMENT(float *positionX, float *positionY, float *velocityX, float *velocityY)
{
	*positionX += *velocityX * dt(); //moves player
	*positionY += *velocityY * dt(); //moves player
}

//ENABLE RIGHT AND LEFT MOVEMENT
void enableRIGHTLEFT(float *velocityX, float accelerationX, float decelerarion, int max_speed)
{
	//MOVE LEFT(A) AND RIGHT(D)
	if (keyIsDown(KEY_D) && !keyIsDown(KEY_A))
	{
		if (abs(*velocityX) < max_speed)	    //if not
			*velocityX += accelerationX * dt(); //can add to velocity
	}
	if (keyIsDown(KEY_A) && !keyIsDown(KEY_D))
	{
		if (abs(*velocityX) < max_speed)	         //if not
			*velocityX += -1 * accelerationX * dt(); //can add to velocity
	}
	if ((!keyIsDown(KEY_A) && !keyIsDown(KEY_D)) || (keyIsDown(KEY_A) && keyIsDown(KEY_D)))
	{
		//*positionX += *velocityX * dt(); //moves player
		*velocityX *= decelerarion;	 //reduces velocity
	}
}

//ENABLE UP AND DOWN MOVEMENT
void enableUPDOWN(float *velocityY, float accelerationY, float decelerarion, int max_speed)
{
	//MOVE UP (W) AND DOWN (S)
	if (keyIsDown(KEY_S) && !keyIsDown(KEY_W))
	{
		if (abs(*velocityY) < max_speed)	    //if player hasnt hit max speed
			*velocityY += accelerationY * dt(); //can add to velocity
	}
	if (keyIsDown(KEY_W) && !keyIsDown(KEY_S))
	{
		if (abs(*velocityY) < max_speed)	         //if not hit max speed
			*velocityY += -1 * accelerationY * dt(); //can add to velocity
	}
	if ((!keyIsDown(KEY_W) && !keyIsDown(KEY_S)) || (keyIsDown(KEY_W) && keyIsDown(KEY_S)))
	{
		*velocityY *= decelerarion;	     //reduces velocity
	}
}

//ENABLES ALL MOVEMENT
void enableALLMOVEMENT(float *positionY, float *positionX, float *velocityY, float *velocityX, float accelerationY, float accelerationX, float decelerarion, int max_speed)
{
	enableRIGHTLEFT(&velocityX, accelerationX, decelerarion, max_speed); //enabels right and left movement
	enableUPDOWN(&velocityY, accelerationY, decelerarion, max_speed);    //enables up and down movement
}

//COLLISION DRAW ATTACHED TO PLAYER MOVEMENT
void disableMOVEMENT(float *positionX, float *positionY, float charWidth, float charHeight, float *velocityX, float *velocityY, float X, float Y, float W, float H, int SeeCollision)
{

//==============================COLORS FOR COLLISION CHECKS=========================================================
	PColor yelloish = color(192, 255, 0, 255);
	PColor sand = color(232, 139, 2, 255);
	PColor blueish = color(29, 12, 232, 255);
	PColor lightblue = color(13, 255, 211, 255);
	PColor magenta = color(255, 0, 81, 255);
	PColor orange = color(255, 84, 0, 255);
	PColor purple = color(202, 2, 232, 255);
	PColor greenish = color(12, 232, 76, 255);
	PColor redish = color(255, 40, 0, 255);
	PColor lime = color(0, 232, 147, 255);
	PColor blackish = color(0, 0, 0, 255);
//==================================================================================================================

//================MAP ALL CORNER POINTS BASED OFF SHORTEST SIDE OF COLLISION AND PLAYER=============================
	int comp1 = 0;
	int comp2 = 0;
	int halfSize = 0;

	if (charWidth < W)
		comp1 = charWidth;
	else
		comp1 = W;
	if (charHeight < H)
		comp2 = charHeight;
	else
		comp2 = H;
	if (comp1 < comp2)
		halfSize = comp1 / 2;
	else
		halfSize = comp2 / 2;

	noStroke();
//===================================================================================================================

//======================BOX COLLISION================================================================================
	vec2_t ORC = { X , Y };         //origin OF collision
	vec2_t MRC = { X + W / 2 , Y }; //middle right collidion
	vec2_t MLC = { X - W / 2 , Y }; //middle left collision
	vec2_t MUC = { X , Y - H / 2 }; //middle upper collision
	vec2_t MDC = { X , Y + H / 2 }; //middle down collidion

	//top LEFT COLLISION
	vec2_t TLLCC = { X - W / 2 , Y - H / 2 };   //TOP LEFT LEFT CORNER COLLISION
	vec2_t TLTMC = { TLLCC.x + halfSize, TLLCC.y };  //TOP LEFT TOP MIDDLE COLLISION
	vec2_t TLLMC = { TLLCC.x , TLLCC.y + halfSize }; //TOP LEFT LEFT MIDDLE COLLISION

	if (SeeCollision)
	{
		fillColor(redish);
		circle(TLLCC.x, TLLCC.y, 5);
		circle(TLTMC.x, TLTMC.y, 5);
		circle(TLLMC.x, TLLMC.y, 5);
	}

	//bottom LEFT COLLISION
	vec2_t BLLCC = { X - W / 2 , Y + H / 2 };   //BOTTOM LEFT LEFT CORNER COLLISION
	vec2_t BLBMC = { BLLCC.x + halfSize , BLLCC.y }; //BOTTOM LEFT BOTTOM MIDDLE COLLISION
	vec2_t BLLMC = { BLLCC.x , BLLCC.y - halfSize }; //BOTTOM LEFT LEFT MIDDLE COLLISION

	if (SeeCollision)
	{
		fillColor(blueish);
		circle(BLLCC.x, BLLCC.y, 5);
		circle(BLBMC.x, BLBMC.y, 5);
		circle(BLLMC.x, BLLMC.y, 5);
	}


	//top RIGHT COLLISION
	vec2_t TRRCC = { X + W / 2 , Y - H / 2 };   //TOP RIGHT RIGHT CORNER COLLISION
	vec2_t TRTMC = { TRRCC.x - halfSize , TRRCC.y }; //TOP RIGHT TOP MIDDLE COLLISION
	vec2_t TRRMC = { TRRCC.x , TRRCC.y + halfSize }; //TOP RIGHT RIGHT MIDDLE COLLISION

	if (SeeCollision)
	{
		fillColor(greenish);
		circle(TRRCC.x, TRRCC.y, 5);
		circle(TRTMC.x, TRTMC.y, 5);
		circle(TRRMC.x, TRRMC.y, 5);
	}


	//bottom RIGHT COLLISION
	vec2_t BRRCC = { X + W / 2 , Y + H / 2 };   //BOTTOM RIGHT RIGHT CORNER COLLISION
	vec2_t BRBMC = { BRRCC.x - halfSize , BRRCC.y }; //BOTTOM RIGHT BOTTOM MIDDLE COLLISION
	vec2_t BRRMC = { BRRCC.x , BRRCC.y - halfSize }; //BOTTOM RIGHT RIGHT MIDDLE COLLISION

	if (SeeCollision)
	{
		fillColor(purple);
		circle(BRRCC.x, BRRCC.y, 5);
		circle(BRBMC.x, BRBMC.y, 5);
		circle(BRRMC.x, BRRMC.y, 5);
	}
//=================================================================================================================

//====================PLAYER COLLISION=============================================================================
	vec2_t ORP = { *positionX , *positionY };                  //origin player
	vec2_t MRP = { *positionX + charWidth / 2 , *positionY };  //middle right player
	vec2_t MLP = { *positionX - charWidth / 2 , *positionY };  //middle left player
	vec2_t MUP = { *positionX , *positionY - charHeight / 2 }; //middle upper player
	vec2_t MDP = { *positionX , *positionY + charHeight / 2 }; //middle down player


	//top LEFT PLAYER
	vec2_t TLLCP = { *positionX - charWidth / 2 , *positionY - charHeight / 2 };  //TOP LEFT LEFT CORNER PLAYER
	vec2_t TLTMP = { TLLCP.x + halfSize , TLLCP.y };                                   //TOP LEFT TOP MIDDLE PLAYER
	vec2_t TLLMP = { TLLCP.x , TLLCP.y + halfSize };                                   //TOP LEFT LEFT MIDDLE PLAYER

	if (SeeCollision)
	{
		fillColor(purple);
		circle(TLLCP.x, TLLCP.y, 5);
		circle(TLTMP.x, TLTMP.y, 5);
		circle(TLLMP.x, TLLMP.y, 5);
	}


	//bottom LEFT PLAYER
	vec2_t BLLCP = { *positionX - charWidth / 2 , *positionY + charHeight / 2 }; //BOTTOM LEFT LEFT CORNER PLAYER
	vec2_t BLBMP = { BLLCP.x + halfSize , BLLCP.y };                                  //BOTTOM LEFT BOTTOM MIDDLE PLAYER
	vec2_t BLLMP = { BLLCP.x , BLLCP.y - halfSize };                                  //BOTTOM LEFT LEFT MIDDLE PLAYER

	if (SeeCollision)
	{
		fillColor(greenish);
		circle(BLLCP.x, BLLCP.y, 5);
		circle(BLBMP.x, BLBMP.y, 5);
		circle(BLLMP.x, BLLMP.y, 5);
	}


	//top RIGHT PLAYER
	vec2_t TRRCP = { *positionX + charWidth / 2 , *positionY - charHeight / 2 };	  //TOP RIGHT RIGHT CORNER PLAYER
	vec2_t TRTMP = { TRRCP.x - halfSize , TRRCP.y };                                  //TOP RIGHT TOP MIDDLE PLAYER
	vec2_t TRRMP = { TRRCP.x , TRRCP.y + halfSize };                                  //TOP RIGHT RIGHT MIDDLE PLAYER

	if (SeeCollision)
	{
		fillColor(blueish);
		circle(TRRCP.x, TRRCP.y, 5);
		circle(TRTMP.x, TRTMP.y, 5);
		circle(TRRMP.x, TRRMP.y, 5);
	}


	//bottom RIGHT PLAYER
	vec2_t BRRCP = { *positionX + charWidth / 2 , *positionY + charHeight / 2 }; //BOTTOM RIGHT RIGHT CORNER PLAYER
	vec2_t BRBMP = { BRRCP.x - halfSize , BRRCP.y };                                  //BOTTOM RIGHT BOTTOM MIDDLE PLAYER
	vec2_t BRRMP = { BRRCP.x , BRRCP.y - halfSize };                                  //BOTTOM RIGHT RIGHT MIDDLE PLAYER

	if (SeeCollision)
	{
		fillColor(redish);
		circle(BRRCP.x, BRRCP.y, 5);
		circle(BRBMP.x, BRBMP.y, 5);
		circle(BRRMP.x, BRRMP.y, 5);
	}
	//=================================================================================================================

	//=====================DISTANCES===================================================================================
	float TRRQP_BLLQC_S = vec2_distance(TRRCP, BLLCC) + vec2_distance(TRRMP, BLLMC); //DISTANCE BETWEEN TOP RIGHT RIGHT PLAYER TO BOTTOM LEFT LEFT COLLISION
	float TRTQP_BLBQC_S = vec2_distance(TRRCP, BLLCC) + vec2_distance(TRTMP, BLBMC); //DISTANCE BETWEEN TOP RIGHT TOP PLAYER TO BOTTOM LEFT BOTTOM COLLISION
	float BRRQP_TLLQC_S = vec2_distance(BRRCP, TLLCC) + vec2_distance(BRRMP, TLLMC); //DISTANCE BETWEEN BOTTOM RIGHT RIGHT PLAYER TO TOP LEFT LEFT COLLITION
	float BRBQP_TLTQC_S = vec2_distance(BRRCP, TLLCC) + vec2_distance(BRBMP, TLTMC); //DISTANCE BETWEEN BOTTOM RIGHT BOTTOM PLAYER TO TOP LEFT TOP COLLIDION

	float TLLQP_BRRQC_S = vec2_distance(TLLCP, BRRCC) + vec2_distance(TLLMP, BRRMC); //DISTANCE BETWEEN TOP LEFT LEFT PLAYER TO BOTTOM RIGHT RIGHT COLLISION
	float TLTQP_BRBQC_S = vec2_distance(TLLCP, BRRCC) + vec2_distance(TLTMP, BRBMC); //DISTANCE BETWEEN TOP LEFT TOP PLAYER TO BOTTOM RIGHT BOTTOM COLLISION
	float BLLQP_TRRQC_S = vec2_distance(BLLCP, TRRCC) + vec2_distance(BLLMP, TRRMC); //DISTANCE BETWEEN BOTTOM LEFT LEFT PLAYER TO TOP RIGHT RIGHT COLLITION
	float BLBQP_TRTQC_S = vec2_distance(BLLCP, TRRCC) + vec2_distance(BLBMP, TRTMC); //DISTANCE BETWEEN BOTTOM LEFT BOTTOM PLAYER TO TOP RIGHT TOP COLLIDION
//==================================================================================================================

	//right side of player colliding with left side of collision
	if (MRP.x >= MLC.x && ORP.x < ORC.x && BRRCP.y > TLLCC.y && TRRCP.y < BLLCC.y && BRRQP_TLLQC_S < BRBQP_TLTQC_S && TRRQP_BLLQC_S < TRTQP_BLBQC_S)
	{
		*velocityX = 0;
		*positionX = MLC.x - charWidth / 2 - .1;
	}
	//bottom side of player colliding with top side of collidion
	if (MDP.y >= MUC.y && ORP.y < ORC.y && BRRCP.x > TLLCC.x && BLLCP.x < TRRCC.x && BRBQP_TLTQC_S < BRRQP_TLLQC_S && BLBQP_TRTQC_S < BLLQP_TRRQC_S)
	{
		*velocityY = 0;
		*positionY = MUC.y - charHeight / 2 - .1;
	}
	//left side of player colliding with right side of collision
	if (MLP.x <= MRC.x && ORP.x > ORC.x && BLLCP.y > TRRCC.y && TLLCP.y < BRRCC.y && BLLQP_TRRQC_S < BLBQP_TRTQC_S && TLLQP_BRRQC_S < TLTQP_BRBQC_S)
	{
		*velocityX = 0;
		*positionX = MRC.x + charWidth / 2 + .1;
	}
	//top side of player collidiing with bottom side of collision
	if (MUP.y <= MDC.y && ORP.y > ORC.y && TLLCP.x < BRRCC.x && TRRCP.x > BLLCC.x && TRTQP_BLBQC_S < TRRQP_BLLQC_S && TLTQP_BRBQC_S < TLLQP_BRRQC_S)
	{
		*velocityY = 0;
		*positionY = MDC.y + charHeight / 2 + .1;
	}

	strokeWeight(3);
	if (SeeCollision)
	{
		strokeColor(blackish);
		line(ORP.x, ORP.y, ORC.x, ORC.y);

		//TOP RIGHT PLAYER -> BOTTOM LEFT COLLISION
		strokeColor(blueish);
		line(TRRCP.x, TRRCP.y, BLLCC.x, BLLCC.y);
		line(TRTMP.x, TRTMP.y, BLLMC.x, BLLMC.y);
		line(TRRMP.x, TRRMP.y, BLBMC.x, BLBMC.y);

		//BOTTOM RIGHT PLAYER -> TOP LEFT COLLISION
		strokeColor(redish);
		line(BRRCP.x, BRRCP.y, TLLCC.x, TLLCC.y);
		line(BRBMP.x, BRBMP.y, TLLMC.x, TLLMC.y);
		line(BRRMP.x, BRRMP.y, TLTMC.x, TLTMC.y);

		//TOP LEFT PLAYER -> BOTTOM RIGHT COLLISION
		strokeColor(purple);
		line(TLLCP.x, TLLCP.y, BRRCC.x, BRRCC.y);
		line(TLTMP.x, TLTMP.y, BRRMC.x, BRRMC.y);
		line(TLLMP.x, TLLMP.y, BRBMC.x, BRBMC.y);

		//BOTTOM LEFT PLAYER -> BOTTOM RIGHT COLLISION
		strokeColor(greenish);
		line(BLLCP.x, BLLCP.y, TRRCC.x, TRRCC.y);
		line(BLBMP.x, BLBMP.y, TRRMC.x, TRRMC.y);
		line(BLLMP.x, BLLMP.y, TRTMC.x, TRTMC.y);
	}
}

//EVENT COLLISION
int eventCollision(float *positionX, float *positionY, float charWidth, float charHeight, float X, float Y, float W, float H)
{
	//======================BOX COLLISION================================================================================
	vec2_t ORC = { X , Y };         //origin OF collision
	vec2_t MRC = { X + W / 2 , Y }; //middle right collidion
	vec2_t MLC = { X - W / 2 , Y }; //middle left collision
	vec2_t MUC = { X , Y - H / 2 }; //middle upper collision
	vec2_t MDC = { X , Y + H / 2 }; //middle down collidion

	vec2_t ORP = { *positionX , *positionY };                  //origin player
	vec2_t MRP = { *positionX + charWidth / 2 , *positionY };  //middle right player
	vec2_t MLP = { *positionX - charWidth / 2 , *positionY };  //middle left player
	vec2_t MUP = { *positionX , *positionY - charHeight / 2 }; //middle upper player
	vec2_t MDP = { *positionX , *positionY + charHeight / 2 }; //middle down player

	//top LEFT COLLISION
	vec2_t TLLCC = { X - W / 2 , Y - H / 2 };   //TOP LEFT LEFT CORNER COLLISION
	//bottom LEFT COLLISION
	vec2_t BLLCC = { X - W / 2 , Y + H / 2 };   //BOTTOM LEFT LEFT CORNER COLLISION
	//top RIGHT COLLISION
	vec2_t TRRCC = { X + W / 2 , Y - H / 2 };   //TOP RIGHT RIGHT CORNER COLLISION
	//bottom RIGHT COLLISION
	vec2_t BRRCC = { X + W / 2 , Y + H / 2 };   //BOTTOM RIGHT RIGHT CORNER COLLISION
	//top LEFT PLAYER
	vec2_t TLLCP = { *positionX - charWidth / 2 , *positionY - charHeight / 2 };  //TOP LEFT LEFT CORNER PLAYER
	//bottom LEFT PLAYER
	vec2_t BLLCP = { *positionX - charWidth / 2 , *positionY + charHeight / 2 }; //BOTTOM LEFT LEFT CORNER PLAYER
	//top RIGHT PLAYER
	vec2_t TRRCP = { *positionX + charWidth / 2 , *positionY - charHeight / 2 };	  //TOP RIGHT RIGHT CORNER PLAYER
	//bottom RIGHT PLAYER
	vec2_t BRRCP = { *positionX + charWidth / 2 , *positionY + charHeight / 2 }; //BOTTOM RIGHT RIGHT CORNER PLAYER

	//magic happens/checks collision
	if ((MRP.x >= MLC.x && BRRCP.y > TLLCC.y && TRRCP.y < BLLCC.y) && (MDP.y >= MUC.y && BRRCP.x > TLLCC.x && BLLCP.x < TRRCC.x) && (MLP.x <= MRC.x && BLLCP.y > TRRCC.y && TLLCP.y < BRRCC.y) && (MUP.y <= MDC.y && TLLCP.x < BRRCC.x && TRRCP.x > BLLCC.x))
		return 1;
	else
		return 0;
}

//FRACTAL TREE DRAWING FUNCTION
void fractalTree(int length, float angle, int strokethick, int condistional)
{
	strokeWeight(1);
	stroke(255, 255, 255, 255);
	line(0, 0, 0, -length);
	translate(0, -length);
	if (length > condistional)
	{
		save();
		rotate(angle);
		fractalTree(length * 0.67, angle, strokethick, condistional);
		restore();

		save();
		rotate(-angle);
		fractalTree(length * 0.67, angle, strokethick, condistional);
		restore();
	}
}

// then in Update, draw the image based on the animation frame index
//image(images[animationIndex], posX, posY, imageWidth, imageHeight);

void mouseXY(void)
{
	//X coord
	char X[256] = { 0 };
	sprintf_s(X, _countof(X), "X = %f", getmouseX());
	text(X, 550, 1000);

	//Y coord
	char Y[256] = { 0 };

	sprintf_s(Y, _countof(Y), "Y = %f", getmouseY());
	text(Y, 920, 1000);
}


//COLLISION USING STRUCTS (not being used)
typedef struct AABB
{
	int x;
	int y;
	int h;
	int w;
} AABB;
//FUNCITON FOR SAID COLLISION
int collision_aabb(AABB* box_1, AABB* box_2)
{
	return ((box_1->x <= box_2->x + box_2->w) && (box_1->x + box_1->w >= box_2->x) && (box_1->y <= box_2->y + box_2->h) && (box_1->y + box_1->h >= box_2->y));
}