/*
September 24, 2019
CSC328- Computer Graphics
Professor Pickett
Jonathan Webber

Assignment 4: Polyman is murdered... IN 3D!!!!
*/

using namespace std;
#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>

//global bariabls for timeing
//global variables for polyman
float polyMAngle = -10.0;
float polyMScale = 1.0;
float polyMdx = 10.0, polyMdy = 0.0, polyMdz = 0.0;
int polyMlegflip = 0;	//0 = still 1 = one walk cycle 2 = other walk cycle
bool polyMopenmouth = false;
bool dead = false;

//global variables for polywoman
float polyWAngle = -10.0;
float polyWScale = 1.0;
float polyWdx = -10.0, polyWdy = 0.0, polyWdz = 0.0;
int polyWlegflip = 0;	//0 = still 1 = one walk cycle 2 = other walk cycle
bool polyWopenmouth = false;

//global variables for squareman
float polySAngle = -10.0;
float polySScale = 1.0;
float polySdx = -10.0, polySdy = 0.0, polySdz = 0.0;
int polySlegflip = 0;	//0 = still 1 = one walk cycle 2 = other walk cycle
bool attack = false;

//other useful variables
int frame = 1;
int frameCount = 0;

//initialize window to clear color
void init(void);

//begin the RenderScene function
void RenderScene(void);

//load and draw polyman icon
void loadMIcon(float[][10], float[][10], float[][10], float[][10], float[][10], float[][10]);
void drawMIcon(float[][10], float[][10], float[][10], float[][10], float[][10], float[][10]);

//load and draw polywoman icon
void loadWIcon(float[][10], float[][10], float[][10], float[][25], float[][25], float[][25]);
void drawWIcon(float[][10], float[][10], float[][10], float[][25], float[][25], float[][25]);

//load and draw squareman icon
void loadSIcon(float[][10], float[][10], float[][10], float[][20], float[][20], float[][20]);
void drawSIcon(float[][10], float[][10], float[][10], float[][20], float[][20], float[][20]);

//transforms
void settrans1(void);
void settrans2(void);
void settrans3(void);

//simple walk functions
void walk(char a);

//sets up the clear color
void setupRC(void);

//called for 30 fps animations
void timerFunction(int);

//main program
int main(int argc, char** argv) {

	//set window title
	char header[] = "The Murder of Polyman... IN 3D!!!! by Jonathan Webber";

	//initiate the glut
	glutInit(&argc, argv);

	//set up the display mode/double buffer
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	//set p the window size and position
	glutInitWindowSize(900, 700);
	glutInitWindowPosition(200, 20);

	//initialize background color
	setupRC();

	//open and label window
	glutCreateWindow(header);
	glutDisplayFunc(RenderScene);
	glutTimerFunc(30, timerFunction, 0);

	//now draw the scene
	glutMainLoop();

	return 0;

}//end of main

void RenderScene(void) {
	
	//set up polyman's points
	float pointMx[10][10], pointMy[10][10], pointMz[10][10], lineMx[10][10], lineMy[10][10], lineMz[10][10];

	//set up polywoman's points
	float pointWx[10][10], pointWy[10][10], pointWz[10][10], lineWx[25][25], lineWy[25][25], lineWz[25][25];

	//set up squareman's points
	float pointSx[10][10], pointSy[10][10], pointSz[10][10], lineSx[20][20], lineSy[20][20], lineSz[20][20];

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//set the viewport to the window dimensions and ortho
	glViewport(0, 0, 900, 700);
	glOrtho(-8.0, 8.0, -8.0, 8.0, 3.0, -3.0);

	//draw the icons untransformed
	loadMIcon(pointMx, pointMy, pointMz, lineMx, lineMy, lineMz);
	loadWIcon(pointWx, pointWy, pointWz, lineWx, lineWy, lineWz);
	loadSIcon(pointSx, pointSy, pointSz, lineSx, lineSy, lineSz);

	glClear(GL_COLOR_BUFFER_BIT);

	//set the MODELVIEW MATRIX for the icons and draw them
	settrans2();
	drawWIcon(pointWx, pointWy, pointWz, lineWx, lineWy, lineWz);
	settrans3();
	drawSIcon(pointSx, pointSy, pointSz, lineSx, lineSy, lineSz);

	//make the top polygon
	settrans1();
	drawMIcon(pointMx, pointMy, pointMz, lineMx, lineMy, lineMz);

	glEnd();
	glutSwapBuffers();

	return;

}//end of RenderScene

 //function to load polyman's icon
