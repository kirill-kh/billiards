#include "stdafx.h"
#include "Ball.h"
#include "vector3f.h"
#include "constant.h"
#include <math.h>

float b_g = (float(G * SPSU * SPSU)) / (float(mM_PER_PIXEL * 1000000));
int b_TableLength = TABLE_LENGTH / mM_PER_PIXEL;
int b_TableWidth = TABLE_WIDTH / mM_PER_PIXEL;
float b_BallRadius = float(BALL_RADIUS) / float(mM_PER_PIXEL);
float b_Pocket = POCKET / mM_PER_PIXEL;
float MaxPocketX = b_TableLength - b_BallRadius - (b_Pocket - b_BallRadius)/1.4142;
float MaxPocketY = b_TableWidth - b_BallRadius - (b_Pocket - b_BallRadius)/1.4142;

Ball::Ball(void)
	: position(vector3f(0,0,0)), speed(vector3f(0,0,0)), spin(vector3f(0,0,0)), avilable(true)
{
}

Ball::Ball(vector3f position1, vector3f speed1, vector3f spin1, bool avilable1)
	: position(position1), speed(speed1), spin(spin1), avilable(avilable1)
{
}


Ball::~Ball(void)
{
}


vector3f Ball::dr(void)
{
	return (*this).speed + ((*this).speed.vUnit() * (-f*b_g/2));
}


vector3f Ball::dv(void)
{
	if ((*this).speed.vModulo() < 0.05)
		return (*this).speed * (-1);
	return (*this).speed.vUnit() * (-f*b_g) + ((*this).speed - (*this).spin) * (-fspin) * BALL_ENERGY;
}

vector3f Ball::ds(void)
{
	return ((*this).speed - (*this).spin) * (fspin);
}


bool Ball::board(void)
{
	return ((abs((*this).position.x + (*this).dr().x) > b_TableLength - b_BallRadius) || (abs((*this).position.y + (*this).dr().y) > b_TableWidth - b_BallRadius));;
}


bool Ball::cick(Ball &other)
{
	return (((*this).position + (*this).dr() - other.position - other.dr()).vModulo() < 2 * b_BallRadius);
}

bool Ball::pocket(void)
{
	return ((abs((*this).position.x + (*this).dr().x) > MaxPocketX) && (abs((*this).position.y + (*this).dr().y) > MaxPocketY)) || ((abs((*this).position.y + (*this).dr().y) > b_TableWidth - b_BallRadius/2)&&(abs((*this).position.x + (*this).dr().x) < (b_Pocket - b_BallRadius/2)));
}
