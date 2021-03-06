// bbbbbbb.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <Windows.h>
#include <math.h>
#include <time.h>
#include <GL/glut.h>
#include <conio.h>
#include <iostream>
#include "vector3f.h"

#define PI 3.141591
#define mM_PER_PIXEL 6
#define TABLE_WIDTH 1750 //mM
#define TABLE_LENGTH 3500 //mM
#define BALL_RADIUS 62 //mM
#define BALL_MASS 0.28 // Kg
#define SPSU 20 //mSeconds Per Screen Update
#define f 0.01
#define G 9810 // mM/sec^2
using namespace std;

int WindowHeight = 680;
int WindowWidth  = 1350;
vector3f yie = vector3f(0, 0, 0);
float yieM = 1;
int TableLength = TABLE_LENGTH / mM_PER_PIXEL;
int TableWidth = TABLE_WIDTH / mM_PER_PIXEL;
float BallRadius = float(BALL_RADIUS) / float(mM_PER_PIXEL);
float g = (float(G * SPSU * SPSU)) / (float(mM_PER_PIXEL * 1000000));
//float BallCord[5][12];
//int SPSU = 40;
//int cons=3;
//float resistance = 0.5; 
float k = 0;
//float MassOfBall = 0.285;
//float f = 0.1;
//float g = 9.81;
float angle = 0;


struct Ball
{
	//Ball * next;
	//bool Available;
	vector3f position;
	vector3f speed;
	vector3f spin; 
} Bal;

void Table()
{
	/*int Vector1[3] = { TableSize[0], 0, 0 };
	int Vector2[3] = { 0, TableSize[1], 0 };
	int Vector3[3] = { 0, 0, -5};
	WireBar(int(-TableSize[0]/2), int(-TableSize[1]/2), 0, Vector1, Vector2, Vector3);*/
	glBegin(GL_QUADS);
		glColor3f(0.05, 0.65, 0.4);
		glVertex3i(int( - TABLE_LENGTH / mM_PER_PIXEL), int( - TABLE_WIDTH / mM_PER_PIXEL), 0);
		glVertex3i(int( - TABLE_LENGTH / mM_PER_PIXEL), int( + TABLE_WIDTH / mM_PER_PIXEL), 0);
		glVertex3i(int( + TABLE_LENGTH / mM_PER_PIXEL), int( + TABLE_WIDTH / mM_PER_PIXEL), 0);
		glVertex3i(int( + TABLE_LENGTH / mM_PER_PIXEL), int( - TABLE_WIDTH / mM_PER_PIXEL), 0);
	glEnd();
}
/*void CompBall(vector3f BallCoord[5][12])
{
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 12; j++){
			BallCoord[i][j].x = sin(j*3.1416/6);  
			BallCoord[i][j].y = sin(((i+1)*3.1416)/6);
			BallCoord[i][j].z = cos((j*3.1416)/6);
		}
	}
}*/

void v3f(vector3f v)
{
	glVertex3f(v.x, v.y, v.z);
}

void CalcBalls (Ball B)
{
	vector3f v1, v2;
	float i, j;
	float t = 10;
	glBegin(GL_QUAD_STRIP);
	glColor3f(1.0, 1.0, 1.0);
	for (i = 0; i < 180/t; i++){
		glColor3f((i*t/180), (i*t/180), (i*t/180));
		v1.z = -cos((i*t/180) * PI);
		v2.z = -cos(((i+1)*t/180) * PI);
		for (j = 0; j < 360/t + 1; j++){
			v1.x = sin((j*t/180) * PI) * sin((i*t/180) * PI);
			v1.y = cos((j*t/180) * PI) * sin((i*t/180) * PI);
			v2.x = sin((j*t/180) * PI) * sin(((i+1)*t/180) * PI);
			v2.y = cos((j*t/180) * PI) * sin(((i+1)*t/180) * PI);
			v3f(B.position + (v1 * (BallRadius)));
			v3f(B.position + (v2 * (BallRadius)));
		}
	}
	glEnd();
}