void loadMIcon(float pointX[][10], float pointY[][10], float pointZ[][10], float lineX[][10], float lineY[][10], float lineZ[][10]) {

	//set the coordinates of polyman's body (with and without an open mouth)
	if (polyMopenmouth) {
		//parallellogram body closest to the viewer
		pointX[0][0] = -9.0 / 8.0;	pointY[0][0] = 0.0;		pointZ[0][0] = 0.5;
		pointX[0][1] = -5.0 / 8.0;	pointY[0][1] = 0.75;	pointZ[0][1] = 0.5;
		pointX[0][2] = 5.0 / 8.0;	pointY[0][2] = 0.75;	pointZ[0][2] = 0.5;
		pointX[0][3] = 9.0 / 8.0;	pointY[0][3] = 0.0;		pointZ[0][3] = 0.5;
		pointX[0][4] = 5.0 / 8.0;	pointY[0][4] = -0.75;	pointZ[0][4] = 0.5;
		pointX[0][5] = -5.0 / 8.0;	pointY[0][5] = -0.75;	pointZ[0][5] = 0.5;
		pointX[0][6] = -3.0 / 8.0;	pointY[0][6] = 0.0;		pointZ[0][6] = 0.5;
		pointX[0][7] = -9.0 / 8.0;	pointY[0][7] = 0.0;		pointZ[0][7] = 0.5;

		//parallellogram body furthest from the viewer
		pointX[1][0] = -9.0 / 8.0;	pointY[1][0] = 0.0;		pointZ[1][0] = -0.5;
		pointX[1][1] = -5.0 / 8.0;	pointY[1][1] = 0.75;	pointZ[1][1] = -0.5;
		pointX[1][2] = 5.0 / 8.0;	pointY[1][2] = 0.75;	pointZ[1][2] = -0.5;
		pointX[1][3] = 9.0 / 8.0;	pointY[1][3] = 0.0;		pointZ[1][3] = -0.5;
		pointX[1][4] = 5.0 / 8.0;	pointY[1][4] = -0.75;	pointZ[1][4] = -0.5;
		pointX[1][5] = -5.0 / 8.0;	pointY[1][5] = -0.75;	pointZ[1][5] = -0.5;
		pointX[1][6] = -3.0 / 8.0;	pointY[1][6] = 0.0;		pointZ[1][6] = -0.5;
		pointX[1][7] = -9.0 / 8.0;	pointY[1][7] = 0.0;		pointZ[1][7] = -0.5;

		//top left/front of head 'rectangle'
		pointX[2][0] = -9.0 / 8.0;	pointY[2][0] = 0.0;		pointZ[2][0] = 0.5;
		pointX[2][1] = -9.0 / 8.0;	pointY[2][1] = 0.0;		pointZ[2][1] = -0.5;
		pointX[2][2] = -5.0 / 8.0;	pointY[2][2] = 0.75;	pointZ[2][2] = -0.5;
		pointX[2][3] = -5.0 / 8.0;	pointY[2][3] = 0.75;	pointZ[2][3] = 0.5;
		pointX[2][4] = -9.0 / 8.0;	pointY[2][4] = 0.0;		pointZ[2][4] = 0.5;

		//top of head 'rectangle'
		pointX[3][0] = -5.0 / 8.0;	pointY[3][0] = 0.75;	pointZ[3][0] = 0.5;
		pointX[3][1] = -5.0 / 8.0;	pointY[3][1] = 0.75;	pointZ[3][1] = -0.5;
		pointX[3][2] = 5.0 / 8.0;	pointY[3][2] = 0.75;	pointZ[3][2] = -0.5;
		pointX[3][3] = 5.0 / 8.0;	pointY[3][3] = 0.75;	pointZ[3][3] = 0.5;
		pointX[3][4] = -5.0 / 8.0;	pointY[3][4] = 0.75;	pointZ[3][4] = 0.5;

		//top right of polyman 'rectangle'
		pointX[4][0] = 5.0 / 8.0;	pointY[4][0] = 0.75;	pointZ[4][0] = 0.5;
		pointX[4][1] = 5.0 / 8.0;	pointY[4][1] = 0.75;	pointZ[4][1] = -0.5;
		pointX[4][2] = 9.0 / 8.0;	pointY[4][2] = 0.0;		pointZ[4][2] = -0.5;
		pointX[4][3] = 9.0 / 8.0;	pointY[4][3] = 0.0;		pointZ[4][3] = 0.5;
		pointX[4][4] = 5.0 / 8.0;	pointY[4][4] = 0.75;	pointZ[4][4] = 0.5;

		//bottom right of polyman 'rectangle'
		pointX[5][0] = 9.0 / 8.0;	pointY[5][0] = 0.0;		pointZ[5][0] = 0.5;
		pointX[5][1] = 9.0 / 8.0;	pointY[5][1] = 0.0;		pointZ[5][1] = -0.5;
		pointX[5][2] = 5.0 / 8.0;	pointY[5][2] = -0.75;	pointZ[5][2] = -0.5;
		pointX[5][3] = 5.0 / 8.0;	pointY[5][3] = -0.75;	pointZ[5][3] = 0.5;
		pointX[5][4] = 9.0 / 8.0;	pointY[5][4] = 0.0;		pointZ[5][4] = 0.5;

		//bottom of polyman 'rectangle'
		pointX[6][0] = 5.0 / 8.0;	pointY[6][0] = -0.75;	pointZ[6][0] = 0.5;
		pointX[6][1] = 5.0 / 8.0;	pointY[6][1] = -0.75;	pointZ[6][1] = -0.5;
		pointX[6][2] = -5.0 / 8.0;	pointY[6][2] = -0.75;	pointZ[6][2] = -0.5;
		pointX[6][3] = -5.0 / 8.0;	pointY[6][3] = -0.75;	pointZ[6][3] = 0.5;
		pointX[6][4] = 5.0 / 8.0;	pointY[6][4] = -0.75;	pointZ[6][4] = 0.5;

		//bottom of open mouth
		pointX[7][0] = -5.0 / 8.0;	pointY[7][0] = -0.75;	pointZ[7][0] = 0.5;
		pointX[7][1] = -5.0 / 8.0;	pointY[7][1] = -0.75;	pointZ[7][1] = -0.5;
		pointX[7][2] = -3.0 / 8.0;	pointY[7][2] = 0.0;		pointZ[7][2] = -0.5;
		pointX[7][3] = -3.0 / 8.0;	pointY[7][3] = 0.0;		pointZ[7][3] = 0.5;
		pointX[7][4] = -5.0 / 8.0;	pointY[7][4] = -0.75;	pointZ[7][4] = 0.5;

		//top of open mouth
		pointX[8][0] = -3.0 / 8.0;	pointY[8][0] = 0.0;		pointZ[8][0] = 0.5;
		pointX[8][1] = -3.0 / 8.0;	pointY[8][1] = 0.0;		pointZ[8][1] = -0.5;
		pointX[8][2] = -9.0 / 8.0;	pointY[8][2] = 0.0;		pointZ[8][2] = -0.5;
		pointX[8][3] = -9.0 / 8.0;	pointY[8][3] = 0.0;		pointZ[8][3] = 0.5;
		pointX[8][4] = -3.0 / 8.0;	pointY[8][4] = 0.0;		pointZ[8][4] = 0.5;

	}//end of if mouth open

	else {
		//parallellogram body closest to the viewer
		pointX[0][0] = -9.0 / 8.0;	pointY[0][0] = 0.0;		pointZ[0][0] = 0.5;
		pointX[0][1] = -5.0 / 8.0;	pointY[0][1] = 0.75;	pointZ[0][1] = 0.5;
		pointX[0][2] = 5.0 / 8.0;	pointY[0][2] = 0.75;	pointZ[0][2] = 0.5;
		pointX[0][3] = 9.0 / 8.0;	pointY[0][3] = 0.0;		pointZ[0][3] = 0.5;
		pointX[0][4] = 5.0 / 8.0;	pointY[0][4] = -0.75;	pointZ[0][4] = 0.5;
		pointX[0][5] = -5.0 / 8.0;	pointY[0][5] = -0.75;	pointZ[0][5] = 0.5;
		pointX[0][6] = -3.0 / 4.0;	pointY[0][6] = -0.5;	pointZ[0][6] = 0.5;
		pointX[0][7] = -9.0 / 8.;	pointY[0][7] = 0.0;		pointZ[0][7] = 0.5;

		//parallellogram body farthest from the viewer
		pointX[1][0] = -9.0 / 8.0;	pointY[1][0] = 0.0;		pointZ[1][0] = -0.5;
		pointX[1][1] = -5.0 / 8.0;	pointY[1][1] = 0.75;	pointZ[1][1] = -0.5;
		pointX[1][2] = 5.0 / 8.0;	pointY[1][2] = 0.75;	pointZ[1][2] = -0.5;
		pointX[1][3] = 9.0 / 8.0;	pointY[1][3] = 0.0;		pointZ[1][3] = -0.5;
		pointX[1][4] = 5.0 / 8.0;	pointY[1][4] = -0.75;	pointZ[1][4] = -0.5;
		pointX[1][5] = -5.0 / 8.0;	pointY[1][5] = -0.75;	pointZ[1][5] = -0.5;
		pointX[1][6] = -3.0 / 4.0;	pointY[1][6] = -0.5;	pointZ[1][6] = -0.5;
		pointX[1][7] = -9.0 / 8.;	pointY[1][7] = 0.0;		pointZ[1][7] = -0.5;

		//top left/front of head 'rectangle'
		pointX[2][0] = -9.0 / 8.0;	pointY[2][0] = 0.0;		pointZ[2][0] = 0.5;
		pointX[2][1] = -9.0 / 8.0;	pointY[2][1] = 0.0;		pointZ[2][1] = -0.5;
		pointX[2][2] = -5.0 / 8.0;	pointY[2][2] = 0.75;	pointZ[2][2] = -0.5;
		pointX[2][3] = -5.0 / 8.0;	pointY[2][3] = 0.75;	pointZ[2][3] = 0.5;
		pointX[2][4] = -9.0 / 8.0;	pointY[2][4] = 0.0;		pointZ[2][4] = 0.5;

		//top of head 'rectangle'
		pointX[3][0] = -5.0 / 8.0;	pointY[3][0] = 0.75;	pointZ[3][0] = 0.5;
		pointX[3][1] = -5.0 / 8.0;	pointY[3][1] = 0.75;	pointZ[3][1] = -0.5;
		pointX[3][2] = 5.0 / 8.0;	pointY[3][2] = 0.75;	pointZ[3][2] = -0.5;
		pointX[3][3] = 5.0 / 8.0;	pointY[3][3] = 0.75;	pointZ[3][3] = 0.5;
		pointX[3][4] = -5.0 / 8.0;	pointY[3][4] = 0.75;	pointZ[3][4] = 0.5;

		//top right of polyman 'rectangle'
		pointX[4][0] = 5.0 / 8.0;	pointY[4][0] = 0.75;	pointZ[4][0] = 0.5;
		pointX[4][1] = 5.0 / 8.0;	pointY[4][1] = 0.75;	pointZ[4][1] = -0.5;
		pointX[4][2] = 9.0 / 8.0;	pointY[4][2] = 0.0;		pointZ[4][2] = -0.5;
		pointX[4][3] = 9.0 / 8.0;	pointY[4][3] = 0.0;		pointZ[4][3] = 0.5;
		pointX[4][4] = 5.0 / 8.0;	pointY[4][4] = 0.75;	pointZ[4][4] = 0.5;

		//bottom right of polyman 'rectangle'
		pointX[5][0] = 9.0 / 8.0;	pointY[5][0] = 0.0;		pointZ[5][0] = 0.5;
		pointX[5][1] = 9.0 / 8.0;	pointY[5][1] = 0.0;		pointZ[5][1] = -0.5;
		pointX[5][2] = 5.0 / 8.0;	pointY[5][2] = -0.75;	pointZ[5][2] = -0.5;
		pointX[5][3] = 5.0 / 8.0;	pointY[5][3] = -0.75;	pointZ[5][3] = 0.5;
		pointX[5][4] = 9.0 / 8.0;	pointY[5][4] = 0.0;		pointZ[5][4] = 0.5;

		//bottom of polyman 'rectangle'
		pointX[6][0] = 5.0 / 8.0;	pointY[6][0] = -0.75;	pointZ[6][0] = 0.5;
		pointX[6][1] = 5.0 / 8.0;	pointY[6][1] = -0.75;	pointZ[6][1] = -0.5;
		pointX[6][2] = -5.0 / 8.0;	pointY[6][2] = -0.75;	pointZ[6][2] = -0.5;
		pointX[6][3] = -5.0 / 8.0;	pointY[6][3] = -0.75;	pointZ[6][3] = 0.5;
		pointX[6][4] = 5.0 / 8.0;	pointY[6][4] = -0.75;	pointZ[6][4] = 0.5;

		//bottom of head 'rectangle'
		pointX[7][0] = -5.0 / 8.0;	pointY[7][0] = -0.75;	pointZ[7][0] = 0.5;
		pointX[7][1] = -5.0 / 8.0;	pointY[7][1] = -0.75;	pointZ[7][1] = -0.5;
		pointX[7][2] = -9.0 / 8.0;	pointY[7][2] = 0.0;		pointZ[7][2] = -0.5;
		pointX[7][3] = -9.0 / 8.0;	pointY[7][3] = 0.0;		pointZ[7][3] = 0.5;
		pointX[7][4] = -5.0 / 8.0;	pointY[7][4] = -0.75;	pointZ[7][4] = 0.5;

	}//end of else for mouth open

	//set the coordinates of polyman's legs (standing still or flipping them as he walks)
	//still
	if (polyMlegflip == 0) {
		//left leg
		lineX[0][0] = 0.0;		lineY[0][0] = -0.5;	lineZ[0][0] = 0.5;
		lineX[0][1] = 0.0;		lineY[0][1] = -1.0;	lineZ[0][1] = 0.5;
		lineX[0][2] = -0.25;	lineY[0][2] = -1.0;	lineZ[0][2] = 0.5;

		//right leg
		lineX[1][0] = 0.0;		lineY[1][0] = -0.5;	lineZ[1][0] = -0.5;
		lineX[1][1] = 0.0;		lineY[1][1] = -1.0;	lineZ[1][1] = -0.5;
		lineX[1][2] = -0.25;	lineY[1][2] = -1.0;	lineZ[1][2] = -0.5;
	}
	else if (polyMlegflip == 1) {
		//left leg
		lineX[0][0] = 0.0;		lineY[0][0] = -0.5;	lineZ[0][0] = 0.5;
		lineX[0][1] = -0.2;		lineY[0][1] = -1.0;	lineZ[0][1] = 0.5;
		lineX[0][2] = -0.4;		lineY[0][2] = -0.9;	lineZ[0][2] = 0.5;

		//right leg
		lineX[1][0] = 0.0;		lineY[1][0] = -0.5;	lineZ[1][0] = -0.5;
		lineX[1][1] = 0.3;		lineY[1][1] = -0.9;	lineZ[1][1] = -0.5;
		lineX[1][2] = 0.05;		lineY[1][2] = -1.0;	lineZ[1][2] = -0.5;
	}
	else {
		//left leg
		lineX[0][0] = 0.0;		lineY[0][0] = -0.5;	lineZ[0][0] = -0.5;
		lineX[0][1] = 0.3;		lineY[0][1] = -0.9;	lineZ[0][1] = -0.5;
		lineX[0][2] = 0.05;		lineY[0][2] = -1.0;	lineZ[0][2] = -0.5;

		//right leg
		lineX[1][0] = 0.0;		lineY[1][0] = -0.5;	lineZ[1][0] = 0.5;
		lineX[1][1] = -0.2;		lineY[1][1] = -1.0;	lineZ[1][1] = 0.5;
		lineX[1][2] = -0.4;		lineY[1][2] = -0.9;	lineZ[1][2] = 0.5;
	}

	//setting polyman's eye
	if (dead) {
		lineX[2][0] = -0.6;	lineY[2][0] = 0.6;	lineZ[2][0] = 0.5;
		lineX[2][1] = -0.4;	lineY[2][1] = 0.4;	lineZ[2][1] = 0.5;

		lineX[2][2] = -0.6;	lineY[2][2] = 0.4;	lineZ[2][2] = 0.5;
		lineX[2][3] = -0.4;	lineY[2][3] = 0.6;	lineZ[2][3] = 0.5;

		lineX[2][4] = -0.6;	lineY[2][4] = 0.6;	lineZ[2][4] = -0.5;
		lineX[2][5] = -0.4;	lineY[2][5] = 0.4;	lineZ[2][5] = -0.5;

		lineX[2][6] = -0.6;	lineY[2][6] = 0.4;	lineZ[2][6] = -0.5;
		lineX[2][7] = -0.4;	lineY[2][7] = 0.6;	lineZ[2][7] = -0.5;
	}
	else {
		lineX[2][0] = -0.6;	lineY[2][0] = 0.5;	lineZ[2][0] = 0.5;
		lineX[2][1] = -0.4;	lineY[2][1] = 0.5;	lineZ[2][1] = 0.5;

		lineX[2][2] = -0.6;	lineY[2][2] = 0.5;	lineZ[2][2] = -0.5;
		lineX[2][3] = -0.4;	lineY[2][3] = 0.5;	lineZ[2][3] = -0.5;
	}

	return;
}//end of loadMIcon

 //function to load polywoman's icon
