//---------------------------------------------------------
// file:	Scene_Room2.c
// author:	Maverick Alexander / Anthony Miller
// brief:   Second Level in game
// Course: GAM100F18
// Copyright © 2018 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "C_Processing.h"
#include "Scene_Room1.h"
#include "SceneManager.h"
#include <windows.h>
#include "Scene_PHYtest.h"
#include "NPC.h"
#include "Desk.h"



// Bottom Student Variables
int bottom_student_npcX;
int bottom_student_npcY;
int bottom_student_npcR;

//teacher movement variables
int teacher_X;
int teacher_Y;
int teacher_R;

//top student movement variables
int top_student_X;
int top_student_Y;
int top_student_R;

//chalkboars student variables
int chalkboard_studentX;
int chalkboard_studentY;
int chalkboard_studentR;

//font
static PFont deskText;

//hitmax variables
bool chalkboard_student;
bool top_student;
bool bottom_student;

//---------------------------------------------------------
// Image Variables:
//---------------------------------------------------------
//Images
PImage classroomBackground; // standard background for the classroom including the teachers desk
PImage standardDesk;		// Normal Desk with nothing on it
PImage pencilDesk;		    // Desk with pencils on it
PImage notebookDesk;		// Desk with a notebook on it 
PImage toyDesk;             // Desk with Monster toy on it
PImage student;
PImage teacher;

//Puddles
PImage puddle;

//---------------------------------------------------------
// Private Variables:
//---------------------------------------------------------

int found;
static int count;
static int hiding;
int topAngle;
int botAngle;
int teacherAngle;
int chalkAngle;
static int teacherMax;
static int topMax;
int topTimer;

vec2_t point1;
vec2_t point2;
vec2_t point3;

vec2_t desk[12];
vec2_t stretch[12];

PLAYER Charpos0;
static vec2_t CharWidthHeight = { 80, 80 };

//---------------------------------------------------------
// Private Function Declarations:
//---------------------------------------------------------

//---------------------------------------------------------
// Public Functions:
//---------------------------------------------------------

//---------------------------------------------------------

//---------------------------------------------------------
// Private Functions:
//---------------------------------------------------------

static float ICEMAXSPEED = 200;
static float ICEACCELERATION = 1.05;
static float ICEFRICTION = .985;

static float NORMALMAXSPEED = 1000.0f;
static float NORMALACCELERATION = 999.0f;
static float NORMALFRICTION = .90f;
static int canLeaveDoor = 1;
static int canLeave = 1;
static int directionX = 1;
static int directionY = 1;

float timer;
int flipped;



