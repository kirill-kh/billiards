#include "stdafx.h"
#include <stdlib.h>
#include <Windows.h>
#include <math.h>
#include <time.h>
#include <GL\glut.h>
#include <conio.h>
#include <iostream>
#include "constant.h"
#include "vector3f.h"
#include "Ball.h"
using namespace std;

int WindowHeight = 680;
int WindowWidth  = 1350;
int TableLength = TABLE_LENGTH / mM_PER_PIXEL;
int TableWidth = TABLE_WIDTH / mM_PER_PIXEL;
int BrownBoardWidth = BROWN_BOARD_WIDTH / mM_PER_PIXEL;
float BallRadius = float(BALL_RADIUS) / float(mM_PER_PIXEL);
float g = (float(G * SPSU * SPSU)) / (float(mM_PER_PIXEL * 1000000));
float Pocket = POCKET / mM_PER_PIXEL;
int BoardWidth = Pocket / 1.4142;
Ball Bal[16];
int CurrentBall;
float latitude = 0.0;
float longitude = 0.0;
bool looking = false;
float scale = 1.0;
int px = 0;
int py = 0;
vector3f tmpPosition;
vector3f cuePosition = vector3f(0.0, 0.0, 0.0);
float force = 0;
bool cueCick;

GLfloat mat_specular0[]={1.0,1.0,1.0,1.0}; // шар
GLfloat mat_ambient0 []={0.2,0.2,0.2,1.0};
GLfloat mat_specular00[]={1.0,0.7,0.7,1.0};// текущий шар
GLfloat mat_ambient00 []={0.3,0.1,0.1,1.0};


