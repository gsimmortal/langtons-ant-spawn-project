#pragma once
#include <vector>


using namespace std;


//structs for grid interface (condensed grids)
struct XY
{
	int x;
	int y;
};
struct GridS
{
	float id;
	int x;
	int y;
	bool s;
};
struct CGrid
{
	vector<GridS> gridSquare;
};

//structs for ant interface
struct RGB {
	float r = 0.0f;
	float g = 0.0f;
	float b = 0.0f;
};

//structs for grid class
struct NeighbourWeight {
	float square;
	int weight;
	int direction;
};
struct Neighbours {
	float westID = 0.1;
	float northID = 0.1;
	float southID = 0.1;
	float eastID = 0.1;
};
struct XYSWN {
	float x;
	float y;
	float s;
	int w;
	bool visited = false;
	vector <Neighbours> neighbourContainer = vector<Neighbours>(2);
};

//structs for ant class
struct XYC {
	float x;
	float y;
	vector <RGB> c = vector<RGB>(1);
	int colourType;
};
struct RT {
	int colour;
	int direction;
};
