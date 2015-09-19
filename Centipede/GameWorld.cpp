#include "GameWorld.h"
#include "ShaderHelper.h"
#include "Shape.h"
#include <iostream>

using namespace std;

vec2 GameWorld::cursorPos = vec2(0, 0);
bool GameWorld::mouseButtonHeld = false;

// Objects
GLuint vertBuffObj;
GLuint vertArrObj;
GLuint program;
ShaderHelper helper;

// Variables
const GLsizei numVerts = 3;
const GLsizei numIndivVerts = numVerts * 2;

// Delta time variables
double lastFrameTime;
double prevTime = 0;

// Location variables
vec3 position;
vec3 scaleVec;
vec3 rotationAxis;
float rotationAmt;

// Window stuff
GLFWwindow* window;
double cursorXPos, cursorYPos;
int windowHeight;
int windowWidth;

// Shapes
Shape* triangle;
const GLsizei triVerts = 3;
const GLsizei triIndividVerts = numVerts * 5;

// Constructor / Destructor
GameWorld::GameWorld() {
}
GameWorld::~GameWorld() {

}


bool GameWorld::init() {
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) return false;

	position = vec3(0, 0, 0);
	scaleVec = vec3(1, 1, 1);
	rotationAxis = vec3(0, 0, 1.0f);

	program = helper.loadShaderProgram("Shaders/vertexShader.glsl", "Shaders/fragmentShader.glsl");
	if (program == 0) {
		cout << "Error loading program" << endl;
	}

	helper.setShaderColor(program, "color", 1.0f, 1.0f, 1.0f);

	// Put initially rendered stuff here, if you want
	GLfloat vertPostns[triIndividVerts] = {
		0.0f, 0.25f, 0.7f, 0.7f, 0.1f,
		0.25f, -0.25f, 0.1f, 0.7f, 0.7f,
		-0.25f, -0.25f, 0.7f, 0.1f, 0.7f
	};

	triangle = new Shape(vertPostns, triVerts, program);

	// ---
	return true;
}


void GameWorld::update() {
	lastFrameTime = glfwGetTime(); // Hey look it's fuckin' delta time
	double dt = lastFrameTime - prevTime;
	prevTime = lastFrameTime;
	rotationAmt += dt;
	// Update all the things here!



	// ---
	if (mouseButtonHeld == true) {

		mouseButtonHeld = false;
	}

}


void GameWorld::draw() {
	glClear(GL_COLOR_BUFFER_BIT);
	// Draw shit here!
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	triangle->Draw(0.25f, 0.25f, 0.0f, 1.0f, 1.0f, 1.0f, rotationAmt);
	// ---
	glFlush();
}


void GameWorld::mouseMove(GLFWwindow* windowPtr, double x, double y)
{
	cursorPos = getCursorPos(windowPtr);
}


void GameWorld::mouseClick(GLFWwindow* windowPtr, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		mouseButtonHeld = true;
	}
}


vec2 GameWorld::getCursorPos(GLFWwindow* windowPtr) {
	double xpos, ypos;
	glfwGetCursorPos(windowPtr, &xpos, &ypos);
	int width, height;
	glfwGetWindowSize(windowPtr, &width, &height);
	vec2 cursorPosition;
	cursorPosition.x = 2.0f * ((float)xpos / (float)width) - 1.0f;
	cursorPosition.y = (2.0f * ((float)ypos / (float)height) - 1.0f) * -1.0f;

	return cursorPosition;
}