void loadWIcon(float pointX[][10], float pointY[][10], float pointZ[][10], float lineX[][25], float lineY[][25], float lineZ[][25]) {

	//set the coordinates of polywoman's body (with and without an open mouth)
	if (polyWopenmouth) {
		//parallellogram body closest to the viewer
		pointX[0][0] = -9.0 / 8.0;	pointY[0][0] = 0.0;		pointZ[0][0] = 0.5;
		pointX[0][1] = -5.0 / 8.0;	pointY[0][1] = 0.75;	pointZ[0][1] = 0.5;
		pointX[0][2] = 5.0 / 8.0;	pointY[0][2] = 0.75;	pointZ[0][2] = 0.5;
		pointX[0][3] = 9.0 / 8.0;	pointY[0][3] = 0.0;		pointZ[0][3] = 0.5;
		pointX[0][4] = 3.0 / 8.0;	pointY[0][4] = 0.0;		pointZ[0][4] = 0.5;
		pointX[0][5] = 5.0 / 8.0;	pointY[0][5] = -0.75;	pointZ[0][5] = 0.5;
		pointX[0][6] = -5.0 / 8.0;	pointY[0][6] = -0.75;	pointZ[0][6] = 0.5;
		pointX[0][7] = -9.0 / 8.0;	pointY[0][7] = 0.0;		pointZ[0][7] = 0.5;

		//parallellogram body furthest from the viewer
		pointX[1][0] = -9.0 / 8.0;	pointY[1][0] = 0.0;		pointZ[1][0] = -0.5;
		pointX[1][1] = -5.0 / 8.0;	pointY[1][1] = 0.75;	pointZ[1][1] = -0.5;
		pointX[1][2] = 5.0 / 8.0;	pointY[1][2] = 0.75;	pointZ[1][2] = -0.5;
		pointX[1][3] = 9.0 / 8.0;	pointY[1][3] = 0.0;		pointZ[1][3] = -0.5;
		pointX[1][4] = 3.0 / 8.0;	pointY[1][4] = 0.0;		pointZ[1][4] = -0.5;
		pointX[1][5] = 5.0 / 8.0;	pointY[1][5] = -0.75;	pointZ[1][5] = -0.5;
		pointX[1][6] = -5.0 / 8.0;	pointY[1][6] = -0.75;	pointZ[1][6] = -0.5;
		pointX[1][7] = -9.0 / 8.0;	pointY[1][7] = 0.0;		pointZ[1][7] = -0.5;

		//top left 'rectangle'
		pointX[2][0] = -9.0 / 8.0;	pointY[2][0] = 0.0;		pointZ[2][0] = 0.5;
		pointX[2][1] = -9.0 / 8.0;	pointY[2][1] = 0.0;		pointZ[2][1] = -0.5;
		pointX[2][2] = -5.0 / 8.0;	pointY[2][2] = 0.75;	pointZ[2][2] = -0.5;
		pointX[2][3] = -5.0 / 8.0;	pointY[2][3] = 0.75;	pointZ[2][3] = 0.5;
		pointX[2][4] = -9.0 / 8.0;	pointY[2][4] = 0.0;		pointZ[2][4] = 0.5;

		//top of head 'rectangle'
		pointX[3][0] = -5.0 / 8.0;	pointY[3][0] = 0.75;	pointZ[3][0] = 0.5;
		pointX[3][1] = -5.0 / 8.0;	pointY[3][1] = 0.75;	pointZ[3][1] = -0.5;
		pointX[3][2] = 5.0 / 8.0;	pointY[3][2] = 0.75;	pointZ[3][2] = -0.5;
		pointX[3][3] = 5.0 / 8.0;	pointY[3][3] = 0.75;	pointZ[3][3] = 0.5;
		pointX[3][4] = -5.0 / 8.0;	pointY[3][4] = 0.75;	pointZ[3][4] = 0.5;

		//top right of polywoman's head 'rectangle'
		pointX[4][0] = 5.0 / 8.0;	pointY[4][0] = 0.75;	pointZ[4][0] = 0.5;
		pointX[4][1] = 5.0 / 8.0;	pointY[4][1] = 0.75;	pointZ[4][1] = -0.5;
		pointX[4][2] = 9.0 / 8.0;	pointY[4][2] = 0.0;		pointZ[4][2] = -0.5;
		pointX[4][3] = 9.0 / 8.0;	pointY[4][3] = 0.0;		pointZ[4][3] = 0.5;
		pointX[4][4] = 5.0 / 8.0;	pointY[4][4] = 0.75;	pointZ[4][4] = 0.5;

		//top of polywoman's mouth
		pointX[5][0] = 9.0 / 8.0;	pointY[5][0] = 0.0;		pointZ[5][0] = 0.5;
		pointX[5][1] = 9.0 / 8.0;	pointY[5][1] = 0.0;		pointZ[5][1] = -0.5;
		pointX[5][2] = 3.0 / 8.0;	pointY[5][2] = 0.0;		pointZ[5][2] = -0.5;
		pointX[5][3] = 3.0 / 8.0;	pointY[5][3] = 0.0;		pointZ[5][3] = 0.5;
		pointX[5][4] = 9.0 / 8.0;	pointY[5][4] = 0.0;		pointZ[5][4] = 0.5;

		//bottom of polywoman's mouth
		pointX[6][0] = 3.0 / 8.0;	pointY[6][0] = 0.0;		pointZ[6][0] = 0.5;
		pointX[6][1] = 3.0 / 8.0;	pointY[6][1] = 0.0;		pointZ[6][1] = -0.5;
		pointX[6][2] = 5.0 / 8.0;	pointY[6][2] = -0.75;	pointZ[6][2] = -0.5;
		pointX[6][3] = 5.0 / 8.0;	pointY[6][3] = -0.75;	pointZ[6][3] = 0.5;
		pointX[6][4] = 3.0 / 8.0;	pointY[6][4] = 0.0;		pointZ[6][4] = 0.5;

		//bottom of polyman 'rectangle'
		pointX[7][0] = 5.0 / 8.0;	pointY[7][0] = -0.75;	pointZ[7][0] = 0.5;
		pointX[7][1] = 5.0 / 8.0;	pointY[7][1] = -0.75;	pointZ[7][1] = -0.5;
		pointX[7][2] = -5.0 / 8.0;	pointY[7][2] = -0.75;	pointZ[7][2] = -0.5;
		pointX[7][3] = -5.0 / 8.0;	pointY[7][3] = -0.75;	pointZ[7][3] = 0.5;
		pointX[7][4] = 5.0 / 8.0;	pointY[7][4] = -0.75;	pointZ[7][4] = 0.5;

		//bottom of open mouth
		pointX[8][0] = -5.0 / 8.0;	pointY[8][0] = -0.75;	pointZ[8][0] = 0.5;
		pointX[8][1] = -5.0 / 8.0;	pointY[8][1] = -0.75;	pointZ[8][1] = -0.5;
		pointX[8][2] = -9.0 / 8.0;	pointY[8][2] = 0.0;		pointZ[8][2] = -0.5;
		pointX[8][3] = -9.0 / 8.0;	pointY[8][3] = 0.0;		pointZ[8][3] = 0.5;
		pointX[8][4] = -5.0 / 8.0;	pointY[8][4] = -0.75;	pointZ[8][4] = 0.5;

	}//end of if mouth open

	else {
		//parallellogram body closest to the viewer
		pointX[0][0] = -9.0 / 8.0;	pointY[0][0] = 0.0;		pointZ[0][0] = 0.5;
		pointX[0][1] = -5.0 / 8.0;	pointY[0][1] = 0.75;	pointZ[0][1] = 0.5;
		pointX[0][2] = 5.0 / 8.0;	pointY[0][2] = 0.75;	pointZ[0][2] = 0.5;
		pointX[0][3] = 9.0 / 8.0;	pointY[0][3] = 0.0;		pointZ[0][3] = 0.5;
		pointX[0][4] = 5.0 / 8.0;	pointY[0][4] = -0.75;	pointZ[0][4] = 0.5;
		pointX[0][5] = -5.0 / 8.0;	pointY[0][5] = -0.75;	pointZ[0][5] = 0.5;
		pointX[0][6] = -3.0 / 4.0;	pointY[0][6] = -0.5;	pointZ[0][6] = 0.5;
		pointX[0][7] = -9.0 / 8.;	pointY[0][7] = 0.0;		pointZ[0][7] = 0.5;

		//parallellogram body farthest from the viewer
		pointX[1][0] = -9.0 / 8.0;	pointY[1][0] = 0.0;		pointZ[1][0] = -0.5;
		pointX[1][1] = -5.0 / 8.0;	pointY[1][1] = 0.75;	pointZ[1][1] = -0.5;
		pointX[1][2] = 5.0 / 8.0;	pointY[1][2] = 0.75;	pointZ[1][2] = -0.5;
		pointX[1][3] = 9.0 / 8.0;	pointY[1][3] = 0.0;		pointZ[1][3] = -0.5;
		pointX[1][4] = 5.0 / 8.0;	pointY[1][4] = -0.75;	pointZ[1][4] = -0.5;
		pointX[1][5] = -5.0 / 8.0;	pointY[1][5] = -0.75;	pointZ[1][5] = -0.5;
		pointX[1][6] = -3.0 / 4.0;	pointY[1][6] = -0.5;	pointZ[1][6] = -0.5;
		pointX[1][7] = -9.0 / 8.;	pointY[1][7] = 0.0;		pointZ[1][7] = -0.5;

		//top left/front of head 'rectangle'
		pointX[2][0] = -9.0 / 8.0;	pointY[2][0] = 0.0;		pointZ[2][0] = 0.5;
		pointX[2][1] = -9.0 / 8.0;	pointY[2][1] = 0.0;		pointZ[2][1] = -0.5;
		pointX[2][2] = -5.0 / 8.0;	pointY[2][2] = 0.75;	pointZ[2][2] = -0.5;
		pointX[2][3] = -5.0 / 8.0;	pointY[2][3] = 0.75;	pointZ[2][3] = 0.5;
		pointX[2][4] = -9.0 / 8.0;	pointY[2][4] = 0.0;		pointZ[2][4] = 0.5;

		//top of head 'rectangle'
		pointX[3][0] = -5.0 / 8.0;	pointY[3][0] = 0.75;	pointZ[3][0] = 0.5;
		pointX[3][1] = -5.0 / 8.0;	pointY[3][1] = 0.75;	pointZ[3][1] = -0.5;
		pointX[3][2] = 5.0 / 8.0;	pointY[3][2] = 0.75;	pointZ[3][2] = -0.5;
		pointX[3][3] = 5.0 / 8.0;	pointY[3][3] = 0.75;	pointZ[3][3] = 0.5;
		pointX[3][4] = -5.0 / 8.0;	pointY[3][4] = 0.75;	pointZ[3][4] = 0.5;

		//top right of polyman 'rectangle'
		pointX[4][0] = 5.0 / 8.0;	pointY[4][0] = 0.75;	pointZ[4][0] = 0.5;
		pointX[4][1] = 5.0 / 8.0;	pointY[4][1] = 0.75;	pointZ[4][1] = -0.5;
		pointX[4][2] = 9.0 / 8.0;	pointY[4][2] = 0.0;		pointZ[4][2] = -0.5;
		pointX[4][3] = 9.0 / 8.0;	pointY[4][3] = 0.0;		pointZ[4][3] = 0.5;
		pointX[4][4] = 5.0 / 8.0;	pointY[4][4] = 0.75;	pointZ[4][4] = 0.5;

		//bottom right of polyman 'rectangle'
		pointX[5][0] = 9.0 / 8.0;	pointY[5][0] = 0.0;		pointZ[5][0] = 0.5;
		pointX[5][1] = 9.0 / 8.0;	pointY[5][1] = 0.0;		pointZ[5][1] = -0.5;
		pointX[5][2] = 5.0 / 8.0;	pointY[5][2] = -0.75;	pointZ[5][2] = -0.5;
		pointX[5][3] = 5.0 / 8.0;	pointY[5][3] = -0.75;	pointZ[5][3] = 0.5;
		pointX[5][4] = 9.0 / 8.0;	pointY[5][4] = 0.0;		pointZ[5][4] = 0.5;

		//bottom of polyman 'rectangle'
		pointX[6][0] = 5.0 / 8.0;	pointY[6][0] = -0.75;	pointZ[6][0] = 0.5;
		pointX[6][1] = 5.0 / 8.0;	pointY[6][1] = -0.75;	pointZ[6][1] = -0.5;
		pointX[6][2] = -5.0 / 8.0;	pointY[6][2] = -0.75;	pointZ[6][2] = -0.5;
		pointX[6][3] = -5.0 / 8.0;	pointY[6][3] = -0.75;	pointZ[6][3] = 0.5;
		pointX[6][4] = 5.0 / 8.0;	pointY[6][4] = -0.75;	pointZ[6][4] = 0.5;

		//bottom of head 'rectangle'
		pointX[7][0] = -5.0 / 8.0;	pointY[7][0] = -0.75;	pointZ[7][0] = 0.5;
		pointX[7][1] = -5.0 / 8.0;	pointY[7][1] = -0.75;	pointZ[7][1] = -0.5;
		pointX[7][2] = -9.0 / 8.0;	pointY[7][2] = 0.0;		pointZ[7][2] = -0.5;
		pointX[7][3] = -9.0 / 8.0;	pointY[7][3] = 0.0;		pointZ[7][3] = 0.5;
		pointX[7][4] = -5.0 / 8.0;	pointY[7][4] = -0.75;	pointZ[7][4] = 0.5;

	}//end of else for mouth open

	 //set the coordinates of polywoman's legs (standing still or flipping them as he walks)
	 //still
	if (polyWlegflip == 0) {
		//left leg
		lineX[0][0] = 0.0;		lineY[0][0] = -0.5;	lineZ[0][0] = 0.5;
		lineX[0][1] = 0.0;		lineY[0][1] = -1.0;	lineZ[0][1] = 0.5;
		lineX[0][2] = 0.25;		lineY[0][2] = -1.0;	lineZ[0][2] = 0.5;

		//right leg
		lineX[1][0] = 0.0;		lineY[1][0] = -0.5;	lineZ[1][0] = -0.5;
		lineX[1][1] = 0.0;		lineY[1][1] = -1.0;	lineZ[1][1] = -0.5;
		lineX[1][2] = 0.25;		lineY[1][2] = -1.0;	lineZ[1][2] = -0.5;

		//bows on feet
		//left bow
		lineX[3][0] = .125 + 0.1;	lineY[3][0] = -0.85;	lineZ[3][0] = 0.5;
		lineX[3][1] = .125 - 0.1;	lineY[3][1] = -1.05;	lineZ[3][1] = 0.5;

		lineX[3][2] = .125 + 0.1;	lineY[3][2] = -1.05;	lineZ[3][2] = 0.5;
		lineX[3][3] = .125 - 0.1;	lineY[3][3] = -0.85;	lineZ[3][3] = 0.5;

		//right bow
		lineX[4][0] = .125 + 0.1;	lineY[4][0] = -0.85;	lineZ[4][0] = -0.5;
		lineX[4][1] = .125 - 0.1;	lineY[4][1] = -1.05;	lineZ[4][1] = -0.5;

		lineX[4][2] = .125 + 0.1;	lineY[4][2] = -1.05;	lineZ[4][2] = -0.5;
		lineX[4][3] = .125 - 0.1;	lineY[4][3] = -0.85;	lineZ[4][3] = -0.5;

	}
	else if (polyWlegflip == 1) {
		//left leg
		lineX[0][0] = 0.0;		lineY[0][0] = -0.5;	lineZ[0][0] = 0.5;
		lineX[0][1] = 0.2;		lineY[0][1] = -1.0;	lineZ[0][1] = 0.5;
		lineX[0][2] = 0.4;		lineY[0][2] = -0.9;	lineZ[0][2] = 0.5;

		//right leg
		lineX[1][0] = 0.0;		lineY[1][0] = -0.5;	lineZ[1][0] = -0.5;
		lineX[1][1] = -0.3;		lineY[1][1] = -0.9;	lineZ[1][1] = -0.5;
		lineX[1][2] = -0.05;	lineY[1][2] = -1.0;	lineZ[1][2] = -0.5;

		//bows on feet
		//left bow
		lineX[3][0] = .3 + 0.1;		lineY[3][0] = -0.85;	lineZ[3][0] = 0.5;
		lineX[3][1] = .3 - 0.1;		lineY[3][1] = -1.05;	lineZ[3][1] = 0.5;

		lineX[3][2] = .3 + 0.1;		lineY[3][2] = -1.05;	lineZ[3][2] = 0.5;
		lineX[3][3] = .3 - 0.1;		lineY[3][3] = -0.85;	lineZ[3][3] = 0.5;

		//right bow
		lineX[4][0] = -0.15 + 0.1;	lineY[4][0] = -0.85;	lineZ[4][0] = -0.5;
		lineX[4][1] = -0.15 - 0.1;	lineY[4][1] = -1.05;	lineZ[4][1] = -0.5;

		lineX[4][2] = -0.15 + 0.1;	lineY[4][2] = -1.05;	lineZ[4][2] = -0.5;
		lineX[4][3] = -0.15 - 0.1;	lineY[4][3] = -0.85;	lineZ[4][3] = -0.5;
	}
	else {
		//left leg
		lineX[0][0] = 0.0;		lineY[0][0] = -0.5;	lineZ[0][0] = -0.5;
		lineX[0][1] = -0.3;		lineY[0][1] = -0.9;	lineZ[0][1] = -0.5;
		lineX[0][2] = -0.05;	lineY[0][2] = -1.0;	lineZ[0][2] = -0.5;

		//right leg
		lineX[1][0] = 0.0;		lineY[1][0] = -0.5;	lineZ[1][0] = 0.5;
		lineX[1][1] = 0.2;		lineY[1][1] = -1.0;	lineZ[1][1] = 0.5;
		lineX[1][2] = 0.4;		lineY[1][2] = -0.9;	lineZ[1][2] = 0.5;

		//left bow
		lineX[3][0] = .3 + 0.1;		lineY[3][0] = -0.85;	lineZ[3][0] = 0.5;
		lineX[3][1] = .3 - 0.1;		lineY[3][1] = -1.05;	lineZ[3][1] = 0.5;

		lineX[3][2] = .3 + 0.1;		lineY[3][2] = -1.05;	lineZ[3][2] = 0.5;
		lineX[3][3] = .3 - 0.1;		lineY[3][3] = -0.85;	lineZ[3][3] = 0.5;

		//right bow
		lineX[4][0] = -0.15 + 0.1;	lineY[4][0] = -0.85;	lineZ[4][0] = -0.5;
		lineX[4][1] = -0.15 - 0.1;	lineY[4][1] = -1.05;	lineZ[4][1] = -0.5;

		lineX[4][2] = -0.15 + 0.1;	lineY[4][2] = -1.05;	lineZ[4][2] = -0.5;
		lineX[4][3] = -0.15 - 0.1;	lineY[4][3] = -0.85;	lineZ[4][3] = -0.5;
	}

	//setting polywoman's eye
	lineX[2][0] = 0.6;	lineY[2][0] = 0.5;	lineZ[2][0] = 0.5;
	lineX[2][1] = 0.4;	lineY[2][1] = 0.5;	lineZ[2][1] = 0.5;

	lineX[2][2] = 0.6;	lineY[2][2] = 0.5;	lineZ[2][2] = -0.5;
	lineX[2][3] = 0.4;	lineY[2][3] = 0.5;	lineZ[2][3] = -0.5;

	//dreadlocks side closest to viewer
	lineX[5][0] = 0.0;		lineY[5][0] = 0.5;	lineZ[5][0] = 0.5;
	lineX[5][1] = 0.0;		lineY[5][1] = 0.75;	lineZ[5][1] = 0.5; //cornrow 1

	lineX[5][2] = 0.25;		lineY[5][2] = 0.5;	lineZ[5][2] = 0.5;
	lineX[5][3] = 0.25;		lineY[5][3] = 0.75;	lineZ[5][3] = 0.5; //cornrow 2

	lineX[5][4] = -0.25;	lineY[5][4] = 0.5;	lineZ[5][4] = 0.5;
	lineX[5][5] = -0.25;	lineY[5][5] = 0.75;	lineZ[5][5] = 0.5; //cornrow 3

	lineX[5][6] = -0.5;		lineY[5][6] = 0.5;	lineZ[5][6] = 0.5;
	lineX[5][7] = -0.5;		lineY[5][7] = 0.75;	lineZ[5][7] = 0.5; //cornrow 4

	//dreadlocks side farthest from viewer
	lineX[5][8] = 0.0;		lineY[5][8] = 0.5;		lineZ[5][8] = -0.5;
	lineX[5][9] = 0.0;		lineY[5][9] = 0.75;		lineZ[5][9] = -0.5; //cornrow 1

	lineX[5][10] = 0.25;	lineY[5][10] = 0.5;		lineZ[5][10] = -0.5;
	lineX[5][11] = 0.25;	lineY[5][11] = 0.75;	lineZ[5][11] = -0.5; //cornrow 2

	lineX[5][12] = -0.25;	lineY[5][12] = 0.5;		lineZ[5][12] = -0.5;
	lineX[5][13] = -0.25;	lineY[5][13] = 0.75;	lineZ[5][13] = -0.5; //cornrow 3

	lineX[5][14] = -0.5;	lineY[5][14] = 0.5;		lineZ[5][14] = -0.5;
	lineX[5][15] = -0.5;	lineY[5][15] = 0.75;	lineZ[5][15] = -0.5; //cornrow 4

	return;
}//end of loadWIcon

 //function to load squareman's icon
