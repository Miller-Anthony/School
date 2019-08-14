//---------------------------------------------------------
// File:	Scene_Room1.c
// Author:	Maverick Alexander / Anthony Miller
// Brief:   First Level in game
// Course: GAM100F18
// Copyright © 2018 DigiPen, All rights reserved.
//---------------------------------------------------------

#include <stdbool.h>
#include "C_Processing.h"
#include "Scene_Room1.h"
#include "SceneManager.h"
#include <windows.h>
#include "Scene_PHYtest.h"
#include "NPC.h"
#include <math.h>
#include "Desk.h"

#include <stdio.h>

//---------------------------------------------------------
// Private Consts:
//---------------------------------------------------------

//---------------------------------------------------------
// Private Structures:
//---------------------------------------------------------

//---------------------------------------------------------
// Public Variables:
//---------------------------------------------------------

int npcX;
int npcY;
int npcR;
bool npc; //hitmax variable

//---------------------------------------------------------
// Image Variables:
//---------------------------------------------------------
//Images
PImage classroomBackground; // standard background for the classroom including the teachers desk
PImage standardDesk;		// Normal Desk with nothing on it
PImage pencilDesk;		    // Desk with pencils on it
PImage notebookDesk;		// Desk with a notebook on it 
PImage toyDesk;             // Desk with Monster toy on it
PImage student;				// Sprite for a student
PImage teacher;				// Sprite for the teacher

//---------------------------------------------------------
// Private Variables:
//---------------------------------------------------------

static PFont deskText;

static count;
static int found;
static int hiding;
static float studentAngle;
static float teacherAngle;
static int studentMax;
static int teacherMax;
vec2_t point1;
vec2_t point2;
vec2_t point3;

vec2_t desk[12];
vec2_t stretch[12];

PLAYER Charpos0;

static vec2_t CharWidthHeight = { 80, 80 };

static float NORMALMAXSPEED = 1000.0f;
static float NORMALACCELERATION = 999.0f;
static float NORMALFRICTION = .90f;

static int DIRECTION = 1;

float timer;
static int canLeaveDoor = 1;
static int canLeave = 1;

void SceneRoom1Init()
{
  canLeave = 1;
  canLeaveDoor = 1;
	setFrameRate(60);

	fullscreen();

	deskText = loadFont("./Assets/Fonts/consoleText.ttf");
	textFont(deskText, 15);
	
	//Removing cursor in Game
	noCursor();

	// Loads the image of the classroom background
	classroomBackground = loadImage("./Assets/Graphics/Classroom/empty_classroom.png");

	// Loads the images of desks 
	standardDesk = loadImage("./Assets/Graphics/Classroom/desk plain.png");
	pencilDesk = loadImage("./Assets/Graphics/Classroom/desk4.png");
	notebookDesk = loadImage("./Assets/Graphics/Classroom/desk_2.png");
	toyDesk = loadImage("./Assets/Graphics/Classroom/desk_3.png");

	//Load image of student and teacher
	student = loadImage("./Assets/sprites/student.png");
	teacher = loadImage("./Assets/sprites/teacher.png");
	
	timer = second() + .02;

	Charpos0.velX = 1.4;
	Charpos0.velY = 1.4;
	Charpos0.x = 75;
	Charpos0.y = 100;
	Charpos0.h = 175;
	Charpos0.w = 175;

	found = FALSE;
  	hiding = FALSE;
	npcX = 1300;
	npcY = 350;
	npcR = 50;
	studentAngle = FALSE;
	teacherAngle = 91;
	studentMax = FALSE;

	//set all the desk points
	desk[0].x = 240;
	desk[0].y = 170;
	stretch[0].x = 179.32;
	stretch[0].y = 263.511;
	desk[1].x = 500;
	desk[1].y = 170;
	stretch[1].x = 224.15;
	stretch[1].y = 263.511;
	desk[2].x = 770;
	desk[2].y = 170;
	stretch[2].x = 224.15;
	stretch[2].y = 235.773;
	desk[3].x = 1040;
	desk[3].y = 170;
	stretch[3].x = 224.15;
	stretch[3].y = 263.511;
	desk[4].x = 240;
	desk[4].y = 536;
	stretch[4].x = 224.15;
	stretch[4].y = 249.642;
	desk[5].x = 500;
	desk[5].y = 536;
	stretch[5].x = 224.15;
	stretch[5].y = 221.904;
	desk[6].x = 770;
	desk[6].y = 536;
	stretch[6].x = 224.15;
	stretch[6].y = 263.511;
	desk[7].x = 1040;
	desk[7].y = 536;
	stretch[7].x = 224.15;
	stretch[7].y = 263.511;
	desk[8].x = 240;
	desk[8].y = 930;
	stretch[8].x = 246.565;
	stretch[8].y = 249.642;
	desk[9].x = 500;
	desk[9].y = 930;
	stretch[9].x = 224.15;
	stretch[9].y = 221.904;
	desk[10].x = 770;
	desk[10].y = 930;
	stretch[10].x = 224.15;
	stretch[10].y = 263.511;
	desk[11].x = 1040;
	desk[11].y = 930;
	stretch[11].x = 224.15;
	stretch[11].y = 263.511;

}


