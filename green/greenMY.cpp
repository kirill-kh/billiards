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
#include "constant.h"
#include "vector3f.h"
#include "Ball.h"
using namespace std;

int WindowHeight = 680;
int WindowWidth  = 1350;
vector3f yie = vector3f(0, 0, 0);
float yieM = 1;
int TableLength = TABLE_LENGTH / mM_PER_PIXEL;
int TableWidth = TABLE_WIDTH / mM_PER_PIXEL;
int BrownBoardWidth = BROWN_BOARD_WIDTH / mM_PER_PIXEL;
float BallRadius = float(BALL_RADIUS) / float(mM_PER_PIXEL);
float g = (float(G * SPSU * SPSU)) / (float(mM_PER_PIXEL * 1000000));
float k = 0;
float angle = 0;
float Pocket = POCKET / mM_PER_PIXEL;
int BoardWidth = Pocket / 1.4142;
vector3f BallCoords[360/BALL_ACCURACY + 1][180/BALL_ACCURACY + 1];
vector3f cue;
vector3f pos;
Ball Bal[16];
int CurrentBall;
float latitude = 0.0;
float longitude = 0.0;
bool looking = false;
float scale = 1.0;
int px = 0;
int py = 0;

void init(void)
{
   GLfloat mat_specular[]={1.0,1.0,1.0,1.0};
   GLfloat mat_shininess[]={50.0,0.0};
   GLfloat light_position[]={0.0,0.0,-600.0,1.0};
   GLfloat white_light[]={1.0,1.0,1.0,1.0};

   glClearColor(0.0,0.0,0.0,0.0); 
   glShadeModel(GL_SMOOTH);
   glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular); 
   glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess); 
   glLightfv(GL_LIGHT0,GL_POSITION,light_position); 
   glLightfv(GL_LIGHT0,GL_DIFFUSE,white_light); 
   glLightfv(GL_LIGHT0,GL_SPECULAR,white_light);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_NORMALIZE);
}

