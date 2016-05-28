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

#define pi 3.141591
using namespace std;

int WindowHeight = 680;
int WindowWidth  = 1350;
int TableLong = 603.5;
int TableWidth = 300.9;
float BallRadius = 12;
float BallCord[5][12];
int SPSU = 40;
int cons=3;
float resistance = 0.5; 
float k = 0;
float MassOfBall = 0.285;
float f = 0.1;
float g = 9.81;


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
		glVertex3i(int( - TableLong), int( - TableWidth), 0);
		glVertex3i(int( - TableLong), int( + TableWidth), 0);
		glVertex3i(int( + TableLong), int( + TableWidth), 0);
		glVertex3i(int( + TableLong), int( - TableWidth), 0);
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

void PrintBalls (Ball B)
{
	vector3f v1, v2, hal = vector3f(0,0,BallRadius);
	float i, j;
	float t = 10;
	glBegin(GL_QUAD_STRIP);
	glColor3f(1.0, 1.0, 1.0);
	for (i = 0; i < 180/t; i++){
		glColor3f((i*t/180), (i*t/180), (i*t/180));
		v1.z = -cos((i*t/180) * pi);
		v2.z = -cos(((i+1)*t/180) * pi);
		for (j = 0; j < 360/t + 1; j++){
			v1.x = sin((j*t/180) * pi) * sin((i*t/180) * pi);
			v1.y = cos((j*t/180) * pi) * sin((i*t/180) * pi);
			v2.x = sin((j*t/180) * pi) * sin(((i+1)*t/180) * pi);
			v2.y = cos((j*t/180) * pi) * sin(((i+1)*t/180) * pi);
			v3f(B.position + hal + (v1 * BallRadius));
			v3f(B.position + hal + (v2 * BallRadius));
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
	return (B.speed * SPSU) + (B.speed.vUnit() * (-f*g*SPSU*SPSU/2));
}

vector3f dv (Ball B)
{
	return B.speed.vUnit() * (-f*g*SPSU);
}

Ball motion (Ball B)
{
	Ball B1;
	B1.position = B.position + dr(B);
	B1.speed = B.speed + dv(B);
	B1.spin = vector3f(0.0, 0.0, 0.0);
	return B1;
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	Table();
	PrintBalls(Bal);
	glutSwapBuffers();
}

void Timer(int)
{
	k+=0.1;
	Bal = motion(Bal);
	glutPostRedisplay();
	glutTimerFunc(SPSU, Timer, 0);
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
			Bal.speed = vector3f (0, 0, 0);
			break;
		case '4': 
			cout<<clock()/CLOCKS_PER_SEC<<endl;
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
	Bal.position = vector3f(0, 0, 0);
	Bal.spin = vector3f(0, 0, 0);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowSize(WindowWidth, WindowHeight);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Proccesing");
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keybord);
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



