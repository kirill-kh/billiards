#pragma once
class vector3f
{
public:
	vector3f(void);
	vector3f(float x1, float y1, float z1);
	~vector3f(void);
	float x;
	float y;
	float z;
	vector3f operator * (float c);
	vector3f operator /  (float c);
	float vModulo(void);
	vector3f vUnit (void);
	vector3f operator + (vector3f &other);
	vector3f operator - (vector3f &other);
	float vAngleCos(vector3f &other);
};