void Table()
{
	glBegin(GL_QUADS);
		glColor3f(0.0, 0.65, 0.4);
		glVertex3i(int( - 10), int( - 10), 10);
		glVertex3i(int( - 10), int( + 10), 10);
		glVertex3i(int( + 10), int( + 10), 10);
		glVertex3i(int( + 10), int( - 10), 10);
		
		glColor3f(0.0, 0.65, 0.4);
		glVertex3i(int( - TableLength), int( - TableWidth), 0);
		glVertex3i(int( - TableLength), int( + TableWidth), 0);
		glVertex3i(int( + TableLength), int( + TableWidth), 0);
		glVertex3i(int( + TableLength), int( - TableWidth), 0);
		//board
		
		glColor3f(0.0, 0.8, 0.5);
		glVertex3i(int( - TableLength + BoardWidth), int( + TableWidth), 12);
		glVertex3i(int( + TableLength - BoardWidth), int( + TableWidth), 12);
		glColor3f(0.0, 0.6, 0.35);
		glVertex3i(int( + TableLength), int( + TableWidth + BoardWidth), 15);
		glVertex3i(int( - TableLength), int( + TableWidth + BoardWidth), 15);

		glColor3f(0.3, 0.2, 0.05);
		glVertex3i(int( - TableLength - BoardWidth - BrownBoardWidth), int( + TableWidth + BoardWidth + BrownBoardWidth), 15);
		glVertex3i(int( + TableLength + BoardWidth + BrownBoardWidth), int( + TableWidth + BoardWidth + BrownBoardWidth), 15);
		glVertex3i(int( + TableLength + BoardWidth), int( + TableWidth + BoardWidth), 15);
		glVertex3i(int( - TableLength - BoardWidth), int( + TableWidth + BoardWidth), 15);

		glColor3f(0.0, 0.8, 0.5);
		glVertex3i(int( - TableLength + BoardWidth), int( - TableWidth), 12);
		glVertex3i(int( + TableLength - BoardWidth), int( - TableWidth), 12);
		glColor3f(0.0, 0.6, 0.35);
		glVertex3i(int( + TableLength), int( - TableWidth - BoardWidth), 15);
		glVertex3i(int( - TableLength), int( - TableWidth - BoardWidth), 15);

		glColor3f(0.3, 0.2, 0.05);
		glVertex3i(int( - TableLength - BoardWidth), int( - TableWidth - BoardWidth), 15);
		glVertex3i(int( + TableLength + BoardWidth), int( - TableWidth - BoardWidth), 15);
		glVertex3i(int( + TableLength + BoardWidth + BrownBoardWidth), int( - TableWidth - BoardWidth - BrownBoardWidth), 15);
		glVertex3i(int( - TableLength - BoardWidth - BrownBoardWidth), int( - TableWidth - BoardWidth - BrownBoardWidth), 15);

		glColor3f(0.0, 0.8, 0.5);
		glVertex3i(int( - TableLength), int( - TableWidth + BoardWidth), 12);
		glVertex3i(int( - TableLength), int( + TableWidth - BoardWidth), 12);
		glColor3f(0.0, 0.6, 0.35);
		glVertex3i(int( - TableLength - BoardWidth), int( + TableWidth), 15);
		glVertex3i(int( - TableLength - BoardWidth), int( - TableWidth), 15);

		glColor3f(0.3, 0.2, 0.05);
		glVertex3i(int( - TableLength - BoardWidth), int( - TableWidth - BoardWidth), 15);
		glVertex3i(int( - TableLength - BoardWidth), int( + TableWidth + BoardWidth), 15);
		glVertex3i(int( - TableLength - BoardWidth - BrownBoardWidth), int( + TableWidth + BoardWidth + BrownBoardWidth), 15);
		glVertex3i(int( - TableLength - BoardWidth - BrownBoardWidth), int( - TableWidth - BoardWidth - BrownBoardWidth), 15);

		glColor3f(0.0, 0.8, 0.5);
		glVertex3i(int( + TableLength), int( - TableWidth + BoardWidth), 12);
		glVertex3i(int( + TableLength), int( + TableWidth - BoardWidth), 12);
		glColor3f(0.0, 0.6, 0.35);
		glVertex3i(int( + TableLength + BoardWidth), int( + TableWidth), 15);
		glVertex3i(int( + TableLength + BoardWidth), int( - TableWidth), 15);

		glColor3f(0.3, 0.2, 0.05);
		glVertex3i(int( + TableLength + BoardWidth), int( - TableWidth - BoardWidth), 15);
		glVertex3i(int( + TableLength + BoardWidth), int( + TableWidth + BoardWidth), 15);
		glVertex3i(int( + TableLength + BoardWidth + BrownBoardWidth), int( + TableWidth + BoardWidth + BrownBoardWidth), 15);
		glVertex3i(int( + TableLength + BoardWidth + BrownBoardWidth), int( - TableWidth - BoardWidth - BrownBoardWidth), 15);
		
		//pockets
		glColor3f(0,0,0);
		glVertex3i(int(-Pocket/2), int(-TableWidth), int(15));
		glVertex3i(int(Pocket/2), int(-TableWidth), int(15));
		glVertex3i(int(Pocket/2), int(-TableWidth - BoardWidth), int(15));
		glVertex3i(int(-Pocket/2), int(-TableWidth - BoardWidth), int(15));
		//pockets
		glVertex3i(int(-Pocket/2), int(TableWidth), int(15));
		glVertex3i(int(Pocket/2), int(TableWidth), int(15));
		glVertex3i(int(Pocket/2), int(TableWidth + BoardWidth), int(15));
		glVertex3i(int(-Pocket/2), int(TableWidth + BoardWidth), int(15));
	glEnd();
}

void v3f(vector3f v)
{
	glVertex3f(v.x, v.y, v.z);
}