void loadSIcon(float pointX[][10], float pointY[][10], float pointZ[][10], float lineX[][20], float lineY[][20], float lineZ[][20]) {
	
	//set the coordinates of squareman's body
	//square closest to user
	pointX[0][0] = -1.0;	pointY[0][0] = 0.0;		pointZ[0][0] = 0.5;
	pointX[0][1] = 0.0;		pointY[0][1] = 1.0;		pointZ[0][1] = 0.5;
	pointX[0][2] = 1.0;		pointY[0][2] = 0.0;		pointZ[0][2] = 0.5;
	pointX[0][3] = 0.0;		pointY[0][3] = -1.0;	pointZ[0][3] = 0.5;
	pointX[0][4] = -1.0;	pointY[0][4] = 0.0;		pointZ[0][4] = 0.5;

	//square furthest from user
	pointX[1][0] = -1.0;	pointY[1][0] = 0.0;		pointZ[1][0] = -0.5;
	pointX[1][1] = 0.0;		pointY[1][1] = 1.0;		pointZ[1][1] = -0.5;
	pointX[1][2] = 1.0;		pointY[1][2] = 0.0;		pointZ[1][2] = -0.5;
	pointX[1][3] = 0.0;		pointY[1][3] = -1.0;	pointZ[1][3] = -0.5;
	pointX[1][4] = -1.0;	pointY[1][4] = 0.0;		pointZ[1][4] = -0.5;

	//top left 'rectangle'
	pointX[2][0] = -1.0;	pointY[2][0] = 0.0;		pointZ[2][0] = 0.5;
	pointX[2][1] = -1.0;	pointY[2][1] = 0.0;		pointZ[2][1] = -0.5;
	pointX[2][2] = 0.0;		pointY[2][2] = 1.0;		pointZ[2][2] = -0.5;
	pointX[2][3] = 0.0;		pointY[2][3] = 1.0;		pointZ[2][3] = 0.5;
	pointX[2][4] = -1.0;	pointY[2][4] = 0.0;		pointZ[2][4] = 0.5;

	//top right 'rectangle'
	pointX[3][0] = 0.0;		pointY[3][0] = 1.0;		pointZ[3][0] = 0.5;
	pointX[3][1] = 0.0;		pointY[3][1] = 1.0;		pointZ[3][1] = -0.5;
	pointX[3][2] = 1.0;		pointY[3][2] = 0.0;		pointZ[3][2] = -0.5;
	pointX[3][3] = 1.0;		pointY[3][3] = 0.0;		pointZ[3][3] = 0.5;
	pointX[3][4] = 0.0;		pointY[3][4] = 1.0;		pointZ[3][4] = 0.5;

	//bottom right 'rectangle'
	pointX[4][0] = 1.0;		pointY[4][0] = 0.0;		pointZ[4][0] = 0.5;
	pointX[4][1] = 1.0;		pointY[4][1] = 0.0;		pointZ[4][1] = -0.5;
	pointX[4][2] = 0.0;		pointY[4][2] = -1.0;	pointZ[4][2] = -0.5;
	pointX[4][3] = 0.0;		pointY[4][3] = -1.0;	pointZ[4][3] = 0.5;
	pointX[4][4] = 1.0;		pointY[4][4] = 0.0;		pointZ[4][4] = 0.5;

	//bottom left 'rectangle'
	pointX[5][0] = 0.0;		pointY[5][0] = -1.0;	pointZ[5][0] = 0.5;
	pointX[5][1] = 0.0;		pointY[5][1] = -1.0;	pointZ[5][1] = -0.5;
	pointX[5][2] = -1.0;	pointY[5][2] = 0.0;		pointZ[5][2] = -0.5;
	pointX[5][3] = -1.0;	pointY[5][3] = 0.0;		pointZ[5][3] = 0.5;
	pointX[5][4] = 0.0;		pointY[5][4] = -1.0;	pointZ[5][4] = 0.5;

	//set the coordinates of squareman's legs (standing still or flipping them as he walks)
	//still
	if (polySlegflip == 0) {
		//right leg
		lineX[0][0] = 0.0;		lineY[0][0] = -0.5;		lineZ[0][0] = 0.5;
		lineX[0][1] = 0.0;		lineY[0][1] = -1.25;	lineZ[0][1] = 0.5;
		lineX[0][2] = 0.25;		lineY[0][2] = -1.25;	lineZ[0][2] = 0.5;

		//left leg
		lineX[1][0] = 0.0;		lineY[1][0] = -0.5;		lineZ[1][0] = -0.5;
		lineX[1][1] = 0.0;		lineY[1][1] = -1.25;	lineZ[1][1] = -0.5;
		lineX[1][2] = 0.25;		lineY[1][2] = -1.25;	lineZ[1][2] = -0.5;
	}
	else if (polySlegflip == 1) {
		//right leg
		lineX[0][0] = 0.0;		lineY[0][0] = -0.5;	lineZ[0][0] = 0.5;
		lineX[0][1] = 0.2;		lineY[0][1] = -1.2;	lineZ[0][1] = 0.5;
		lineX[0][2] = 0.4;		lineY[0][2] = -1.1;	lineZ[0][2] = 0.5;

		//left leg
		lineX[1][0] = 0.0;		lineY[1][0] = -0.5;	lineZ[1][0] = -0.5;
		lineX[1][1] = -0.25;	lineY[1][1] = -1.1;	lineZ[1][1] = -0.5;
		lineX[1][2] = 0.0;		lineY[1][2] = -1.2;	lineZ[1][2] = -0.5;
	}
	else {
		//right leg
		lineX[0][0] = 0.0;		lineY[0][0] = -0.5;	lineZ[0][0] = -0.5;
		lineX[0][1] = 0.2;		lineY[0][1] = -1.2;	lineZ[0][1] = -0.5;
		lineX[0][2] = 0.4;		lineY[0][2] = -1.1;	lineZ[0][2] = -0.5;

		//left leg
		lineX[1][0] = 0.0;		lineY[1][0] = -0.5;	lineZ[1][0] = 0.5;
		lineX[1][1] = -0.25;	lineY[1][1] = -1.1;	lineZ[1][1] = 0.5;
		lineX[1][2] = 0.0;		lineY[1][2] = -1.2;	lineZ[1][2] = 0.5;
	}

	//setting squareman's eyes
	lineX[2][0] = 0.2;	lineY[2][0] = 0.5;	lineZ[2][0] = 0.5;
	lineX[2][1] = 0.3;	lineY[2][1] = 0.5;	lineZ[2][1] = 0.5;

	lineX[2][2] = 0.2;	lineY[2][2] = 0.5;	lineZ[2][2] = -0.5;
	lineX[2][3] = 0.3;	lineY[2][3] = 0.5;	lineZ[2][3] = -0.5;

	//setting squareman's weapon
	if (attack) {
		lineX[3][0] = -0.25;	lineY[3][0] = 0.0;		lineZ[3][0] = 0.5;
		lineX[3][1] = 1.75;		lineY[3][1] = 0.0;		lineZ[3][1] = 0.5;
		lineX[3][2] = 1.5;		lineY[3][2] = -0.25;	lineZ[3][2] = 0.5;
		lineX[3][3] = 1.5;		lineY[3][3] = 0.25;		lineZ[3][3] = 0.5;
		lineX[3][4] = 1.75;		lineY[3][4] = 0.0;		lineZ[3][4] = 0.5;
	}
	else {
		lineX[3][0] = -0.25;	lineY[3][0] = -0.25;	lineZ[3][0] = 0.5;
		lineX[3][1] = 1.25;		lineY[3][1] = 1.25;		lineZ[3][1] = 0.5;
		lineX[3][2] = 1.25;		lineY[3][2] = 1.0;		lineZ[3][2] = 0.5;
		lineX[3][3] = 1.0;		lineY[3][3] = 1.25;		lineZ[3][3] = 0.5;
		lineX[3][4] = 1.25;		lineY[3][4] = 1.25;		lineZ[3][4] = 0.5;
	}

	return;
}

 //this function draws the polyman icon at the transformed position
