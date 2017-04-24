
#include "stdafx.h"
#include "MakeGrid.h"

// ==== CONSTRUCTORS ====
Grids::Grids(void)
{

}

// ==== GETTERS ====
float Grids::gridGetX(float square)
{
	return squareHolderXYSWN[square].x;
}
float Grids::gridGetY(float square)
{
	return squareHolderXYSWN[square].y;
}
float Grids::gridGetS(float square)
{
	return squareHolderXYSWN[square].s;
}
float Grids::gridGetScale(void)
{
	return gridScale;
}

// ==== SETTERS ====
void Grids::gridSetScale(float scale)
{
	//make odd for wall insertion
	int check = ((int)scale % 2);

	if (check == 0)gridScale = scale + 1;
	else gridScale = scale;

	squareHolderXYSWN = vector<XYSWN>(int(gridScale) * int(gridScale));
	reDo();
}
void Grids::gridSetS(float square, float solidity)
{
	squareHolderXYSWN[square].s = solidity;
}
//setWeight may be needed in future to influence maze structure
/*void Grids::gridSetW(float square, int weighting)
{
	squareHolderXYSWN[square].w = weighting;
}
*/

// ==== UPDATE FUNCTIONS ====
void Grids::callNeighbours(float square)
{
	cout << "N@ Wid: " << squareHolderXYSWN[square].neighbourContainer[0].westID << " Nid: " << squareHolderXYSWN[square].neighbourContainer[0].northID;
	cout << " Sid: " << squareHolderXYSWN[square].neighbourContainer[0].southID << " Eid: " << squareHolderXYSWN[square].neighbourContainer[0].eastID << endl;
}
void Grids::gridMazify(void)
{
	cout << "Running the Maze !!!" << endl;

	//initialise local counter here to see if all cells have been checked and holder for current cell ID
	int visitable = ((gridScale + 1) / 2)*((gridScale + 1) / 2);
	int visited = 0;
	int currentCell = 0;
	int chosenCell = 0;

	//work out best suited 'centre'
	int makeEven = ((gridScale + 1) / 2);//gridscale is always odd so this finds how many non wall objects there are (valid checkable cells)
	float centreID;
	int check = (makeEven % 2);//this checks if the no. of valid checkable cells is even by finding remainder when dividing by 2if odd the centre can be used
	if (check == 0) centreID = (((squareHolderXYSWN.capacity() - 1) / 2) - gridScale) - 1; //if even the centre of the maze must be offset
	else if (check != 0)centreID = (squareHolderXYSWN.capacity() - 1) / 2;//if odd the centre can be used
	else cout << "checkMe";

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!mazing stuff here!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	//============================Make the initial cell the current cell and mark it as visited======================

	currentCell = centreID;
	squareHolderXYSWN[currentCell].visited = true;
	squareHolderXYSWN[currentCell].s = 1;//solidity 0 makes this cell a path and not a wall
	visited++;

	//=============================While there are unvisited valid cells==============================
	int invalidPassR = 0;//keep for debugging

	while (visited < visitable)
	{
#pragma region Valid Square Neighbour Checks and Sorting
		bool validNeighbours = false;

		//reset neighbours when restarting
		validNeighbours = false;
		//cout << "at id " << currentCell;
		//NORTH -- only inc this if its not cellID 0.1 (off the grid) and not already visited!

		float tmpN = squareHolderXYSWN[currentCell].neighbourContainer[1].northID;

		//validation check.. DO NOT GET VISITED value IF CELL ID = 0.1 (invalid/off grid)... this typesets to 0 and returns entity 0's visited value
		bool tmpNV = true;//visited flag defaults to true (already visited) and only changes if a valid id needs to be checked
		if (tmpN != 0.1)  tmpNV = squareHolderXYSWN[(squareHolderXYSWN[currentCell].neighbourContainer[1].northID)].visited;

		if (((tmpN < 0.1- epsilon)||(tmpN > 0.1 + epsilon)) && !tmpNV)
		{
			//cout << " my north is: " << tmpN;
				//squareHolderXYSWN[currentCell].neighbourContainer[1].northID << endl;
			heldSquares[0].square = squareHolderXYSWN[currentCell].neighbourContainer[1].northID;
			heldSquares[0].weight = squareHolderXYSWN[heldSquares[0].square].w;
			heldSquares[0].direction = 1;//1 = NORTH
			validNeighbours = true;
		}
		else //clear previously held neighbour and make it unlikely this is the 'lightest' cell
		{
			heldSquares[0].square = 0.1;
			heldSquares[0].weight = 9999;
			heldSquares[0].direction = 0;//invalid direction
		}
		//EAST -- only inc this if its not cellID 0.1 (off the grid) and not already visited!
		float tmpE = squareHolderXYSWN[currentCell].neighbourContainer[1].eastID;
		//validation check.. DO NOT GET VISITED value IF CELL ID = 0.1 (invalid/off grid)... this typesets to 0 and returns entity 0's visited value
		bool tmpEV = true;//visited flag defaults to true (already visited) and only changes if a valid id needs to be checked
		if (tmpE != 0.1)  tmpEV = squareHolderXYSWN[(squareHolderXYSWN[currentCell].neighbourContainer[1].eastID)].visited;

		if (((tmpE < 0.1 - epsilon) || (tmpE > 0.1 + epsilon)) && !tmpEV)
		{
			//cout << " my east is: " << tmpE;
				//squareHolderXYSWN[currentCell].neighbourContainer[1].eastID << endl;
			heldSquares[1].square = squareHolderXYSWN[currentCell].neighbourContainer[1].eastID;
			heldSquares[1].weight = squareHolderXYSWN[heldSquares[1].square].w;
			heldSquares[1].direction = 2;//2 = EAST
			validNeighbours = true;
		}
		else //clear previously held neighbour and make it unlikely this is the 'lightest' cell
		{
			heldSquares[1].square = 0.1;
			heldSquares[1].weight = 9999;
			heldSquares[1].direction = 0;//invalid direction
		}
		//SOUTH -- only inc this if its not cellID 0.1 (off the grid) and not already visited!
		float tmpS = squareHolderXYSWN[currentCell].neighbourContainer[1].southID;

		//validation check.. DO NOT GET VISITED value IF CELL ID = 0.1 (invalid/off grid)... this typesets to 0 and returns entity 0's visited value
		bool tmpSV = true;//visited flag defaults to true (already visited) and only changes if a valid id needs to be checked
		if (tmpS != 0.1)  tmpSV = squareHolderXYSWN[(squareHolderXYSWN[currentCell].neighbourContainer[1].southID)].visited;

		if (((tmpS < 0.1 - epsilon) || (tmpS > 0.1 + epsilon)) && !tmpSV)
		{
			//cout << " my south is: " << tmpS;
				//squareHolderXYSWN[currentCell].neighbourContainer[1].southID << endl;
			heldSquares[2].square = squareHolderXYSWN[currentCell].neighbourContainer[1].southID;
			heldSquares[2].weight = squareHolderXYSWN[heldSquares[2].square].w;
			heldSquares[2].direction = 3;//3 = SOUTH
			validNeighbours = true;
		}
		else //clear previously held neighbour and make it unlikely this is the 'lightest' cell
		{
			heldSquares[2].square = 0.1;
			heldSquares[2].weight = 9999;
			heldSquares[2].direction = 0;//invalid direction
		}
		//WEST -- only inc this if its not cellID 0.1 (off the grid) and not already visited!
		float tmpW = squareHolderXYSWN[currentCell].neighbourContainer[1].westID;
		//validation check.. DO NOT GET VISITED value IF CELL ID = 0.1 (invalid/off grid)... this typesets to 0 and returns entity 0's visited value
		bool tmpWV = true;//visited flag defaults to true (already visited) and only changes if a valid id needs to be checked
		if (tmpW != 0.1)  tmpWV = squareHolderXYSWN[(squareHolderXYSWN[currentCell].neighbourContainer[1].westID)].visited;

		if (((tmpW < 0.1 - epsilon) || (tmpW > 0.1 + epsilon)) && !tmpWV)
		{
			//cout << " my west is: " << tmpW;
				//squareHolderXYSWN[currentCell].neighbourContainer[1].westID << endl;
			heldSquares[3].square = squareHolderXYSWN[currentCell].neighbourContainer[1].westID;
			heldSquares[3].weight = squareHolderXYSWN[heldSquares[3].square].w;
			heldSquares[3].direction = 4;//4 = WEST
			validNeighbours = true;
		}
		else //clear previously held neighbour and make it unlikely this is the 'lightest' cell
		{
			heldSquares[3].square = 0.1;
			heldSquares[3].weight = 9999;
			heldSquares[3].direction = 0;//invalid direction
		}
		//cout << "bubble in:";
		//cout << heldSquares[0].weight << ",";
		//cout << heldSquares[1].weight << ",";
		//cout << heldSquares[2].weight << ",";
		//cout << heldSquares[3].weight << endl;

		neighbourSorting();
		//if (validNeighbours)cout << " bubble out:" << heldSquares[0].weight << endl;

#pragma endregion

		//=====================If the current cell has any valid neighbours which have not been visited=======================

		if (validNeighbours)
		{
			//=============================Choose lightest of the unvisited neighbours (heldSquare[0]after sorting)=============================
			chosenCell = heldSquares[0].square;

			//=====================================Push the current cell ID to the stack=================================
			mazingStack.push(currentCell);
			//cout << "pushed" << currentCell;
			//===Remove the wall between the current cell and the chosen cell if it hasnt been visited previously=========================
			//if (!squareHolderXYSWN[chosenCell].visited)
			//{
			//cout << "should travel " << heldSquares[0].direction;
				switch (heldSquares[0].direction)
				{
				case 1: //NORTH
					squareHolderXYSWN[(squareHolderXYSWN[currentCell].neighbourContainer[0].northID)].visited = true;
					squareHolderXYSWN[(squareHolderXYSWN[currentCell].neighbourContainer[0].northID)].s = 1;//solidity 1 makes this cell a path and not a wall
					//cout << " did travel 1" << endl;
					break;
				case 2: //EAST
					squareHolderXYSWN[(squareHolderXYSWN[currentCell].neighbourContainer[0].eastID)].visited = true;
					squareHolderXYSWN[(squareHolderXYSWN[currentCell].neighbourContainer[0].eastID)].s = 1;//solidity 1 makes this cell a path and not a wall
					//cout << " did travel 2" << endl;
					break;
				case 3: //SOUTH
					squareHolderXYSWN[(squareHolderXYSWN[currentCell].neighbourContainer[0].southID)].visited = true;
					squareHolderXYSWN[(squareHolderXYSWN[currentCell].neighbourContainer[0].southID)].s = 1;//solidity 1 makes this cell a path and not a wall
					//cout << " did travel 3" << endl;
					break;
				case 4: //WEST
					squareHolderXYSWN[(squareHolderXYSWN[currentCell].neighbourContainer[0].westID)].visited = true;
					squareHolderXYSWN[(squareHolderXYSWN[currentCell].neighbourContainer[0].westID)].s = 1;//solidity 1 makes this cell a path and not a wall
					//cout << " did travel 4" << endl;
					break;
				default:
					cout << "invalid direction passed at:" << squareHolderXYSWN[(heldSquares[0].square)].x << "," << squareHolderXYSWN[(heldSquares[0].square)].y << endl;
					invalidPassR++;
					break;
				}
			//}

			//=====================================Make the chosen cell the current cell and mark it as visited=============================
			currentCell = chosenCell;
			squareHolderXYSWN[currentCell].visited = true;
			squareHolderXYSWN[currentCell].s = 1;//solidity 1 makes this cell a path and not a wall
			visited++;
		}
		//==============================================Else if stack is not empty========================================
		else if (mazingStack.size() > 0)
		{
			mazingStack.pop();
			//cout << "backtrack to:" << mazingStack.top() << endl;
			//==========================================Make stack top the current cell=====================================
			currentCell = mazingStack.top();
			//==============================================Pop/remove it from stack=========================================
			
			//cout << "popped:" << currentCell << endl;
			//mazingStack.pop();
		}

		//===================================Else======================================
		else
		{
			cout << "went into else... Why?" << endl;
			//=================================Pick a random unvisited cell, make it the current cell and mark it as visited================================
		}
	}
	cout << "A-Maze-Ing!!!" << endl;
	cout << "INVALID PASSES RECIEVED: " << invalidPassR << endl;


}