void Coords(vector3f Coord[360/BALL_ACCURACY + 1][180/BALL_ACCURACY + 1])
{
	int i, j;
	for (i = 0; i <= 360/BALL_ACCURACY; i ++) {
		for (j = 0; j < 180/BALL_ACCURACY; j ++) {
			Coord[i][j].z = BallRadius * (-cos((float(j)*BALL_ACCURACY/180) * PI));
			Coord[i][j].x = BallRadius * cos((float(i)*BALL_ACCURACY/180) * PI) * sin((float(j)*BALL_ACCURACY/180) * PI);
			Coord[i][j].y = BallRadius * sin((float(i)*BALL_ACCURACY/180) * PI) * sin((float(j)*BALL_ACCURACY/180) * PI);
		}
	}
}

void PrintBalls (Ball B)
{
	int i, j;
	glBegin(GL_QUAD_STRIP);
	glColor3f(1.0, 1.0, 1.0);
	for (i = 0; i < 360/BALL_ACCURACY; i++){	
		for (j = 0; j < 180/BALL_ACCURACY + 1; j++){
			glColor3f((float(j)*BALL_ACCURACY/180), (float(j)*BALL_ACCURACY/180), (float(j)*BALL_ACCURACY/180));
			v3f(B.position + BallCoords[i][j]);
			v3f(B.position + BallCoords[i+1][j]);
		}
	}
	glEnd();
}

void PrintCurrentBall (Ball B)
{
	int i, j;
	glBegin(GL_QUAD_STRIP);
	glColor3f(1.0, 0.75, 0.75);
	for (i = 0; i < 360/BALL_ACCURACY; i++){	
		for (j = 0; j < 180/BALL_ACCURACY + 1; j++){
			glColor3f((float(j)*BALL_ACCURACY/180), (float(j)*BALL_ACCURACY/270), (float(j)*BALL_ACCURACY/270));
			v3f(B.position + BallCoords[i][j]);
			v3f(B.position + BallCoords[i+1][j]);
		}
	}
	glEnd();
}

void AnyPocket (Ball B[16]) {
	int i;
	for (i = 0; i < 15; i++) {
		if (B[i].pocket()) {
			B[i].avilable = false;
		}
	}
}

void MotionCick(Ball *B1, Ball *B2) {
	vector3f b1, b2;
	float mod1, mod2;
	mod1 = (B1->speed).vModulo();
	mod2 = (B2->speed).vModulo();
	b1 = (B1->position - B2->position).vUnit() * mod2 * (B1->position - B2->position).vAngleCos(B2->speed) + B1->speed - (B2->position - B1->position).vUnit() * mod1 * (B2->position - B1->position).vAngleCos(B1->speed);
	b2 = (B2->position - B1->position).vUnit() * mod1 * (B2->position - B1->position).vAngleCos(B1->speed) + B2->speed - (B1->position - B2->position).vUnit() * mod2 * (B1->position - B2->position).vAngleCos(B2->speed);
	B1->speed = b1;
	B2->speed = b2;
}

void AnyCick(Ball B[16]) {
	int i, j;
	for (i = 0; i < 16; i++) {
		if (B[i].avilable){
			for (j = 0; j < 16; j++) {
				if (B[j].avilable){
					if ((B[i]).cick(B[j])) {
						MotionCick(&B[i], &B[j]);
					}
				}
			}
		}
	}
	for (i = 0; i < 16; i++) {
		if (B[i].avilable){
			for (j = 0; j < 16; j++) {
				if (B[j].avilable){
					if ((B[i]).cick(B[j])) {
						MotionCick(&B[i], &B[j]);
					}
				}
			}
		}
	}
}

