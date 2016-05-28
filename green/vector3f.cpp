#include "stdafx.h"
#include "vector3f.h"
#include <math.h>


vector3f::vector3f(void)
	: x(0), y(0), z(0)
{
}

vector3f::vector3f(float x1, float y1, float z1)
	: x(x1), y(y1), z(z1)
{
}

vector3f::~vector3f(void)
{
}

vector3f vector3f::operator *  (float c)
{	
	return vector3f(x * c, y * c, z * c);
}

vector3f vector3f::operator /  (float c)
{	
	return vector3f(x / c, y / c, z / c);
}

float vector3f::vModulo(void)
{
	return sqrt(x*x + y*y + z*z);
}

vector3f vector3f::vUnit (void)
{
	if (vModulo() != 0)
		return *this / vModulo();
	else return vector3f(0, 0, 0);
}



vector3f vector3f::operator + (vector3f &other)
{
	return vector3f(x + other.x, y + other.y, z + other.z);
}

vector3f vector3f::operator - (vector3f &other)
{
	return vector3f(x - other.x, y - other.y, z - other.z);
}

float vector3f::vAngleCos(vector3f &other)
{
	if( ((*this).vModulo()!=0) && (other.vModulo()!=0))
		return ((*this).x*(other.x) + (*this).y*(other.y) + (*this).z*(other.z))/((*this).vModulo()*(other).vModulo());
	else
		return 0;
}
