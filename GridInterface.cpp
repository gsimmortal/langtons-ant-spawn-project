
#include "stdafx.h"
#include "GridInterface.h"

//needed functions
/*
 generate general maze (25*25) at origin (X, Y)               ------- Ext. can generate custome sized maze, can generate maze of selected weight pattern, 
 needs to tidy up maze and remove un-needed information such as weighting used in maze generation
 callout general maze data
 **MAYBE** needs to add newly created maze to old maze (no need to store multiple mazes)
 ** F E ** generate new maze tile to n,e,s,w(either or) of current which starts maze generation at given square.


=====SECTION NEEDS RELEVANT VALIDATION CHECKING=====

 needs to be able to toggle drawing of L A grid to see spawns
 
*/

// ==== CONSTRUCTORS ====
GridInterface::GridInterface()
{

}

// ==== GENERATORS ====
void GridInterface::generate(void)
{
	if (!initialGeneration)
	{
	tmpGrid[0].gridSetScale(gridScale);
	tmpGrid[0].gridMazify();
	antVector[0].gridSetScale(gridScale);
	condensedGrid[0].gridSquare = vector<GridS>(gridScale * gridScale);
	initialGeneration = true;
	condense(0);
	}
	else
	{
	cout << "maze already generated, regenerating the maze" << endl;
	int tmpScale = tmpGrid[0].gridGetScale();
	tmpGrid[0].gridSetScale(tmpScale);
	tmpGrid[0].gridMazify();
	antVector[0].gridSetScale(tmpScale);
	condensedGrid[0].gridSquare = vector<GridS>(tmpScale * tmpScale);
	condense(0);
	}
	gridScale = tmpGrid[0].gridGetScale();
}
void GridInterface::generate(float scale)
{
	if (!initialGeneration)
	{
		tmpGrid[0].gridSetScale(scale);
		tmpGrid[0].gridMazify();
		antVector[0].gridSetScale(scale);
		int tmpScale = tmpGrid[0].gridGetScale();
		condensedGrid[0].gridSquare = vector<GridS>(tmpScale * tmpScale);
		condense(0);
		initialGeneration = true;
	}
	else
	{
	cout << "maze already generated, regenerating the maze. Scale: " << scale << endl;
	tmpGrid[0].gridSetScale(scale);
	tmpGrid[0].gridMazify();
	antVector[0].gridSetScale(scale);
	int tmpScale = tmpGrid[0].gridGetScale();
	condensedGrid[0].gridSquare = vector<GridS>(tmpScale * tmpScale);
	condense(0);
	}
	gridScale = tmpGrid[0].gridGetScale();
}

void GridInterface::resetLA(void) //reset langtons ant rules
{
	//callout of langtons ant rules
	//regenerate langtons ant grid
	if (initialGeneration)
	{
		int tmpScale = tmpGrid[0].gridGetScale();
		antVector[0].gridSetScale(tmpScale);
	}
	else cout << "cannot reset LA if one hasnt been generated yet" << endl;
}
void GridInterface::resetLA(int maze)
{
	if (maze >= 0 && maze < antVector.capacity())
	{
		if (initialGeneration)
		{
			int tmpScale = tmpGrid[maze].gridGetScale();
			antVector[maze].gridSetScale(tmpScale);
		}
		else cout << "cannot reset LA if one hasnt been generated yet" << endl;
	}
	else cout << "error: cannot reset LA of maze: " << maze << endl << "Does this maze even exist?" << endl;
}
void GridInterface::newRuleset(void)
{
	//add newruleset function to ant class then call it here using the ant holder vector
}

// ==== DEBUG CALLOUTS ====
void GridInterface::heldData(int maze)
{
	if (maze >= 0 && maze < condensedGrid.capacity())
	{
		cout << "ID: " << maze << " entities: " << condensedGrid[maze].gridSquare.capacity() << endl;


	}
	else cout << "what?????????" << endl;
}
void GridInterface::heldData(int maze, float square)
{

}
void GridInterface::getRuleset(void)
{
	//add ruleset callout to ant class call it here using the ant holder vector
}

// ==== GETTERS ====
bool GridInterface::getSolid(float square)
{
	if (condensedGrid[0].gridSquare[square].s)return true;
	else return false;
}
bool GridInterface::getInitialized(void)
{
	return initialGeneration;
}
RGB GridInterface::getLAC(float square)
{
	return antVector[0].gridGetC(square);
}
XY GridInterface::getXY(float square)
{
	XY tmpXY;
	tmpXY.x = condensedGrid[0].gridSquare[square].x;
	tmpXY.y = condensedGrid[0].gridSquare[square].y;
	return tmpXY;
}
float GridInterface::getScale(void)
{
	return gridScale;
}

// ==== SETTERS ====
void GridInterface::setTickSpeed(int speed) //set stepping speed(fastest 1)
{
	updateEvery = speed;
}

// ==== UPDATE FUNCTIONS ====
void GridInterface::update(void)
{
	currentCount++;
	if (currentCount == updateEvery)
	{
		antVector[0].antCrawl(1); //stepping of langtons ant
		currentCount = 0;
	}
}

// ==== PRIVATE CALCULATIONS ====
void GridInterface::condense(float maze)
{
	int tmpScale = tmpGrid[0].gridGetScale();

	for (int i = 0; i < (tmpScale * tmpScale); i++)
	{
		condensedGrid[maze].gridSquare[i].id = i;
		condensedGrid[maze].gridSquare[i].x = tmpGrid[0].gridGetX(i);
		condensedGrid[maze].gridSquare[i].y = tmpGrid[0].gridGetY(i);
		if (tmpGrid[0].gridGetS(i) >= -0.01 && tmpGrid[0].gridGetS(i) <= 0.01)
		{
			condensedGrid[maze].gridSquare[i].s = true;
		}
		else condensedGrid[maze].gridSquare[i].s = false;
	}
}