void drawMIcon(float pointXprime[][10], float pointYprime[][10], float pointZprime[][10], float lineXprime[][10], float lineYprime[][10], float lineZprime[][10]) {

	//set the drawing color to white
	glColor3f(1.0, 1.0, 1.0);

	//move to the first point in icon
	glBegin(GL_LINE_STRIP);

	//now outline polyman..
	//with his mouth open
	if (polyMopenmouth) {// i <= 9 if do points for top of mouth
		
		//go through the rows
		for (int i = 0; i <= 8; i++) { 
			
			//the first two rows deal with the hexagonal bodies
			if(i < 2){
				for (int j = 0; j <= 7; j++) { glVertex3f(pointXprime[i][j], pointYprime[i][j], pointZprime[i][j]); }
			}
			else {
				for (int j = 0; j <= 4; j++) { glVertex3f(pointXprime[i][j], pointYprime[i][j], pointZprime[i][j]); }
			}//end of if-else
		}//end of i for loop
	}//end of true mouthopen if

	//with his mouth closed
	else {

		//go through all the rows
		for (int i = 0; i <= 7; i++) { 

			//the first two rows deal with the hexagonal bodies
			if (i < 2) {
				for(int j = 0; j <= 7; j++) { glVertex3f(pointXprime[i][j], pointYprime[i][j], pointZprime[i][j]); }
			}
			else {
				for (int j = 0; j <= 4; j++) { glVertex3f(pointXprime[i][j], pointYprime[i][j], pointZprime[i][j]); }
			}//end of if-else
		}//end of i for loop
	}//end of false mouthopen if
	
	glEnd();
	glFlush();

	//now draw the legs
	glBegin(GL_LINES);
	glVertex3f(lineXprime[0][0], lineYprime[0][0], lineZprime[0][0]);
	glVertex3f(lineXprime[0][1], lineYprime[0][1], lineZprime[0][1]);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(lineXprime[0][1], lineYprime[0][1], lineZprime[0][1]);
	glVertex3f(lineXprime[0][2], lineYprime[0][2], lineZprime[0][2]);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(lineXprime[1][0], lineYprime[1][0], lineZprime[1][0]);
	glVertex3f(lineXprime[1][1], lineYprime[1][1], lineZprime[1][1]);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(lineXprime[1][1], lineYprime[1][1], lineZprime[1][1]);
	glVertex3f(lineXprime[1][2], lineYprime[1][2], lineZprime[1][2]);
	glEnd();
	glFlush();

	//draw the 'eyes'
	if (dead) {
		for (int i = 0; i <= 7; i++) {
			glBegin(GL_LINES);
			glVertex3f(lineXprime[2][i], lineYprime[2][i], lineZprime[2][i]);
			glVertex3f(lineXprime[2][i+1], lineYprime[2][i+1], lineZprime[2][i+1]);
			glEnd();
			i++;
		}
	}
	else {
		for (int i = 0; i <= 3; i++) {
			glBegin(GL_LINES);
			glVertex3f(lineXprime[2][i], lineYprime[2][i], lineZprime[2][i]);
			glVertex3f(lineXprime[2][i + 1], lineYprime[2][i + 1], lineZprime[2][i + 1]);
			glEnd();
			i++;
		}
	}
	glFlush();
	return;

}//end of drawMIcon

 //this function draws the polywoman icon at the transformed position
