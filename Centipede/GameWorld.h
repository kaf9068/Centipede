#pragma once
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glew.h>
#include <glfw3.h>

using namespace glm;

class GameWorld
{
public:
	GameWorld();
	~GameWorld();
	static bool init();
	static void update();
	static void draw();
	static void mouseClick(GLFWwindow* window, int button, int action, int mods);
	static void mouseMove(GLFWwindow* window, double x, double y);

	static vec2 cursorPos;
	static bool mouseButtonHeld;

private:
	static vec2 getCursorPos(GLFWwindow* windowPtr);
};

