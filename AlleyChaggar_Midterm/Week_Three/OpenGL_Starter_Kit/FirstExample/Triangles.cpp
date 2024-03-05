
///////////////////////////////////////////////////////////////////////
//
// By: Alireza Moghaddam Sep. 23 2020
// This code is used to demonstrate the renering pipeline for students in Seneca college
// Course GAM531/DPS931 Game Engine Foundations
//
///////////////////////////////////////////////////////////////////////

using namespace std;

#include "vgl.h"
#include "LoadShaders.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"


const GLint NumBuffers = 2;

GLuint Buffers[NumBuffers];

const GLuint NumVertices = 6;


//Will be used to store the location of our model-view matrix in VRAM
GLuint location;

//Will be used to create animation (rotate the square)
GLfloat alpha = 0;

//---------------------------------------------------------------------
//
// initialization: Setting up our rendering pipeline. Loading Shaders. Creating buffers in VRAM. 
//
//---------------------------------------------------------------------


GLfloat xPos1 = 0.0f; // X-coordinate for the first square
GLfloat yPos1 = 0.0f; // Y-coordinate for the first square

GLfloat xPos2 = 0.0f; // X-coordinate for the second square
GLfloat yPos2 = 0.0f; // Y-coordinate for the second square

bool moveSquares = true; // Flag to control square movement

void init(void)
{
	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "triangles.vert" },
		{ GL_FRAGMENT_SHADER, "triangles.frag" },
		{ GL_NONE, NULL }
	};

	GLuint program = LoadShaders(shaders);	//Loading the shaders from files: triangles.vert & triangles.frag
	glUseProgram(program);	//Compiling and running the shaders. And now, my Pipeline is set up :-)

	GLfloat vertices[NumVertices][2] = {
		// We use two triangles and connect them together to get a square. We're ONLY allowed to use triangles in this course.

		{ -0.45f,  0.45f },
		{  0.45f,  0.45f },
		{  0.45f, -0.45f },
		{  0.45f, -0.45f },
		{ -0.45f, -0.45f },
		{ -0.45f,  0.45f }
	};

	GLfloat colorData[NumVertices][3] = {
		{ 1.0f, 0.0f, 0.0f }, // Red
		{ 1.0f, 0.0f, 0.0f }, // Red
		{ 1.0f, 0.0f, 0.0f }, // Red

		{ 0.0f, 0.0f, 1.0f }, // Blue
		{ 0.0f, 0.0f, 1.0f }, // Blue
		{ 0.0f, 0.0f, 1.0f }  // Blue

	};

	//We allocate two buffers in VRAM: One for vertex data and the other for colors
	//Once created, we use Buffers[0] to point to the first, and Buffers[1] to point to the second.
	glGenBuffers(2, Buffers);

	//-----------------------------------------
	//Initializing the first buffer: Buffers[0]
	//-----------------------------------------





	//Selecting Buffers[0]
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);

	//Pushing the vertices data into the buffer (transmission from RAM to VRAM)
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//During the run-time, the buffer data should be transferred to the "vPosition" variable in the vertex shader
	glBindAttribLocation(program, 0, "vPosition");

	//We specify the format of the data in the buffer: 
	// GL_FLOAT: They are float as we have used a GLfloat[] array up in the code
	// 2: They must be considered as couples since we have 2D vertices (X, Y)
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	//Enable the buffer
	glEnableVertexAttribArray(0);
	//-------------------------------------------------------------------------
	//---------------We are done initializing the first buffer-----------------
	//-------------------------------------------------------------------------


	//-----------------------------------------
	//Initializing the second buffer: Buffers[1]
	//-----------------------------------------

	//Selecting Buffers[1]
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[1]);

	//Pushing the color data into the buffer (transmission from RAM to VRAM)
	glBufferData(GL_ARRAY_BUFFER, sizeof(colorData), colorData, GL_STATIC_DRAW);

	//During the run-time, the buffer data should be transferred to the "vertexColor" variable in the vertex shader
	glBindAttribLocation(program, 1, "vertexColor");

	//We specify the format of the data in the buffer: 
	// GL_FLOAT: They are float as we have used a GLfloat[] array up in the code
	// 3: They must be considered as triplets since we use 3 values for each color(red, green, blue)
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	//Enable the buffer
	glEnableVertexAttribArray(1);
	//-------------------------------------------------------------------------
	//---------------We are done initializing the second buffer----------------
	//-------------------------------------------------------------------------


	//Retreiving the memory address of the "model_view" matrix in VRAM (in vertex shader)
	location = glGetUniformLocation(program, "model_view");
}
//---------------Initialization accomplished :-)