void drawWIcon(float pointXprime[][10], float pointYprime[][10], float pointZprime[][10], float lineXprime[][25], float lineYprime[][25], float lineZprime[][25]) {

	//set the drawing color to white
	glColor3f(1.0, 1.0, 1.0);

	//move to the first point in icon
	glBegin(GL_LINE_STRIP);

	//now outline polywoman..
	//with her mouth open
	if (polyWopenmouth) {// i <= 9 if do points for top of mouth

		//go through the rows
		for (int i = 0; i <= 8; i++) { 

			//the first two rows deal with the hexagonal bodies
			if (i < 2) {
				for (int j = 0; j <= 7; j++) { glVertex3f(pointXprime[i][j], pointYprime[i][j], pointZprime[i][j]); }
			}
			else {
				for (int j = 0; j <= 4; j++) { glVertex3f(pointXprime[i][j], pointYprime[i][j], pointZprime[i][j]); }
			}//end of if-else
		}//end of i for loop
	}//end of true mouthopen if

	 //with her mouth closed
	else {

		//go through all the rows
		for (int i = 0; i <= 7; i++) {

			//the first two rows deal with the hexagonal bodies
			if (i < 2) {
				for (int j = 0; j <= 7; j++) { glVertex3f(pointXprime[i][j], pointYprime[i][j], pointZprime[i][j]); }
			}
			else {
				for (int j = 0; j <= 4; j++) { glVertex3f(pointXprime[i][j], pointYprime[i][j], pointZprime[i][j]); }
			}//end of if-else
		}//end of i for loop
	}//end of false mouthopen if

	glEnd();
	glFlush();

	//now draw the legs
	glBegin(GL_LINES);
	glVertex3f(lineXprime[0][0], lineYprime[0][0], lineZprime[0][0]);
	glVertex3f(lineXprime[0][1], lineYprime[0][1], lineZprime[0][1]);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(lineXprime[0][1], lineYprime[0][1], lineZprime[0][1]);
	glVertex3f(lineXprime[0][2], lineYprime[0][2], lineZprime[0][2]);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(lineXprime[1][0], lineYprime[1][0], lineZprime[1][0]);
	glVertex3f(lineXprime[1][1], lineYprime[1][1], lineZprime[1][1]);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(lineXprime[1][1], lineYprime[1][1], lineZprime[1][1]);
	glVertex3f(lineXprime[1][2], lineYprime[1][2], lineZprime[1][2]);
	glEnd();
	glFlush();

	//draw the 'eyes'
	for (int i = 0; i <= 3; i++) {
		glBegin(GL_LINES);
		glVertex3f(lineXprime[2][i], lineYprime[2][i], lineZprime[2][i]);
		glVertex3f(lineXprime[2][i + 1], lineYprime[2][i + 1], lineZprime[2][i + 1]);
		glEnd();
		i++;
	}
	glFlush();

	//draw the bows
	for (int i = 3; i <= 4; i++) {
		for (int j = 0; j <= 3; j++) { 
			glBegin(GL_LINES);
			glVertex3f(lineXprime[i][j], lineYprime[i][j], lineZprime[i][j]);
			glVertex3f(lineXprime[i][j + 1], lineYprime[i][j + 1], lineZprime[i][j + 1]);
			glEnd();
			j++;
		}
	}
	glFlush();

	//draw the dreadlocks
	for (int i = 0; i <= 15; i++) {
		glBegin(GL_LINES);
		glVertex3f(lineXprime[5][i], lineYprime[5][i], lineZprime[5][i]);
		glVertex3f(lineXprime[5][i + 1], lineYprime[5][i + 1], lineZprime[5][i + 1]);
		glEnd();
		i++;
	}
	glFlush();

	return;

}//end of drawWIcon

 //this function draws the squareman icon at the transformed position
