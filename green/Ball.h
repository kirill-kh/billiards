#pragma once
#include "vector3f.h"
#include "constant.h"
class Ball
{
public:
	Ball(void);
	Ball(vector3f position1, vector3f speed1, vector3f spin1, bool avilable1);
	~Ball(void);
	vector3f position;
	vector3f speed;
	vector3f spin;
	vector3f dr(void);
	vector3f dv(void);
	vector3f ds(void);
	bool board(void);
	bool cick(Ball &other);
	bool pocket(void);
	Ball MotionCick(Ball &other);
	bool avilable;
};