//---------------------------------------------------------------------
//
// display function. All drawings happen here in the "display" function
//
//---------------------------------------------------------------------
void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	if (moveSquares) {
		// Move squares away from the center as they rotate
		if (xPos1 < 0.5f) xPos1 += 0.001f;
		if (yPos1 > -0.5f) yPos1 -= 0.001f;
		if (xPos2 > -0.5f) xPos2 -= 0.001f;
		if (yPos2 < 0.5f) yPos2 += 0.001f;
	}

	// Build model-view matrix for the first square (rotating clockwise)
	glm::mat4 model1 = glm::mat4(1.0f);
	model1 = glm::translate(model1, glm::vec3(xPos1, yPos1, 0.0f)); // Set position
	model1 = glm::rotate(model1, -alpha, glm::vec3(0, 0, 1)); // Rotate clockwise
	model1 = glm::scale(model1, glm::vec3(0.25f, 0.25f, 0.25f)); // Scale to desired size



	// Build model-view matrix for the second square (rotating counter-clockwise)
	glm::mat4 model2 = glm::mat4(1.0f);
	model2 = glm::translate(model2, glm::vec3(xPos2, yPos2, 0.0f)); // Set position
	model2 = glm::rotate(model2, alpha, glm::vec3(0, 0, 1)); // Rotate counter-clockwise
	model2 = glm::scale(model2, glm::vec3(0.25f, 0.25f, 0.25f)); // Scale to desired size



	// Pass model-view matrices to shader
	glUniformMatrix4fv(location, 1, GL_FALSE, &model1[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);

	glUniformMatrix4fv(location, 1, GL_FALSE, &model2[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);

	// Stop moving squares when they reach the destination points
	if (xPos1 >= 0.5f && yPos1 <= -0.5f && xPos2 <= -0.5f && yPos2 >= 0.5f) {
		moveSquares = false;
	}

	glutSwapBuffers();
	glutPostRedisplay();
}


void keyboard(unsigned char key, int x, int y)
{
	//Handler function for keyboard events
	//To be developed in next lectures
}

void mouse(int state, int button, int x, int y)
{
	//Handler function for keyboard events
	//To be developed in next lectures
}

//This function gets called for every frame. This will be used to animate the world 
void idle()
{
	float omega = 1;	//let omega to be the angular speed
	float timeSinceStart = glutGet(GLUT_ELAPSED_TIME) / 1000.f;		//Retreives the time in seconds
	alpha = omega * timeSinceStart;		//We use Theta = omega * time to calculate the amount of rotation of the geometry in this frame

	glutPostRedisplay();	//This is the explicit call to display function: display()
}

//---------------------------------------------------------------------
//
// main
//

int
main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);

	//The dimensions of the window
	glutInitWindowSize(512, 512);

	//The title for the window
	glutCreateWindow("Hello World");

	glewInit();	//Initializes the glew and prepares the drawing pipeline.

	init();

	//Defining our 'display', 'idle', 'mouse' and 'keyboard' functions.
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);

	//The following function makes the OpenGL to go through an infinite loop and waits for any event from keyboard, mouse, etc.
	glutMainLoop();



}