void drawSIcon(float pointXprime[][10], float pointYprime[][10], float pointZprime[][10], float lineXprime[][20], float lineYprime[][20], float lineZprime[][20]) {

	//set the drawing color to white
	glColor3f(1.0, 1.0, 1.0);

	//move to the first point in icon
	glBegin(GL_LINE_STRIP);

	//now outline squareman..
	for (int i = 0; i <= 5; i++) {
		for (int j = 0; j <= 4; j++) { glVertex3f(pointXprime[i][j], pointYprime[i][j], pointZprime[i][j]); }
	}

	glEnd();
	glFlush();

	//now draw the legs
	glBegin(GL_LINES);
	glVertex3f(lineXprime[0][0], lineYprime[0][0], lineZprime[0][0]);
	glVertex3f(lineXprime[0][1], lineYprime[0][1], lineZprime[0][1]);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(lineXprime[0][1], lineYprime[0][1], lineZprime[0][1]);
	glVertex3f(lineXprime[0][2], lineYprime[0][2], lineZprime[0][2]);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(lineXprime[1][0], lineYprime[1][0], lineZprime[1][0]);
	glVertex3f(lineXprime[1][1], lineYprime[1][1], lineZprime[1][1]);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(lineXprime[1][1], lineYprime[1][1], lineZprime[1][1]);
	glVertex3f(lineXprime[1][2], lineYprime[1][2], lineZprime[1][2]);
	glEnd();
	glFlush();

	//draw the 'eyes'
	for (int i = 0; i <= 3; i++) {
		glBegin(GL_LINES);
		glVertex3f(lineXprime[2][i], lineYprime[2][i], lineZprime[2][i]);
		glVertex3f(lineXprime[2][i + 1], lineYprime[2][i + 1], lineZprime[2][i + 1]);
		glEnd();
		i++;
	}
	glFlush();

	//draw squareman's weapon
	for (int i = 0; i < 4; i++) {
		glBegin(GL_LINES);
		glVertex3f(lineXprime[3][i], lineYprime[3][i], lineZprime[3][i]);
		glVertex3f(lineXprime[3][i + 1], lineYprime[3][i + 1], lineZprime[3][i + 1]);
		glEnd();
	}
	glFlush();
	return;

}//end of drawSIcon