void Table()
{

   GLfloat mat_specular1[]={0.0, 0.6, 0.35, 1.0}; // стол
   GLfloat mat_ambient1[] ={0.0, 0.5, 0.25, 1.0};
   GLfloat mat_specular2[]={0.0, 0.7, 0.4, 1.0}; // стол яркий градиент
   GLfloat mat_ambient2[] ={0.0, 0.45, 0.25, 1.0};
   GLfloat mat_specular3[]={0.0, 0.5, 0.3, 1.0};// стол темный градиент
   GLfloat mat_ambient3[] ={0.0, 0.4, 0.2, 1.0};
   GLfloat mat_specular4[]={0.3, 0.2, 0.05, 1.0};// борт
   GLfloat mat_ambient4[] ={0.3, 0.2, 0.05, 1.0};
   GLfloat mat_specular5[]={0.0, 0.0, 0.0, 1.0}; // луза
   GLfloat mat_ambient5[] ={0.0, 0.0, 0.0, 1.0};
   GLfloat mat_specular6[]={0.0, 0.1, 0.0, 1.0};// стол темный градиент
   GLfloat mat_ambient6[] ={0.0, 0.3, 0.05, 1.0};


   glBegin(GL_QUADS);
		glColor3f(0.0, 0.65, 0.4);
                glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,mat_specular1);
                glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_ambient1);
		glVertex3i(int( + TableLength + 6), int( - TableWidth - 6), 0);
		glVertex3i(int( + TableLength + 6), int( + TableWidth + 6), 0);
		glVertex3i(int( - TableLength - 6), int( + TableWidth + 6), 0);
		glVertex3i(int( - TableLength - 6), int( - TableWidth - 6), 0);

		//board

		glColor3f(0.0, 0.8, 0.5);
                glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,mat_specular2);  //2
                glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_ambient2);
		glVertex3i(int( - TableLength + BoardWidth), int( + TableWidth), 12);
		glVertex3i(int( + TableLength - BoardWidth), int( + TableWidth), 12);
		glColor3f(0.0, 0.6, 0.35);
                glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,mat_specular3); //3
                glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_ambient3);
		glVertex3i(int( + TableLength), int( + TableWidth + BoardWidth), 15);
		glVertex3i(int( - TableLength), int( + TableWidth + BoardWidth), 15);

		//-------------------------------------
		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,mat_specular6);  //6
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_ambient6);
		glVertex3i(int( - TableLength + BoardWidth), int( + TableWidth), 12);
		glVertex3i(int( + TableLength - BoardWidth), int( + TableWidth), 12);
		glVertex3i(int( + TableLength - BoardWidth), int( + TableWidth + 6), 0);
		glVertex3i(int( - TableLength + BoardWidth), int( + TableWidth + 6), 0);
		//-------------------------------------
		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,mat_specular6);  //6
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_ambient6);
		//-------------------------------------
		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,mat_specular6);  //6
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_ambient6);
		glVertex3i(int( + TableLength - BoardWidth), int( - TableWidth), 12);
		glVertex3i(int( - TableLength + BoardWidth), int( - TableWidth), 12);
		glVertex3i(int( - TableLength + BoardWidth), int( - TableWidth - 6), 0);
		glVertex3i(int( + TableLength - BoardWidth), int( - TableWidth - 6), 0);
		//-------------------------------------

		glColor3f(0.3, 0.2, 0.05);
                glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,mat_specular4);
                glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_ambient4);
		glVertex3i(int( - TableLength - BoardWidth), int( + TableWidth + BoardWidth), 15);
		glVertex3i(int( + TableLength + BoardWidth), int( + TableWidth + BoardWidth), 15);
		glVertex3i(int( + TableLength + BoardWidth + BrownBoardWidth), int( + TableWidth + BoardWidth + BrownBoardWidth), 15);
		glVertex3i(int( - TableLength - BoardWidth - BrownBoardWidth), int( + TableWidth + BoardWidth + BrownBoardWidth), 15);

		glColor3f(0.0, 0.8, 0.5);
                glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,mat_specular2);  //2
                glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_ambient2);
		glVertex3i(int( - TableLength), int( - TableWidth - BoardWidth), 15);
		glVertex3i(int( + TableLength), int( - TableWidth - BoardWidth), 15);
		glColor3f(0.0, 0.6, 0.35);
                glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,mat_specular3);    //3
                glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_ambient3);
		glVertex3i(int( + TableLength - BoardWidth), int( - TableWidth), 12);
		glVertex3i(int( - TableLength + BoardWidth), int( - TableWidth), 12);

		//------------------------------------------
		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,mat_specular6);  //6
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_ambient6);
		glVertex3i(int( + TableLength), int( + TableWidth - BoardWidth), 12);
		glVertex3i(int( + TableLength), int( - TableWidth + BoardWidth), 12);
		glVertex3i(int( + TableLength + 6), int( - TableWidth + BoardWidth), 0);
		glVertex3i(int( + TableLength + 6), int( + TableWidth  - BoardWidth), 0);
		
		glVertex3i(int( - TableLength), int( - TableWidth  + BoardWidth), 12);
		glVertex3i(int( - TableLength), int( + TableWidth  - BoardWidth), 12);
		glVertex3i(int( - TableLength - 6), int( + TableWidth  - BoardWidth), 0);
		glVertex3i(int( - TableLength - 6), int( - TableWidth  + BoardWidth), 0);
		//------------------------------------------

		glColor3f(0.3, 0.2, 0.05);
                glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,mat_specular4);
                glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_ambient4);
		glVertex3i(int( - TableLength - BoardWidth - BrownBoardWidth), int( - TableWidth - BoardWidth - BrownBoardWidth), 15);
		glVertex3i(int( + TableLength + BoardWidth + BrownBoardWidth), int( - TableWidth - BoardWidth - BrownBoardWidth), 15);
		glVertex3i(int( + TableLength + BoardWidth), int( - TableWidth - BoardWidth), 15);
		glVertex3i(int( - TableLength - BoardWidth), int( - TableWidth - BoardWidth), 15);

		glColor3f(0.0, 0.8, 0.5);
                glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,mat_specular2);  //2
                glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_ambient2);
		glVertex3i(int( - TableLength), int( - TableWidth + BoardWidth), 12);
		glVertex3i(int( - TableLength), int( + TableWidth - BoardWidth), 12);
		glColor3f(0.0, 0.6, 0.35);
                glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,mat_specular3);  //3
                glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_ambient3);
		glVertex3i(int( - TableLength - BoardWidth), int( + TableWidth), 15);
		glVertex3i(int( - TableLength - BoardWidth), int( - TableWidth), 15);

		glColor3f(0.3, 0.2, 0.05);
                glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,mat_specular4);
                glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_ambient4);
		glVertex3i(int( - TableLength - BoardWidth), int( - TableWidth - BoardWidth), 15);
		glVertex3i(int( - TableLength - BoardWidth), int( + TableWidth + BoardWidth), 15);
		glVertex3i(int( - TableLength - BoardWidth - BrownBoardWidth), int( + TableWidth + BoardWidth + BrownBoardWidth), 15);
		glVertex3i(int( - TableLength - BoardWidth - BrownBoardWidth), int( - TableWidth - BoardWidth - BrownBoardWidth), 15);

		glColor3f(0.0, 0.8, 0.5);
                glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,mat_specular2);  //2
                glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_ambient2);
		glVertex3i(int( + TableLength + BoardWidth), int( - TableWidth), 15);
		glVertex3i(int( + TableLength + BoardWidth), int( + TableWidth), 15);
		glColor3f(0.0, 0.6, 0.35);
                glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,mat_specular3);  //3
                glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_ambient3);
		glVertex3i(int( + TableLength), int( + TableWidth - BoardWidth), 12);
		glVertex3i(int( + TableLength), int( - TableWidth + BoardWidth), 12);

		glColor3f(0.3, 0.2, 0.05);
                glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,mat_specular4);
                glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_ambient4);
		glVertex3i(int( + TableLength + BoardWidth + BrownBoardWidth), int( - TableWidth - BoardWidth - BrownBoardWidth), 15);
		glVertex3i(int( + TableLength + BoardWidth + BrownBoardWidth), int( + TableWidth + BoardWidth + BrownBoardWidth), 15);
		glVertex3i(int( + TableLength + BoardWidth), int( + TableWidth + BoardWidth), 15);
		glVertex3i(int( + TableLength + BoardWidth), int( - TableWidth - BoardWidth), 15);

		//pockets
		glColor3f(0,0,0);
                glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,mat_specular5);
                glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_ambient5);
		glVertex3i(int(-Pocket/2), int(-TableWidth - BoardWidth), int(16));
		glVertex3i(int(Pocket/2), int(-TableWidth - BoardWidth), int(16));
		glVertex3i(int(Pocket/2), int(-TableWidth), int(12));
		glVertex3i(int(-Pocket/2), int(-TableWidth), int(12));
		//pockets
		glVertex3i(int(-Pocket/2), int(TableWidth), int(12));
		glVertex3i(int(Pocket/2), int(TableWidth), int(12));
		glVertex3i(int(Pocket/2), int(TableWidth + BoardWidth), int(16));
		glVertex3i(int(-Pocket/2), int(TableWidth + BoardWidth), int(16));

		glVertex3i(int(Pocket/2), int(-TableWidth), int(12));
		glVertex3i(int(-Pocket/2), int(-TableWidth), int(12));
		glVertex3i(int(-Pocket/2), int(-TableWidth - 5), int(0));
		glVertex3i(int(+Pocket/2), int(-TableWidth - 5), int(0));

		glVertex3i(int(-Pocket/2), int(TableWidth), int(12));
		glVertex3i(int(+Pocket/2), int(TableWidth), int(12));
		glVertex3i(int(+Pocket/2), int(TableWidth + 5), int(0));
		glVertex3i(int(-Pocket/2), int(TableWidth + 5), int(0));

		glVertex3i(int( TableLength + 6), int( + TableWidth - BoardWidth + 6), 0);
		glVertex3i(int( TableLength - BoardWidth), int( + TableWidth  +6), 0);
		glVertex3i(int( TableLength + 6), int( + TableWidth  + 6), 1);
		glVertex3i(int( TableLength + 6), int( + TableWidth  + 6), 1);

		glVertex3i(int( -TableLength - 6), int( - TableWidth + BoardWidth - 6), 0);
		glVertex3i(int( -TableLength + BoardWidth), int( - TableWidth  -6), 0);
		glVertex3i(int( -TableLength - 6), int( - TableWidth  - 6), 1);
		glVertex3i(int( -TableLength - 6), int( - TableWidth  - 6), 1);

		glVertex3i(int( -TableLength - 6), int( + TableWidth - BoardWidth + 6), 0);
		glVertex3i(int( -TableLength + BoardWidth), int( + TableWidth  +6), 0);
		glVertex3i(int( -TableLength - 6), int( + TableWidth  + 6), 1);
		glVertex3i(int( -TableLength - 6), int( + TableWidth  + 6), 1);

		glVertex3i(int( TableLength + 6), int( - TableWidth + BoardWidth - 6), 0);
		glVertex3i(int( TableLength - BoardWidth), int( - TableWidth  -6), 0);
		glVertex3i(int( TableLength + 6), int( - TableWidth  - 6), 1);
		glVertex3i(int( TableLength + 6), int( - TableWidth  - 6), 1);

	glEnd();
}