Ball MotionBoard(Ball B) {
	Ball B1;
	if (B.position.x + B.dr().x > TableLength - BallRadius){
		B1.position = B.position + B.dr() - vector3f(2*(B.position.x + B.dr().x - TableLength + BallRadius), 0 , 0);
		B1.speed.x = -0.8 * B.speed.x;
		B1.speed.y = B.speed.y / (abs(B.speed.x)/10 + 1);
	}
	if (B.position.x + B.dr().x < - TableLength + BallRadius){
		B1.position = B.position + B.dr() - vector3f(2*(B.position.x + B.dr().x + TableLength - BallRadius), 0 , 0);
		B1.speed.x = -0.8 * B.speed.x;
		B1.speed.y = B.speed.y / (abs(B.speed.x)/20 + 1);
	}
	if (B.position.y + B.dr().y > TableWidth - BallRadius){
		B1.position = B.position + B.dr() - vector3f(0, 2*(B.position.y + B.dr().y - TableWidth + BallRadius), 0);
		B1.speed.y = -0.8 * B.speed.y;
		B1.speed.x = B.speed.x / (abs(B.speed.y)/10 + 1);
	}
	if (B.position.y + B.dr().y < - TableWidth + BallRadius){
		B1.position = B.position + B.dr() - vector3f(0, 2*(B.position.y + B.dr().y + TableWidth - BallRadius), 0);
		B1.speed.y = -0.8 * B.speed.y;
		B1.speed.x = B.speed.x / (abs(B.speed.y)/20 + 1);
	}
	return B1;
}

void AnyBoard(Ball B[16]) {
	int i;
	for (i = 0; i < 16; i++) {
		if (B[i].avilable) {
			if ((B[i]).board()) {
				B[i] = MotionBoard(B[i]);
			}
			else {
				B[i].position = B[i].position + (B[i]).dr();
				B[i].speed = B[i].speed + (B[i]).dv();
				B[i].spin = B[i].spin + (B[i]).ds();
			}
		}
	}
}

void motion (Ball B[16])
{
	Ball b1;

	AnyPocket(B);
	
	AnyCick(B);

	AnyBoard(B);
}

void Display()
{
	//========================================//
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -1000.0); // отодвинуться от сцены
	glRotatef(latitude, 1.0, 0.0, 0.0); // повернуть камеру по широте
	glRotatef(longitude, 0.0, 0.0, 1.0); // повернуть камеру по долготе
//		gluLookAt(lx, ly, lz, 0,0,0, 0,1,0);
	glScalef(scale, scale, scale);

	Table();
	glTranslatef(0.0, 0.0, -BallRadius); //сдвинуть шары над столом
	//========================================//
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	Table();
	for (int i = 0; i < 16; i++)
		if (Bal[i].avilable) {
			if (i != CurrentBall) {
//					PrintBalls(Bal[i]);
					glColor3f(1.0, 1.0, 1.0);
					glPushMatrix();
					glTranslated(Bal[i].position.x, Bal[i].position.y, Bal[i].position.z);
					glutSolidSphere(BallRadius,50,50);
					glPopMatrix();
				}
			else {
//				PrintCurrentBall(Bal[i]);
				glColor3f (1.0, 0.7, 0.7);
				glPushMatrix();
				glTranslated(Bal[i].position.x, Bal[i].position.y, Bal[i].position.z);
				glutSolidSphere(BallRadius,50,50);
				glPopMatrix();
			}
		}
//	glutSolidSphere(BallRadius,40,16);
	glFlush();
	glutSwapBuffers();
}

void Timer(int)
{
	motion(Bal);
	glutPostRedisplay();
	glutTimerFunc(SPSU, Timer, 0);
}

//========================================//
void PassiveMotion(int x, int y)
{
	looking = false;
}

void mouse(int button, int state, int x, int y)
{
  switch (button) {
    case GLUT_LEFT_BUTTON:
        break;
    case GLUT_RIGHT_BUTTON:
        looking = true;
		px = x;
		py = y;
        break;
      }
}