// ==== PRIVATE CALCULATIONS ====
void Grids::reDo(void)
{
	//random number init
	random_device rd;
	mt19937 mt(rd());

	uniform_int_distribution<int>iPoint(1, 100);

	for (int i = 0; i < squareHolderXYSWN.capacity(); i++)
	{
		squareHolderXYSWN[i].x = (float)((int)i % (int)gridScale);
		squareHolderXYSWN[i].y = (float)((int)i / (int)gridScale);
		//if valid give it weight and solidity
		//valid squares have an even x and even y value
		int remainderX = ((int)squareHolderXYSWN[i].x % 2), remainderY = ((int)squareHolderXYSWN[i].y % 2);

		if (remainderX == 0 && remainderY == 0) //if valid give it weight and solidity 
		{
			squareHolderXYSWN[i].w = iPoint(rd);
			squareHolderXYSWN[i].s = ((float)squareHolderXYSWN[i].w / 100);
		}
		else //if invalid make it a solid wall
		{
			squareHolderXYSWN[i].w = 100;
			squareHolderXYSWN[i].s = 0;//solidity 0 makes this cell a wall not a path

		}

		//neighbour adding for walls
		if (squareHolderXYSWN[i].x > 0)
		{
			squareHolderXYSWN[i].neighbourContainer[0].westID = (float)i - 1;
		}
		if (squareHolderXYSWN[i].x < (gridScale - 1))
		{
			squareHolderXYSWN[i].neighbourContainer[0].eastID = (float)i + 1;
		}
		if (squareHolderXYSWN[i].y > 0)
		{
			squareHolderXYSWN[i].neighbourContainer[0].northID = (float)i - gridScale;
		}
		if (squareHolderXYSWN[i].y < (gridScale - 1))
		{
			squareHolderXYSWN[i].neighbourContainer[0].southID = (float)i + gridScale;
		}
		//neighbour adding for valid cells same as above +1
		if (squareHolderXYSWN[i].x > 1)
		{
			squareHolderXYSWN[i].neighbourContainer[1].westID = (float)i - 2;
		}
		if (squareHolderXYSWN[i].x < (gridScale - 2))
		{
			squareHolderXYSWN[i].neighbourContainer[1].eastID = (float)i + 2;
		}
		if (squareHolderXYSWN[i].y > 1)
		{
			squareHolderXYSWN[i].neighbourContainer[1].northID = (float)i - (2 * gridScale);
		}
		if (squareHolderXYSWN[i].y < (gridScale - 2))
		{
			squareHolderXYSWN[i].neighbourContainer[1].southID = (float)i + (2 * gridScale);
		}
	}
}
void Grids::neighbourSorting(void)
{

	int index = 0, pass = 0;
	bool swap = false;
	//sort neighbours via weight smallest ends up as held square 0
	while (true)//improved bubble sort
	{
		if (heldSquares[index].weight > heldSquares[index + 1].weight) //compare elemts
		{
			tmpNeighbour[0] = heldSquares[index]; //use temp variable to handle swap
			heldSquares[index] = heldSquares[index + 1];
			heldSquares[index + 1] = tmpNeighbour[0];
			swap = true; //done at least one swap
		}

		index++;

		if (index >= (maxIndex - pass)) // done n - i - 1 operations
		{
			if (!swap) break; //check to see if swap occurred. If not, break.
			pass++;
			index = 0; //start again
			swap = false; //reset swap flag before restarting
		}
	}
}