void v3f(vector3f v)
{
	glVertex3f(v.x, v.y, v.z);
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
		B1.spin.x *= -1;
	}
	if (B.position.x + B.dr().x < - TableLength + BallRadius){
		B1.position = B.position + B.dr() - vector3f(2*(B.position.x + B.dr().x + TableLength - BallRadius), 0 , 0);
		B1.speed.x = -0.8 * B.speed.x;
		B1.speed.y = B.speed.y / (abs(B.speed.x)/20 + 1);
		B1.spin.y *= -1;
	}
	if (B.position.y + B.dr().y > TableWidth - BallRadius){
		B1.position = B.position + B.dr() - vector3f(0, 2*(B.position.y + B.dr().y - TableWidth + BallRadius), 0);
		B1.speed.y = -0.8 * B.speed.y;
		B1.speed.x = B.speed.x / (abs(B.speed.y)/10 + 1);
		B1.spin.y *= -1;
	}
	if (B.position.y + B.dr().y < - TableWidth + BallRadius){
		B1.position = B.position + B.dr() - vector3f(0, 2*(B.position.y + B.dr().y + TableWidth - BallRadius), 0);
		B1.speed.y = -0.8 * B.speed.y;
		B1.speed.x = B.speed.x / (abs(B.speed.y)/20 + 1);
		B1.spin.y *= -1;
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

bool ZeroSpeed (void) {
	bool tmp;
	int i;
	tmp = true;
	for (i=0; i<16; i++)
		if (Bal[i].avilable)
			if ((Bal[i].speed.x != 0.0) || (Bal[i].speed.y != 0.0) || (Bal[i].speed.x != 0.0))
				tmp = false;
	return tmp;
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

//	Table();
	//========================================//
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glTranslatef(0.0, 0.0, -BallRadius); //сдвинуть шары над столом
//    glEnable(GL_NORMALIZE);
	if (ZeroSpeed()) {
	glPushMatrix();
	glTranslated(-Bal[CurrentBall].position.x, -Bal[CurrentBall].position.y, -Bal[CurrentBall].position.z);
	Table();
	glPopMatrix();
	glPushMatrix();
	glTranslated(-Bal[CurrentBall].position.x, -Bal[CurrentBall].position.y, -Bal[CurrentBall].position.z);
	for (int i = 0; i < 16; i++)
		if (Bal[i].avilable) {
			if (i != CurrentBall) {
                                        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,mat_specular0);
                                        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_ambient0);
					glColor3f(1.0, 1.0, 1.0);
					glPushMatrix();
					glTranslated(Bal[i].position.x, Bal[i].position.y, Bal[i].position.z);
					glutSolidSphere(BallRadius,50,50);
					glPopMatrix();
				}
			else {
				glColor3f (1.0, 0.7, 0.7);
                                glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,mat_specular00);
                                glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_ambient00);
				glPushMatrix();
				glTranslated(Bal[i].position.x, Bal[i].position.y, Bal[i].position.z);
				glutSolidSphere(BallRadius,50,50);
				glPopMatrix();
			}
		}
	glPopMatrix();
	}
	else {
		glPushMatrix();
	glTranslated(-tmpPosition.x, -tmpPosition.y, -tmpPosition.z);
	Table();
	glPopMatrix();
	glPushMatrix();
	glTranslated(-tmpPosition.x, -tmpPosition.y, -tmpPosition.z);
	for (int i = 0; i < 16; i++)
		if (Bal[i].avilable) {
			if (i != CurrentBall) {
                                        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,mat_specular0);
                                        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_ambient0);
					glColor3f(1.0, 1.0, 1.0);
					glPushMatrix();
					glTranslated(Bal[i].position.x, Bal[i].position.y, Bal[i].position.z);
					glutSolidSphere(BallRadius,50,50);
					glPopMatrix();
				}
			else {
				glColor3f (1.0, 0.7, 0.7);
                                glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,mat_specular00);
                                glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_ambient00);
				glPushMatrix();
				glTranslated(Bal[i].position.x, Bal[i].position.y, Bal[i].position.z);
				glutSolidSphere(BallRadius,50,50);
				glPopMatrix();
			}
		}
	glPopMatrix();
	}
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
		case '1':
			scale *= 0.9;
			break;
		case '2':
			scale *= 1.1;
			break;
		case '3':
			Bal[1].speed = vector3f(6, 0.4, 0);
			break;
		case 'k':
			if ((cuePosition.vModulo() < 0.9) || (cuePosition.y > 0))
				cuePosition.y -= 0.01;
			break;
		case 'i':
			if ((cuePosition.vModulo() < 0.9) || (cuePosition.y < 0))
				cuePosition.y += 0.01;
			break;
		case 'l':
			if ((cuePosition.vModulo() < 0.9) || (cuePosition.x < 0))
				cuePosition.y += 0.01;
			break;
		case 'j':
			if ((cuePosition.vModulo() < 0.9) || (cuePosition.x > 0))
				cuePosition.y -= 0.01;
			break;
		case 32:
			Bal[CurrentBall].speed = vector3f(sin(longitude*PI/180.0), cos(longitude*PI/180.0), 0.0) * force;
			tmpPosition = Bal[CurrentBall].position;
			force = 0;
			break;
		case 9:
			CurrentBall = (CurrentBall + 1) % 16;
			break;
		case 'v': 
			{
			latitude = longitude = 0;
			tmpPosition = vector3f(0.0, 0.0, 0.0);
			}
			break;
		case 'c': {
			Bal[0].spin = vector3f(-40, 0, 0);
			Bal[0].speed = vector3f(10, 10, 0);
			}
		case 'z': {
			if (force < 40)
				force += 1.0;
			}
			break;
		case 'x': {
			force = 0.0;
			}
			break;
		case 'p': {
				Bal[0].speed = vector3f(0, 0, 0);
				Bal[0].position = vector3f(-TableLength/2, 0, BallRadius);
				Bal[0].spin = vector3f(0, 0, 0);
				Bal[0].avilable = true;
				int num = 1;
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < i + 1; j++) {
						Bal[num].position.x = TableLength/2 + i * BallRadius * THREE;
						Bal[num].position.y = 2 * BallRadius * j - BallRadius * i;
						Bal[num].position.z = BallRadius;
						Bal[num].speed = vector3f(0, 0, 0);
						Bal[num].spin = vector3f(0, 0, 0);
						Bal[num].avilable = true;
						num++;
					}
				}
			}
			break;
		default:
			break;
	}
}

void init(void)
{
   GLfloat mat_shininess[]={50.0,0.0};
   GLfloat light_position[]={0.0,0.0,-600.0,1.0};
   GLfloat white_light[]={1.0,1.0,1.0,1.0};

   glClearColor(0.0,0.0,0.0,0.0);
   glShadeModel(GL_SMOOTH);

   GLfloat lmodel_ambient[]={1.0,1.0,1.0,1.0};
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT,lmodel_ambient);
   glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

   glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,mat_shininess);
   glLightfv(GL_LIGHT0,GL_POSITION,light_position);
   glLightfv(GL_LIGHT0,GL_DIFFUSE,white_light);
   glLightfv(GL_LIGHT0,GL_SPECULAR,white_light);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_NORMALIZE);
}

int main(int argc, char ** argv)
{
	int i, j;

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
	gluPerspective ( 40 , float(WindowWidth)/float(WindowHeight), 5 , 5000);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glutMainLoop();
	return 0;
}
