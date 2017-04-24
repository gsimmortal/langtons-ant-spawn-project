// Graphics courseworkWeek adapted from week 9 - Demo 04 

#include "stdafx.h"
#include <glew\glew.h>
#include <freeglut\freeglut.h>
#include <CoreStructures\CoreStructures.h>
#include <math.h>
#include "GridInterface.h"
//#include "MakeGrid.h"
//#include "Ant.h"

using namespace std;
using namespace CoreStructures;

#pragma region Prototypes
// Function Prototypes
void init(void);
void report_version(void);
void update(void);
void display(void);
void keyDown(unsigned char key, int x, int y);
int getScale();
#pragma endregion

//grid holders size 10 for now (were only using element0)
Grids gridHolder[10];
Ants antHolder[10];
GridInterface interface1[2];
int gridSize = 1;
bool drawAnts = false;
int antCountdown = 0;


int _tmain(int argc, char* argv[]) {

	glutInit(&argc, argv);

	// Initialise COM so we can use Windows Imaging Component
	initCOM();

	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

	glutInitWindowSize(800, 800);
	glutInitWindowPosition(64, 64);
	glutCreateWindow("GridStructor");

	// Register display callback function
	glutDisplayFunc(display);

	// Keyboard and mouse callback functions
	glutKeyboardFunc(keyDown);
	glutIdleFunc(update);

	init();

	glutMainLoop();

	// Shut down COM
	shutdownCOM();

	return 0;
}
void init(void) {

#pragma region glew initialisation
	// Initialise GLEW library
	GLenum err = glewInit();
	// Ensure GLEW was initialised successfully before proceeding
	if (err == GLEW_OK) {
		cout << "GLEW initialised okay\n";
	}
	else {
		cout << "GLEW could not be initialised\n";
		throw;
	}

	// Example query OpenGL state (get version number)
	report_version();
	// Report maximum number of vertex attributes
	GLint numAttributeSlots;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &numAttributeSlots);
	cout << "GL_MAX_VERTEX_ATTRIBS = " << numAttributeSlots << endl;
	//set up texture mapping properties
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//set clear background colour:
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//set line width:
	glLineWidth(2.0f);
	//glShadeModel(GL_FLAT);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	//enable transparency and blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Set Projection and model view transformations
	glMatrixMode(GL_PROJECTION); // Select the projection matrix
	glLoadIdentity(); // Reset the projection matrix
	glOrtho(-5.0f, 5.0f, -5.0f, 5.0f, -1.0f, 1.0f);
	// Clear all previous transformations
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

#pragma endregion

	//Reccomend maze parameters
	cout << endl << "When initialising a grid it is reccomend to use" << endl << "a grid size of bettween 3 and 650" << endl << " ====== OR AT MAXIMUM 2500 ====== " << endl;

}

void report_version(void) {
	int majorVersion, minorVersion;
	glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
	glGetIntegerv(GL_MINOR_VERSION, &minorVersion);
	cout << "OpenGL version " << majorVersion << "." << minorVersion << endl;
}

void update(void)
{
	glutPostRedisplay();

	if (drawAnts)
	{
		//antCountdown++;
		//if (antCountdown >= 5)
		//{
			antHolder[0].antCrawl(1);
			//antCountdown = 0;
		//}
	}

}

void display(void) {

	// 1. Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// 2. Clear previous transformations
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Draw grid


	if (interface1[0].getInitialized())
	{
		interface1[0].update();
		for (int i = 0; i < getScale()*getScale(); i++)
		{
			XY tmpXY = interface1[0].getXY(i); 
			bool tmpIsSolid = interface1[0].getSolid((float)i);

			glBegin(GL_QUADS);
			if (tmpIsSolid)glColor4f(0.0f, 0.0f, 0.0f, 1.0f); 
			else 
			{
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				RGB tmpRGB = interface1[0].getLAC((float)i);
				glColor4f(tmpRGB.r, tmpRGB.g, tmpRGB.b, 1.0f);
			}
			glVertex2f(tmpXY.y - (getScale() / 2) + 1, tmpXY.x - (getScale() / 2) + 1);
			glVertex2f(tmpXY.y - (getScale() / 2) + 1, tmpXY.x - (getScale() / 2));
			glVertex2f(tmpXY.y - (getScale() / 2), tmpXY.x - (getScale() / 2));
			glVertex2f(tmpXY.y - (getScale() / 2), tmpXY.x - (getScale() / 2) + 1);
			glEnd();
		}
	}

	// 2. Clear previous transformations??????????
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutSwapBuffers();
}

void keyDown(unsigned char key, int x, int y) {
	float tmpGS = 1.0f;
	int check = 0;
	int tmpSize = 25;

	switch (key) {
	case 'i':
		interface1[0].generate();
		interface1[0].setTickSpeed(25);

		// Set Projection and model view transformations
		glMatrixMode(GL_PROJECTION); // Select the projection matrix
		glLoadIdentity(); // Reset the projection matrix
		glOrtho(((float)-getScale() / 2), ((float)getScale() / 2) + (getScale() * 0.05), ((float)-getScale() / 2), ((float)getScale() / 2) + (getScale() * 0.05), -1.0f, 1.0f);

		// Clear all previous transformations
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		break;
	case 'r':
		interface1[0].resetLA();
		break;
	case 'c':
		
		
		cout << "enter gs: " << endl;
		cin >> tmpSize;

		interface1[0].generate(tmpSize);
		interface1[0].resetLA();
		

		interface1[0].setTickSpeed(25);
		// Set Projection and model view transformations
		glMatrixMode(GL_PROJECTION); // Select the projection matrix
		glLoadIdentity(); // Reset the projection matrix
		//0.05 = scale / (20*scale)
		glOrtho(((float)-getScale() / 2), ((float)getScale() / 2) + (getScale() * 0.05), ((float)-getScale() / 2), ((float)getScale() / 2) + (getScale() * 0.05), -1.0f, 1.0f);
		
		// Clear all previous transformations
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		break;
	case 'z':
		interface1[0].heldData(0);
		break;
	}
}

int getScale(){
	return interface1[0].getScale();
}
