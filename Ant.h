#pragma once
#include "GridInterface.h"

using namespace std;
using namespace CoreStructures;

//======================================================================
//		STRUCTS HAVE BEEN MOVED TO GStructs.h HEADER FILE
//======================================================================

class Ants {

private:
	//variables needed for grid construction
	float gridScale;
	vector<XYC> squareHolderXYC;

	//Variables needed for ant movement and control
	int direction = 3; //starts facing south
	int currentPosition = 0; //starts at 0 (top left)
	int positionColour = 0; //starts with no colour (assigned at grid generation (redo call))
	
	//rules here (for each colour (6) set a new colour and a turn value)
	const int maxColours = 6,maxDirections = 6;//(R O Y G B P)(N E S W - repeat 2)
	vector<RT> ruleSet = vector<RT>(6);
	vector<int> colourHolder = vector<int>(maxColours);
	vector<int> directionHolder = vector<int>(maxDirections);

	//private calculation functions
	void reDo(void);
	void reColour(void);

public:

	//default constructor
	Ants();
	//getters
	float gridGetX(float square);
	float gridGetY(float square);
	RGB gridGetC(float square);
	float gridGetScale(void);

	//setters
	void gridSetScale(float scale);
	void gridSetC(float square, int colour);

	//do-ers
	void antCrawl(int steps);
	
};