//settrans for polyman
void settrans1(void) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(polyMdx, polyMdy, polyMdz);
	glRotatef(polyMAngle, 1.0, 0.0, 0.0);
	glRotatef(polyMAngle, 0.0, 1.0, 0.0);
	glRotatef(polyMAngle, 0.0, 0.0, 1.0);
	return;
}//end of settrans1

 //settrans for polywoman
void settrans2(void) {
	//looks right
	if (frame < 16 || frame == 17) {
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(polyWdx, polyWdy, polyWdz);
		glRotatef(polyWAngle, 1.0, 0.0, 0.0);
		glRotatef(polyWAngle, 0.0, 1.0, 0.0);
		glRotatef(polyWAngle, 0.0, 0.0, 1.0);
	}
	//looks to the left
	else {
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(polyWdx, polyWdy, polyWdz);
		//glRotatef(polyWAngle, 1.0, 0.0, 0.0);
		glRotatef(180.0, 0.0, 1.0, 0.0);
		//glRotatef(polyWAngle, 0.0, 0.0, 1.0);
	}
	return;
}//end of settrans2

 //settrans for squarewoman
void settrans3(void) {
	//looks right
	if (frame < 15) {
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(polySdx, polySdy, polySdz);
		glRotatef(polySAngle, 1.0, 0.0, 0.0);
		glRotatef(polySAngle, 0.0, 1.0, 0.0);
		glRotatef(polySAngle, 0.0, 0.0, 1.0);
	}
	//looks to the left
	else {
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(polySdx, polySdy, polySdz);
		//glRotatef(polySAngle, 1.0, 0.0, 0.0);
		glRotatef(180.0, 0.0, 1.0, 0.0);
		//glRotatef(polySAngle, 0.0, 0.0, 1.0);
	}

	return;
}//end of settrans3

//walk function
void walk(char a) {
	if(a == 'm'){
		if (frameCount % 40 == 0)  { polyMlegflip = 0; }
		if (frameCount % 40 == 10) { polyMlegflip = 1; }
		if (frameCount % 40 == 20) { polyMlegflip = 0; }
		if (frameCount % 40 == 30) { polyMlegflip = 2; }
	}
	else if (a == 'w') {
		if (frameCount % 40 == 0) { polyWlegflip = 0; }
		if (frameCount % 40 == 10) { polyWlegflip = 1; }
		if (frameCount % 40 == 20) { polyWlegflip = 0; }
		if (frameCount % 40 == 30) { polyWlegflip = 2; }
	}
	else {
		if (frameCount % 40 == 0) { polySlegflip = 0; }
		if (frameCount % 40 == 10) { polySlegflip = 1; }
		if (frameCount % 40 == 20) { polySlegflip = 0; }
		if (frameCount % 40 == 30) { polySlegflip = 2; }
	}
}

void setupRC(void) {
	glClearColor(0.0, 0.0, 1.0, 1.0);
	return;
}

//engine to handle the 30 fps. Uses global variables andgles and frame
void timerFunction(int value) {
	cout << frame << endl;

	switch (frame) {
	case 1:
		//polyman starts at the right and moves left
		polyMdx -= 0.1;

		//polywoman starts at the left and moves right
		polyWdx += 0.1;

		//polyman flip legs every 10 frames
		if (frameCount % 10 == 0) { walk('m'); }

		//polywoman walks until stopping 
		if (polyWdx < -4) {
			if (frameCount % 10 == 0) { walk('w'); }
		}
		else {
			polyWdx = -4;
			polyWlegflip = false;
		}

		//polyman stops at the middle of the screen
		if (polyMdx <= 1.0) {
			polyMlegflip = false;
			polyMdx = 1.0;
			frame = 2;
		}
		break;
	case 2:
		//polyman begins rising in the middle of the screen
		polyMdy += 0.1;
		polyMAngle += 10.0;

		if (polyMAngle >= 180.0) {
			polyMAngle = 180.0;
			frame = 3;
		}
		break;
	case 3:
		//polyman begins descending
		polyMdy -= 0.1;
		polyMAngle += 10.0;

		if (polyMAngle >= 360.0) {
			polyMdy = 0.0;
			polyMAngle = 0.0;
			polyMopenmouth = true;
			frame = 4;
		}
		break;
	case 4:
		//polywoman rocks back...
		polyWAngle -= 3.0;

		if (polyWAngle <= -45.0) {
			polyWAngle = -45.0;
			frame = 5;
		}
		break;
	case 5:
		//... and forth...
		polyWAngle += 3.0;

		if (polyWAngle >= 45.0) {
			polyWAngle = 45.0;
			frame = 6;
		}
		break;
	case 6:
		//polywoman back to normal
		polyWAngle -= 3.0;

		if (polyWAngle <= 0.0) {
			polyWAngle = 0.0;
			polyMopenmouth = false;
			frame = 7;
		}
		break;
	case 7:
		//squareman comes out
		polySdx += 0.1;
		polySdz += 0.1;

		//squareman flip legs every 10 frames
		if (frameCount % 10 == 0) { walk('s'); }

		if (polySdx >= -5.5) {
			polySdx = -5.5;
			frame = 8;
		}
		break;
	case 8:
		//squareman moves past polywoman
		polySdx += 0.1;
		polySdz -= 0.105;			//hopefully squareman can stab polyman straight through

		//squareman flip legs every 10 frames
		if (frameCount % 10 == 0) { walk('s'); }

		if (polySdx >= -2.0) {
			polySdx = -2.0;
			polySlegflip = false;
			attack = true;
			frame = 9;
		}
		break;
	case 9:
		//wait to build tension
		if (frameCount == 350) {
			frame = 10;
		}
		break;
	case 10:
		//squareman attacks
		polySdx += 0.7;

		if (polySdx >= -1.3) {
			polyWopenmouth = true;
			dead = true;
			polySdx = -1.3;
			frame = 11;
		}
		break;
	case 11:
		//wait to let it sink in
		if (frameCount == 400) {
			frame = 12;
		}
		break;
	case 12:
		//squareman back up
		polySdx -= 0.7;

		if (polySdx <= -2.0) {
			polySdx = -2.0;
			attack = false;
			frame = 13;
		}
		break;
	case 13:
		//wait some more
		if (frameCount == 475) {
			frame = 14;
		}
		break;
	case 14:
		//polyman slowly rolls back dead
		polyMAngle -= 5.0;

		if (polyMAngle <= -90.0) {
			polyMAngle = -90.0;
			frame = 15;
		}
		break;
	case 15:
		//wait some more
		if (frameCount == 550) {
			frame = 16;
		}
		break;
	case 16:
		//squareman turns and walks away
		polySdx -= 0.1;
		polySdz += 0.105;				//hopefully this is far enough away to not hit polywoman

		if (frameCount % 10 == 0) { walk('s'); }

		if (polySdx <= -9.0) {
			polySdx = -9.0;
			frame = 17;
		}
		break;
	case 17:
		//polywoman turns to look at squareman
		if (frameCount == 650) {
			frame = 18;
		}
		break;
	case 18:
		//polywoman turns to look at polyman
		if (frameCount == 700) {
			polyWopenmouth = false;
			frame = 19;
		}
		break;
	case 19:
		//polywoman turns around and walks after squareman
		polyWdx -= 0.1;
		polyWdz += 0.1;			//following squareman
		if (frameCount % 10 == 0) { walk('w'); }

		if (polyWdx <= -9.0) {
			polyWdx = -9.0;
		}
		break;
	}

	frameCount += 1;
	glutPostRedisplay();
	glutTimerFunc(30, timerFunction, 0);
}//end of timerFunction