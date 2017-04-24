#pragma once
#include "GridInterface.h"

using namespace std;
using namespace CoreStructures;

//======================================================================
//		STRUCTS HAVE BEEN MOVED TO GStructs.h HEADER FILE
//======================================================================

class Grids{

private:
	//neighbour sorting variables
	const int maxIndex = 3, maxNeighbours = maxIndex + 1;
	const float epsilon = 0.001;											//float error range
	vector <NeighbourWeight> heldSquares = vector <NeighbourWeight>(4);		//brings togethor neighbour id and weight in one place
	vector <NeighbourWeight> tmpNeighbour = vector <NeighbourWeight>(1);	//holds tmp neighbour while sorting

	//variables needed for grid and maze construction
	float gridScale;
	vector<XYSWN> squareHolderXYSWN;
	stack<int> mazingStack; //holds ID of held square/'s
	

	//private calculation functions
	void reDo(void);
	void neighbourSorting(void);//returns original direction of 'lightest' cell

public:

	//default constructor
	Grids();
	//getters
	float gridGetX(float square);
	float gridGetY(float square);
	float gridGetS(float square);
	float gridGetScale(void);

	//setters
	void gridSetScale(float scale);
	void gridSetS(float square, float solidity);
	//void gridSetW(float square, int weighting);//may be needed in future to influence maze structure

	//do-ers
	void callNeighbours(float square);
	void gridMazify(void);	
};