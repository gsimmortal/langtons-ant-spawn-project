
#include "stdafx.h"
#include "Ant.h"

// ==== CONSTRUCTORS ====
Ants::Ants(void)
{

}

// ==== GETTERS ====
float Ants::gridGetX(float square)
{
	return squareHolderXYC[square].x;
}
float Ants::gridGetY(float square)
{
	return squareHolderXYC[square].y;
}
RGB Ants::gridGetC(float square)
{
	return squareHolderXYC[square].c[0];
}
float Ants::gridGetScale(void)
{
	return gridScale;
}

// ==== SETTERS ====
void Ants::gridSetScale(float scale)
{
	//make odd for wall insertion
	int check = ((int)scale % 2);

	if (check == 0)gridScale = scale + 1;
	else gridScale = scale;

	//redo/reset vectors
	squareHolderXYC = vector<XYC>(int(gridScale) * int(gridScale));

	reDo();
}
void Ants::gridSetC(float square, int colour)
{
	squareHolderXYC[square].colourType = colour;
	switch (colour)
	{
	case 1://red
		squareHolderXYC[square].c[0].r = 1;
		squareHolderXYC[square].c[0].g = 1;
		squareHolderXYC[square].c[0].b = 1;
		break;
	case 2://orange
		squareHolderXYC[square].c[0].r = 1;
		squareHolderXYC[square].c[0].g = 1;
		squareHolderXYC[square].c[0].b =1 ;
		break;
	case 3://yellow
		squareHolderXYC[square].c[0].r = 1;
		squareHolderXYC[square].c[0].g =1 ;
		squareHolderXYC[square].c[0].b = 1;
		break;
	case 4://green
		squareHolderXYC[square].c[0].r = 1;
		squareHolderXYC[square].c[0].g =1 ;
		squareHolderXYC[square].c[0].b = 1;
		break;
	case 5://blue
		squareHolderXYC[square].c[0].r = 1;
		squareHolderXYC[square].c[0].g = 1;
		squareHolderXYC[square].c[0].b = 1;
		break;
	case 6://purple
		squareHolderXYC[square].c[0].r = 1;
		squareHolderXYC[square].c[0].g = 1;
		squareHolderXYC[square].c[0].b = 1;
		break;
	}

}

// ==== UPDATE FUNCTIONS ====
void Ants::antCrawl(int steps)
{
	for (int i = 0; i < steps; i++)
	{
		//get colour
		positionColour = squareHolderXYC[currentPosition].colourType;
		//set to new colour according to ruleset
		squareHolderXYC[currentPosition].colourType = ruleSet[(positionColour-1)].colour;
		reColour();
		//get new direction from ruleset
		direction = ruleSet[(positionColour-1)].direction;
		//move forward in that direction (include border warping conditions)
		switch (direction)
		{
		case 1: //north
			currentPosition = currentPosition - gridScale;
			//check if gone off top
			if (currentPosition < 0) currentPosition = (squareHolderXYC.capacity() - 1) + currentPosition;
			break;
		case 2: //east
			currentPosition = currentPosition + 1;
			//check if gone over max entities
			if (currentPosition > (squareHolderXYC.capacity() - 1)) currentPosition = 0;
			break;
		case 3: //south
			currentPosition = currentPosition + gridScale;
			//check if gone off bottom
			if (currentPosition > (squareHolderXYC.capacity() - 1)) currentPosition = 0 + (currentPosition - (squareHolderXYC.capacity() - 1));
			break;
		case 4: //west
			currentPosition = currentPosition - 1;
			//check if gone over max entities
			if (currentPosition <0) currentPosition = (squareHolderXYC.capacity() - 1) + currentPosition;
			break;
		}
	}

}