void SceneRoom2Init()
{
	if (keyPressed(KEY_A))
		directionX = -1;
	if (keyPressed(KEY_D))
		directionX = 1;
	if (keyPressed(KEY_W))
		directionY = -1;
	if (keyPressed(KEY_S))
		directionY = 1;


  setFrameRate(60);
  canLeave = 1;
  canLeaveDoor = 1;
	// Setting Canvas size to 1920 x 1080
	fullscreen();

	//set text font stuff
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

	//Load the image of the puddle
	puddle = loadImage("./Assets/sprites/Puddle.png");

	Charpos0.velX = 1.4;
	Charpos0.velY = 1.4;
	Charpos0.x = 75;
	Charpos0.y = 100;
	Charpos0.h = 175;
	Charpos0.w = 175;

	found = FALSE;

	//Setting teacher values
	teacher_X = 1300;
	teacher_Y = 350;
	teacher_R = 100;
	teacherAngle = 91;

	//Setting top student values
	top_student_X = 450;
	top_student_Y = 350;
	top_student_R = 100;
	topTimer = second() + 2;

	//Setting chalkboard student values
	chalkboard_studentX = 1700;
	chalkboard_studentY = 500;
	chalkboard_studentR = 100;
	chalkboard_student = false;

	//Bottom Student values
	bottom_student_npcX = 800;
	bottom_student_npcY = 740;
	bottom_student_npcR = 100;
	bottom_student = false;

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


void SceneRoom2Update()
{
	// Draws the classroom image
	image(classroomBackground, 960, 540, 1920, 1080, 255);

	/*
	if (!(frameCount % 20))
	{
		printf("teacher x: %i\n", teacher_X);
		printf("teacher y: %i\n", teacher_Y);
		printf("teacher r: %i\n", teacher_R);
	}
	*/

	//Puddle locations and player puddle physics
//Top Puddle
	image(puddle, 850, 350, 100, 100, 230);

	if (Charpos0.x >= 750 && Charpos0.x < 950)
	{
		if (Charpos0.y >= 250 && Charpos0.y <= 450)
		{
			Charpos0.velX *= directionX + 0.07;
			Charpos0.velY *= directionX + 0.07;

		}
	}

	//Door Puddle
	image(puddle, 1200, 720, 150, 150, 230);

	if (Charpos0.x >= 1050 && Charpos0.x < 1350)
	{
		if (Charpos0.y >= 570 && Charpos0.y <= 870)
		{
			Charpos0.velX *= directionX + 0.07;
			Charpos0.velY *= directionX + 0.07;

		}
	}

	//Bottom Puddle
	image(puddle, 700, 720, 150, 150, 230);

	if (Charpos0.x >= 700 && Charpos0.x < 1000)
	{
		if (Charpos0.y >= 670 && Charpos0.y <= 870)
		{
			Charpos0.velX *= directionX + 0.07;
			Charpos0.velY *= directionX + 0.07;
		}
	}
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
	

	//Teacher Movement
	point1.x = teacher_X;
	point2.x = teacher_X + 400;
	point3.x = teacher_X + 400;
	point1.y = teacher_Y;
	point2.y = teacher_Y + 65;
	point3.y = teacher_Y - 65;
	

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

	//draw the sight triangle for the teacher
	rotateTriangle(&point1, &point2, &point3, teacherAngle);
	fill(255, 255, 0, 255);
	triangle(point1.x, point1.y, point2.x, point2.y, point3.x, point3.y);

	//check if the player is in the teachers sight trangle
	if (!found)
	{
		found = checkDetection(point1, point2, point3, Charpos0);
	}
	
	//draw the teacher
	fill(255, 0, 0, 255);
	imageRotated(teacher, teacher_X, teacher_Y, teacher_R, teacher_R, 255, teacherAngle);

	// Bottom Student Placement/Movement
	point1.x = bottom_student_npcX;
	point2.x = bottom_student_npcX + 275;
	point3.x = bottom_student_npcX + 275;
	point1.y = bottom_student_npcY;
	point2.y = bottom_student_npcY + 65;
	point3.y = bottom_student_npcY - 65;

	//changle the angle  of the bot student bassed on the direction it is heading
	if (!bottom_student)
	{
		botAngle = 0;
	}
	else
	{
		botAngle = 180;
	}
	
	//draw the triangle for the bot student
	fill(255, 255, 0, 255);
	rotateTriangle(&point1, &point2, &point3, botAngle);
	triangle(point1.x, point1.y, point2.x, point2.y, point3.x, point3.y);

	//check if the player is in the bot students sight triangle
	if (!found)
	{
		found = checkDetection(point1, point2, point3, Charpos0);
	}
	////////////////////////////////////////////////////////////////
	//Student Sightline
	//When the student is walking left have the triangel moving left with him
	//When the student is moving right have the triangle moving right with him
	////////////////////////////////////////////////////////////////
	fill(0, 255, 0, 255);
	npc_leftright_movement(&bottom_student_npcX, 1, 1000, 100, &bottom_student);
	imageRotated(student, bottom_student_npcX, bottom_student_npcY, bottom_student_npcR, bottom_student_npcR, 255, botAngle);

	//Top student Placement
	point1.x = top_student_X;
	point2.x = top_student_X + 275;
	point3.x = top_student_X + 275;
	point1.y = top_student_Y;
	point2.y = top_student_Y + 65;
	point3.y = top_student_Y - 65;
	

	//adjust the angle for the top students triangle 
	if (second() >= topTimer && topMax)
	{
		topMax = !topMax;
		topAngle = 180;
		topTimer = second() + 2;
	}
	else if (second() >= topTimer && !topMax)
	{
		topMax = !topMax;
		topAngle = 0;
		topTimer = second() + 2;
	}

	fill(255, 255, 0, 255); 
	rotateTriangle(&point1, &point2, &point3, topAngle);
	triangle(point1.x, point1.y, point2.x, point2.y, point3.x, point3.y);
	
	if (!found)
	{
		found = checkDetection(point1, point2, point3, Charpos0);
	}

	fill(0, 255, 0, 255);
	imageRotated(student, top_student_X, top_student_Y, top_student_R, top_student_R, 255, topAngle);
	//rotate the students triangle
	
	///////////////////////////////////////////////////////////////////
	//Top student Sightline
	//Triangle that rotates 180 degrees to either side of the student
	///////////////////////////////////////////////////////////////////

	fill(0, 0, 0, 255);
	rect(Charpos0.x, Charpos0.y, 5, 5);

	fill(128, 0, 128, 50);
	rect(0, 0, 1920, 1080);

	//Chalkboard Student Placement/Movement
	point1.x = chalkboard_studentX;
	point2.x = chalkboard_studentX - 275;
	point3.x = chalkboard_studentX - 275;
	point1.y = chalkboard_studentY;
	point2.y = chalkboard_studentY + 65;
	point3.y = chalkboard_studentY - 65;
	chalkAngle = 0;

	fill(255, 255, 0, 255);
	rotateTriangle(&point1, &point2, &point3, chalkAngle);
	triangle(point1.x, point1.y, point2.x, point2.y, point3.x, point3.y);
	
	if (!found)
	{
		found = checkDetection(point1, point2, point3, Charpos0);
	}

	fill(0, 255, 0, 255);
	npc_updown_movement(&chalkboard_studentY, 1, 950, 500, &chalkboard_student);
	image(student, chalkboard_studentX, chalkboard_studentY, chalkboard_studentR, chalkboard_studentR, 255);
	///////////////////////////////////////////////////////////////////
	//chalkboard student Sightline
	//Triangle that faces the desks and moves with the student
	///////////////////////////////////////////////////////////////////



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

	drawPlayerNUDE(Charpos0);
}