/*void BallVectors (Ball * Bal)
{
	float Res[2];
	if (Bal[0].speed.x >= TableLong/2 || Bal[0].speed.x <= -TableLong/2) 
		Bal[0].speed.x *= -1;
	if (Bal[0].position.y >= TableWidth/2 || Bal[0].position.y <= -TableWidth/2) 
		Bal[0].speed.x *= -1;
	if (Bal[0].speed.x){
		Res[0]=sqrt(resistance*resistance/((Bal[0].speed.y / Bal[0].speed[0])*(Bal[0].speed.y / Bal[0].speed.x)+1));
		if (Bal[0].speed.x>0) Res[0] *= -1;
		Bal[0].speed.x += Res[0];
		Bal[0].position.x += Bal[0].speed.x;
	}
	if (Bal[0].speed.y){
		Res[1]=sqrt(resistance*resistance/((Bal[0].speed.x / Bal[0].speed.y) * (Bal[0].speed.x / Bal[0].speed.y)+1));
		if (Bal[0].speed.y > 0) Res[1] *= -1;
		Bal[0].Speed.y += Res[1];
		Bal[0].position.y += Bal[0].speed.y;
	}

}*/



vector3f dr (Ball B)
{
	//return (B.speed * (SPSU/10)) + (B.speed.vUnit() * (-f*(g*mM_PER_PIXEL/1000)*SPSU*SPSU/200));
	//return B.speed * SPSU + (B.speed.vUnit() * (-f*g*SPSU*SPSU/2));
	return B.speed + (B.speed.vUnit() * (-f*g/2));
}

vector3f dv (Ball B)
{
	//return B.speed.vUnit() * (-f*(g*mM_PER_PIXEL/1000)*SPSU/10);
	//return B.speed.vUnit() * (-f*g*SPSU);
	return B.speed.vUnit() * (-f*g);
}

Ball motion (Ball B)
{
	Ball B1;
	if (abs(B.position.x + dr(B).x) > TableLength - BallRadius){
		B1.position = B.position + dr(B) - vector3f(2(TableLength - BallRadius - B.position.x), 0 , 0);
		B1.speed.x = -0.8 * B.speed.x;
		B1.speed.y = B.speed.y / (abs(B.speed.x)/5 + 1);
	}
	if (abs(B.position.y + dr(B).y) > TableWidth - BallRadius){
		B1.position = B.position + dr(B) - vector3f(0, 2(TableWidth - BallRadius - B.position.y), 0);
		B1.speed.y = -0.8 * B.speed.y;
		B1.speed.x = B.speed.x / (abs(B.speed.y)/5 + 1);
	}
	if (!(abs(B.position.x + dr(B).x) > TableLength - BallRadius) && !(abs(B.position.y + dr(B).y) > TableWidth - BallRadius)) {
		B1.position = B.position + dr(B);
		B1.speed = B.speed + dv(B);
	}
/*	if (abs(B1.position.x) > TableLength - BallRadius){
		B1.speed.x *= -1;
		B1.speed.y /= abs(B1.speed.x)/5 + 1;
	}
	if (abs(B1.position.y) > TableWidth - BallRadius){
		B1.speed.y *= -1;
		B1.speed.x /= abs(B1.speed.x)/5 + 1;
	}*/
	B1.spin = vector3f(0.0, 0.0, 0.0);
	return B1;
}

void Display()
{
	/*glRotatef(yie.x, 1, 0, 0);
	glRotatef(yie.x, 0, 1, 0);
	glRotatef(yie.x, 0, 0, 1);*/
	glClear(GL_COLOR_BUFFER_BIT);
	Table();
	PrintBalls(Bal);
	glutSwapBuffers();
	/*glRotatef(-yie.x, 1, 0, 0);
	glRotatef(-yie.x, 0, 1, 0);
	glRotatef(-yie.x, 0, 0, 1);*/
}

