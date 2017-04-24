#pragma once
#include <glew\glew.h>
#include <freeglut\freeglut.h>
#include <CoreStructures\CoreStructures.h>

class Sun {

	float sunAngle;
	float sunX;
	float sunY;
	float sunScale;
	float sunEnergy;
	int sunCol;

public:

	//default constructor
	Sun();

	//getters
	int getCol(void);
	float getX(void);
	float getY(void);
	float getAngle(void);
	float getScale(void);

	//setters
	void initialise(float x, float y, float scale, int colour, float energy);
	void moveX(float locX);
	void moveY(float locY);
	void updateAngle(void);
	void setX(float x);
	void setY(float y);

};