void SceneRoom1Update()
{
	// Draws the classroom image
	image(classroomBackground, 960, 540 , 1920, 1080, 255);

	//Draws Desks in classroom
	//Row 1
	imageRotated(toyDesk, 240, 170, 263.511, 179.32, 255, 90);
	imageRotated(standardDesk, 500, 170, 263.511, 224.15, 255, 90);
	imageRotated(notebookDesk, 770, 170, 235.773, 224.15, 255, 90);
	imageRotated(standardDesk, 1040, 170, 263.511, 224.15, 255, 90);
	//Row 2
	imageRotated(standardDesk, 240, 536, 249.642, 224.15, 255, 90);
	imageRotated(pencilDesk, 500, 536, 221.904, 224.15, 255, 90);
	imageRotated(standardDesk, 770, 536, 263.511, 224.15, 255, 90);
	imageRotated(standardDesk, 1040, 536, 263.511, 224.15, 255, 90);
	//Row 3
	imageRotated(standardDesk, 240, 930, 249.642, 246.565, 255, 90);
	imageRotated(notebookDesk, 500, 930, 235.773, 224.15, 255, 90);
	imageRotated(pencilDesk, 770, 930, 221.904, 224.15, 255, 90);
	imageRotated(standardDesk, 1040, 930, 263.511, 224.15, 255, 90);

	//Door, also Exit to Level Select
	fill(200, 30, 100, 255);
	rect(1479.39, 1052.6, 300, 55.476);

	//if not hiddes
	if (!hiding)
	{
		//loop through the desks
		for (int i = 0; i < 12; i++)
		{
			//if close enough show you can go under and return if you went under or not
			hiding = checkDesk(&Charpos0, desk[i], stretch[i]);
			count = i;

			//if you hid
			if (hiding)
			{
				break; //break out of the loop to check if you can hide or not
			}
		}
	}

	if (!hiding) //not under a desk
	{
		Charpos0.w /= 2;
		Charpos0.h /= 2;
			// enable movement
		enableRIGHTLEFT(&Charpos0.velX, NORMALACCELERATION, NORMALFRICTION, NORMALMAXSPEED);
		enableUPDOWN(&Charpos0.velY, NORMALACCELERATION, NORMALFRICTION, NORMALMAXSPEED);

		//collision with desks
		disableMOVEMENT(&Charpos0.x, &Charpos0.y, Charpos0.w, Charpos0.h, &Charpos0.velX, &Charpos0.velY, 655, 140, 950, 280, FALSE);
		disableMOVEMENT(&Charpos0.x, &Charpos0.y, Charpos0.w, Charpos0.h, &Charpos0.velX, &Charpos0.velY, 565, 532, 1130, 225, FALSE);
		disableMOVEMENT(&Charpos0.x, &Charpos0.y, Charpos0.w, Charpos0.h, &Charpos0.velX, &Charpos0.velY, 565, 935, 1130, 240, FALSE);

		//collision with teacher's desk
		disableMOVEMENT(&Charpos0.x, &Charpos0.y, Charpos0.w, Charpos0.h, &Charpos0.velX, &Charpos0.velY, 1670, 300, 500, 105, FALSE);
		disableMOVEMENT(&Charpos0.x, &Charpos0.y, Charpos0.w, Charpos0.h, &Charpos0.velX, &Charpos0.velY, 1815, 175, 205, 350, FALSE);

		//collision with room walls
		disableMOVEMENT(&Charpos0.x, &Charpos0.y, Charpos0.w, Charpos0.h, &Charpos0.velX, &Charpos0.velY, canvasWidth / 2, 0, canvasWidth, 2, FALSE);
		disableMOVEMENT(&Charpos0.x, &Charpos0.y, Charpos0.w, Charpos0.h, &Charpos0.velX, &Charpos0.velY, 0, canvasHeight / 2, 2, canvasHeight, FALSE);
		disableMOVEMENT(&Charpos0.x, &Charpos0.y, Charpos0.w, Charpos0.h, &Charpos0.velX, &Charpos0.velY, canvasWidth / 2, canvasHeight, canvasWidth, 2, FALSE);
		disableMOVEMENT(&Charpos0.x, &Charpos0.y, Charpos0.w, Charpos0.h, &Charpos0.velX, &Charpos0.velY, canvasWidth, canvasHeight / 2, 2, canvasHeight, FALSE);

		//allow player to move
		enableMOVEMENT(&Charpos0.x, &Charpos0.y, &Charpos0.velX, &Charpos0.velY);
		Charpos0.w *= 2;
		Charpos0.h *= 2;
	}
	else //while under a desk
	{
		hiding = stopHiding(&Charpos0);
	}
	
	//adjust the angle for the teachers triangle 
	if (second() >= timer && !teacherMax)
	{
		teacherAngle++;
		timer = second() + 0.01;
	}
	else if (second() >= timer && teacherMax)
	{
		teacherAngle--;
		timer = second() + 0.01;
	}

	//reverse teacher direction
	if (teacherAngle == 180 || teacherAngle == 90)
	{
		teacherMax = !teacherMax;
	}

	// set points for the teachers triangle
	point1.x = npcX;
	point2.x = npcX + 400;
	point3.x = npcX + 400;
	point1.y = npcY;
	point2.y = npcY + 65;
	point3.y = npcY - 65;

	//rotate the angle with a affine transformation
	rotateTriangle(&point1, &point2, &point3, teacherAngle);

	//Teacher Movement
	fill(255, 255, 0, 255);
	triangle(point1.x, point1.y, point2.x, point2.y, point3.x, point3.y);
	fill(255, 0, 0, 255);
	imageRotated(teacher, 1300, 350, 100, 100, 255, teacherAngle);
	

	//check to see if the player is in the teachers sight
	found = checkDetection(point1, point2, point3, Charpos0);

	//set points for students sight triangle
	point1.x = 600;
	point2.x = 530;
	point3.x = 670;
	point1.y = 920;
	point2.y = 645;
	point3.y = 645;

	//switch student view rotation
	if (studentMax)
	{
		studentAngle--;
	}
	else
	{
		studentAngle++;
	}
	if (studentAngle == 90 || studentAngle == -90)
	{
		studentMax = !studentMax;
	}

	//rotate the students triangle
	rotateTriangle(&point1, &point2, &point3, studentAngle);

	if (!found)
	{
		found = checkDetection(point1, point2, point3, Charpos0);
	}

	//student
	fill(255, 255, 0, 255);
	triangle(point1.x, point1.y, point2.x, point2.y, point3.x, point3.y);
	fill(0, 255, 0, 255);
	imageRotated(student, point1.x, point1.y, 100, 100, 255, studentAngle);

	//tester dot for center of player 
	fill(0, 0, 0, 255);
	rect(Charpos0.x, Charpos0.y, 5, 5);

	fill(128, 0, 128, 50);
	rect(0, 0, 1920, 1080);

	//draw a triangle over the desk you are hiding under
	if (hiding)
	{
		showDesk(desk[count]);
	}

	//return to level select if you are found
	if (found == TRUE)
    canLeave = 0;
  if (canLeave == 0 && fadeout() == 0)
    SceneManagerSetNextScene(SCENE_GAMEOVER);

	//Return to LEVEL SELECT AT DOOR
	if (1480 < Charpos0.x - 40 && Charpos0.x + 40 < 1780 && Charpos0.y + Charpos0.h / 2 > 1052)
    canLeaveDoor = 0;
  if (canLeave != 0 && canLeaveDoor == 0 && fadein() == 0)
    SceneManagerSetNextScene(SCENE_LEVEL_SELECT);
	drawPlayerNUDE(Charpos0);
}