void ActiveMotion(int x, int y)
{
//	vector3f vvv;
//	vvv = Bal[1].position;
	cue = (vector3f(WindowWidth/2, WindowHeight/2, 0) - vector3f(x, y, 0));
	cue.x *= -1;
	/*glBegin(GL_LINES);
	glColor3f(1,1,1);
	glVertex3i( int(Bal[CurrentBall].position.x), int(Bal[CurrentBall].position.x + cue.y), 1);
	glVertex3i( int(Bal[CurrentBall].position.y), int(Bal[CurrentBall].position.y + cue.y), 1);
	glEnd();*/
	cue = (cue)/-25;
//	cue = vector3f(5, 0.3, 0);

	if( looking )
	{
		if( px && x>px ){
			longitude = longitude + float(x-px)/7.0; // чем быстрее двигаем мышкой тем угол поворота больше
//			if ( longitude < -180.0 ) longitude = -180.0;
		}
		if( px && x<px ){
			longitude = longitude - float(px-x)/7.0;
//			if ( longitude > 180.0 ) longitude = 180.0;
		}
		if( py && y<py ){
			latitude = latitude - float(py-y)/3.0;
//			if ( latitude > 90.0 ) latitude = 90.0;
		}
		if( py && y>py ){
			latitude = latitude + float(y-py)/3.0;
//			if ( latitude < 0.0 ) latitude = 0.0;
		}
		px=x; py=y;
	}

}
//========================================//

void Keybord(unsigned char key, int x, int y)
{
	switch(key) 
	{
		/*case 'd': 
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
			Bal[1].speed = vector3f(6, 0.4, 0);
			break;
		case '4': 
			Bal[1].speed = cue;
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
		case 32:
			Bal[CurrentBall].speed = cue;
			break;
		case 9:
			CurrentBall = (CurrentBall + 1) % 15;
			break;
		case 'v': {
			Bal[0].spin = vector3f(-40, 0, 0);
			Bal[0].speed = vector3f(15, 0, 0);
			}
			break;
		default:
			break;*/
		case '1':
			scale *= 0.9;
//			glScalef(0.8,0.8,0.8);
			break;
		case '2':
			scale *= 1.1;
//			glScalef(1.25,1.25,1.25);
			break;
		case '3':
			Bal[1].speed = vector3f(6, 0.4, 0);
			break;
		case '4': 
			Bal[1].speed = cue;
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
		case 32:
			Bal[CurrentBall].speed = cue;
			break;
		case 9:
			CurrentBall = (CurrentBall + 1) % 16;
			break;
		case 'v':
			latitude = longitude = 0;
			break;
		case 'c': {
			Bal[0].spin = vector3f(-40, 0, 0);
			Bal[0].speed = vector3f(10, 10, 0);
			}
			break;
		default:
			break;
	}
}

int main(int argc, char ** argv)
{
	int i, j;
	Coords(BallCoords);

	Bal[0].speed = vector3f(0, 0, 0);
	Bal[0].position = vector3f(-TableLength/2, 0, BallRadius);
	Bal[0].spin = vector3f(0, 0, 0);
	Bal[0].avilable = true;
	int num = 1;
	for (i = 0; i < 5; i++) {
		for (j = 0; j < i + 1; j++) {
			Bal[num].position.x = TableLength/2 + i * BallRadius * THREE;
			Bal[num].position.y = 2 * BallRadius * j - BallRadius * i;
			Bal[num].position.z = BallRadius;
			Bal[num].speed = vector3f(0, 0, 0);
			Bal[num].spin = vector3f(0, 0, 0);
			Bal[num].avilable = true;
			num++;
		}
	}

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
	glEnable(GL_DEPTH_TEST);
	glutInitWindowSize(WindowWidth, WindowHeight);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Proccesing");
	init();
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keybord);
	//========================================//
	glutMotionFunc(ActiveMotion);
	glutPassiveMotionFunc(PassiveMotion);
	glutMouseFunc(mouse);
//========================================//
	glutTimerFunc(SPSU, Timer, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
//	gluPerspective(50, WindowWidth/WindowHeight, 1, 20000);
//	glOrtho(-WindowWidth/2,WindowWidth/2,-WindowHeight/2,WindowHeight/2,-5000,5000);
	gluPerspective ( 40 , float(WindowWidth)/float(WindowHeight), 5 , 5000);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glutMainLoop();
	return 0;
}



