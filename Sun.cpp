
#include "stdafx.h"
#include "SunObject.h"


using namespace std;
using namespace CoreStructures;

Sun::Sun()
{

}

//getters
int Sun::getCol(void)
{
	return sunCol;
}
float Sun::getX(void)
{
	return sunX;
}
float Sun::getY()
{
	return sunY;
}
float Sun::getAngle()
{
	return sunAngle;
}
float Sun::getScale()
{
	return sunScale;
}

//setters
void Sun::initialise(float x, float y, float scale, int colour, float energy)
{
	sunX = x;
	sunY = y;
	sunScale = scale;
	sunCol = colour;
	sunEnergy = energy;
}
void Sun::moveX(float locX)
{
	sunX += locX;
}
void Sun::moveY(float locY)
{
	sunY += locY;
}
void Sun::updateAngle(void)
{
	sunAngle += (sunEnergy/2);
	if (sunAngle > 360)sunAngle = 0;
	if (sunAngle < 0)sunAngle = 360 - (sunEnergy/2);
}
void Sun::setX(float x)
{
	sunX = x;
}
void Sun::setY(float y)
{
	sunY = y;
}