// ==== PRIVATE CALCULATIONS ====
void Ants::reDo(void)
{
	//random number init
	random_device rd;
	mt19937 mt(rd());

	uniform_int_distribution<int>cPoint(1, 6);
	uniform_int_distribution<int>dPoint(1, 4);

	cout << "entered redo in ant" << endl;

	for (int r = 0; r < ruleSet.capacity(); r++)
	{
		ruleSet[r].colour = 0;
		ruleSet[r].direction = 0;
	}
	for (int r = 0; r < colourHolder.capacity(); r++)
	{
		colourHolder[r] = 0;
	}
	for (int r = 0; r < directionHolder.capacity(); r++)
	{
		directionHolder[r] = 0;
	}

	//'seed' the random rules for recolour
	for (int i = 0; i < colourHolder.capacity(); i++)
	{
		int tmpCol2;
		while (true)
		{
			cout << "entered colour while in ant" << endl;
			bool used = false;
			//generate number
			tmpCol2 = cPoint(rd); 
			//check if used
			for (int j = 0; j < colourHolder.capacity(); j++)
			{
				//if used break (no need to keep searching)
				if (tmpCol2 == colourHolder[j])
				{
					used = true;
					break;
				}
			}
			//if not used after checking all elements break loop and assign value
			if (!used) break;
		}
		colourHolder[i] = tmpCol2;
		cout << "exited colour while in ant" << endl;
	}
	//'seed' the random rules for redirection
	for (int i = 0; i < directionHolder.capacity()-2; i++)
	{
		int tmpDir;
		while (true)
		{
			bool used = false;
			//generate number
			tmpDir = dPoint(rd);
			//check if used
			for (int j = 0; j < directionHolder.capacity()-2; j++)
			{
				//if used break (no need to keep searching)
				if (tmpDir == directionHolder[j])
				{
					used = true;
					break;
				}
			}
			//if not used after checking all elements break loop and assign value
			if (!used) break;
		}
		directionHolder[i] = tmpDir;
	}
	//re-use two directions giving directional bias
	directionHolder[4] = dPoint(rd);
	directionHolder[5] = dPoint(rd);

	//combine 'seeded' random rules to create ant rules
	for (int i = 0; i < ruleSet.capacity(); i++)
	{
		ruleSet[i].colour = colourHolder[i];
		ruleSet[i].direction = directionHolder[i];
	}

	cout << "ruleset for red: " << ruleSet[0].colour << "," << ruleSet[0].direction << endl;
	cout << "ruleset for orange: " << ruleSet[1].colour << "," << ruleSet[1].direction << endl;
	cout << "ruleset for yellow: " << ruleSet[2].colour << "," << ruleSet[2].direction << endl;
	cout << "ruleset for green: " << ruleSet[3].colour << "," << ruleSet[3].direction << endl;
	cout << "ruleset for blue: " << ruleSet[4].colour << "," << ruleSet[4].direction << endl;
	cout << "ruleset for purple: " << ruleSet[5].colour << "," << ruleSet[5].direction << endl;

	//set xy co-ordinates and random colour with rgb's
	for (int i = 0; i < squareHolderXYC.capacity(); i++)
	{
		squareHolderXYC[i].x = (float)((int)i % (int)gridScale);
		squareHolderXYC[i].y = (float)((int)i / (int)gridScale);
		squareHolderXYC[i].colourType = cPoint(rd);
		switch (squareHolderXYC[i].colourType)
		{
		case 1: //red
			squareHolderXYC[i].c[0].r = 1.0f;
			squareHolderXYC[i].c[0].g = 0.0f;
			squareHolderXYC[i].c[0].b = 0.0f;
			break;
		case 2: //orange
			squareHolderXYC[i].c[0].r = 1.0f;
			squareHolderXYC[i].c[0].g = 0.5f;
			squareHolderXYC[i].c[0].b = 0.0f;
			break;
		case 3: //yellow
			squareHolderXYC[i].c[0].r = 1.0f;
			squareHolderXYC[i].c[0].g = 1.0f;
			squareHolderXYC[i].c[0].b = 0.0f;
			break;
		case 4: //green
			squareHolderXYC[i].c[0].r = 0.0f;
			squareHolderXYC[i].c[0].g = 1.0f;
			squareHolderXYC[i].c[0].b = 0.0f;
			break;
		case 5: //blue
			squareHolderXYC[i].c[0].r = 0.0f;
			squareHolderXYC[i].c[0].g = 0.0f;
			squareHolderXYC[i].c[0].b = 1.0f;
			break;
		case 6: //purple
			squareHolderXYC[i].c[0].r = 0.5f;
			squareHolderXYC[i].c[0].g = 0.0f;
			squareHolderXYC[i].c[0].b = 0.5f;
			break;
		}

	}

	cout << "exiting redo in ant" << endl;

}
void Ants::reColour(void)
{
	switch (squareHolderXYC[currentPosition].colourType)
	{
	case 1: //red
		squareHolderXYC[currentPosition].c[0].r = 1.0f;
		squareHolderXYC[currentPosition].c[0].g = 0.0f;
		squareHolderXYC[currentPosition].c[0].b = 0.0f;
		break;
	case 2: //orange
		squareHolderXYC[currentPosition].c[0].r = 1.0f;
		squareHolderXYC[currentPosition].c[0].g = 0.5f;
		squareHolderXYC[currentPosition].c[0].b = 0.0f;
		break;
	case 3: //yellow
		squareHolderXYC[currentPosition].c[0].r = 1.0f;
		squareHolderXYC[currentPosition].c[0].g = 1.0f;
		squareHolderXYC[currentPosition].c[0].b = 0.0f;
		break;
	case 4: //green
		squareHolderXYC[currentPosition].c[0].r = 0.0f;
		squareHolderXYC[currentPosition].c[0].g = 1.0f;
		squareHolderXYC[currentPosition].c[0].b = 0.0f;
		break;
	case 5: //blue
		squareHolderXYC[currentPosition].c[0].r = 0.0f;
		squareHolderXYC[currentPosition].c[0].g = 0.0f;
		squareHolderXYC[currentPosition].c[0].b = 1.0f;
		break;
	case 6: //purple
		squareHolderXYC[currentPosition].c[0].r = 0.5f;
		squareHolderXYC[currentPosition].c[0].g = 0.0f;
		squareHolderXYC[currentPosition].c[0].b = 0.5f;
		break;
	}
}