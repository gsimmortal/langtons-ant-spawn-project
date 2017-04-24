#pragma once
#include <glew\glew.h>
#include <freeglut\freeglut.h>
#include <CoreStructures\CoreStructures.h>
#include <vector>
#include <math.h>
#include <random>
#include <stack>

#include "GStructs.h"

#include "MakeGrid.h"
#include "Ant.h"
#include "stdafx.h"

using namespace std;
using namespace CoreStructures;

class Grids;
class Ants;

//======================================================================
//		STRUCTS HAVE BEEN MOVED TO GStructs.h HEADER FILE
//======================================================================


class GridInterface
{
private: // Grid holders here as well as important variables we dont want the end user to have direct access too:

	//array for holding grid thats being generated
	vector<Grids> tmpGrid = vector<Grids>(1);
	//vector for holding condensed grids (grid with unneccesaries removed (weighting etc))
	vector<CGrid> condensedGrid = vector<CGrid>(1);
	//vector for holding LA's
	vector<Ants> antVector = vector<Ants>(1);
	
	//validation check and general variables
	bool initialGeneration = false;
	int gridScale = 25;
	int updateEvery = 100;
	int currentCount = 0;



	//private calculation functions
	//move grid to condensed grid function
	void condense(float maze);

public: // functions and overloaded functions we want the user to have access too:

	// ==== CONSTRUCTORS ====
	//constructor
	GridInterface();

	// ==== GENERATORS ====
	//generate general maze square (25*25)						==== 
	void generate(void);
	void generate(float scale);
	//redo grid													==== 
	//void reGenerate(void);									-	combined with generate()
	//void reGenerate(float scale);								-	combined with generate(scale)
	//redo LA													==== 
	void resetLA(void);
	void resetLA(int maze);
	//generate new LA ruleset									==== 
	void newRuleset(void);

	// ==== DEBUG CALLOUTS ====
	//callout for maze data input maze/input maze and square	==== 
	void heldData(int maze);
	void heldData(int maze, float square);
	//callout for LA rules										==== 
	void getRuleset(void);

	// ==== GETTERS ====
	//access maze solidity at square entity no					====
	bool getSolid(float square);
	//access maze solidity at maze no. entity no.				====
	bool getSolid(float maze, float square);

	bool getInitialized(void);

	XY getXY(float square);
	//access la colour at square entity no						====
	RGB getLAC(float square);

	//access scale of grid
	float getScale(void);

	/*
	//access la colour at maze no. entity no.					====
	vector<RGB> getLAC(float maze, float square);
	*/

	// ==== SETTERS ====
	void setTickSpeed(int speed);

	// ==== UPDATE FUNCTION ====
	void update(void);

};