void Timer(int)
{
	k+=0.1;
	Bal = motion(Bal);
	glutPostRedisplay();
	glutTimerFunc(SPSU, Timer, 0);
}

void PassiveMotion(int x, int y)
{
	static int px;
	static int py;

/*	if( x>px ) glRotatef(-5,0.0,0.0,1.0);
	if( x<px ) glRotatef( 5,0.0,0.0,1.0);
	if( y>py ) glRotatef(-5,1.0,0.0,0.0);
	if( y<py ) glRotatef( 5,1.0,0.0,0.0);*/
	if( x>px ){
		yie.z = yie.z + 1;
		if (yie.z > 360) yie.z -= 360;
		if (yie.z < 0) yie.z += 360;
		glRotatef(1, 0, 0, 1);
	}
	if( x<px ){
		yie.z = yie.z - 1;
		if (yie.z > 360) yie.z -= 360;
		if (yie.z < 0) yie.z += 360;
		glRotatef(-1, 0, 0, 1);
	}
	if( y>py ){
		/*glRotatef(cos(yie.z/360), 1, 0, 0);
		glRotatef(sin(yie.z/360), 0, 1, 0);*/
		glRotatef(1, cos(yie.z/360), sin(yie.z/360), 0);
		//yie.x = yie.x + sin(yie.z/360);
		//yie.y = yie.y + cos(yie.z/360);
		//if (yie.x > 360) yie.x -= 360;
		//if (yie.x < 0) yie.x += 360;
	}
	if( y<py ){
		/*glRotatef(-cos(yie.z/360), 1, 0, 0);
		glRotatef(-sin(yie.z/360), 0, 1, 0);*/

		glRotatef(-1, cos(yie.z/360), sin(yie.z/360), 0);

		//yie.x = yie.x - sin(yie.z/360);
		//yie.y = yie.y - cos(yie.z/360);
		//if (yie.y > 360) yie.y -= 360;
		//if (yie.y < 0) yie.y += 360;
	}
	px=x; py=y;
}

void Keybord(unsigned char key, int x, int y)
{
	switch(key) 
	{
		case 'd': 
			glRotatef(-1,0.0,0.0,1.0);
			break;
		case 'a': 
			glRotatef(1,0.0,0.0,1.0);
			break;
		case 'w':
			glRotatef(0.5,1.0,0.0,0.0);
			break;
		case 's':
			glRotatef(-0.5,1.0,0.0,0.0);
			break;
		case 'q':
			glRotatef(1,0.0,1.0,0.0);
			break;
		case 'e':
			glRotatef(-1,0.0,1.0,0.0);
			break;
		case '1':
			glScalef(0.8,0.8,0.8);
			break;
		case '2':
			glScalef(1.25,1.25,1.25);
			break;
		case '3':
			Bal.speed = vector3f(1, 0, 0);
			break;
		case '4': 
			Bal.speed = vector3f(3, 3, 0);
			 break;
		case 'i':
			glTranslatef(0,10,0);
			break;
		case 'k':
			glTranslatef(0,-10,0);
			break;
		case 'j':
			glTranslatef(-10,0,0);
			break;
		case 'l':
			glTranslatef(10,0,0);
			break;
		case 'u':
			glTranslatef(0,0,10);
			break;
		case 'o':
			glTranslatef(0,0,-10);
			break;
	}
}

int main(int argc, char ** argv)
{
	Bal.speed = vector3f(0, 0, 0);
	Bal.position = vector3f(0, BallRadius, 0);
	Bal.spin = vector3f(0, 0, 0);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowSize(WindowWidth, WindowHeight);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Proccesing");
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keybord);
	glutMotionFunc(PassiveMotion);
	glutTimerFunc(SPSU, Timer, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(50, WindowWidth/WindowHeight, 1, 20000);
	glOrtho(-WindowWidth/2,WindowWidth/2,-WindowHeight/2,WindowHeight/2,-5000,5000);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glutMainLoop();
	return 0;
}



