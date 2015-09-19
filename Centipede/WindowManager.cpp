#include "WindowManager.h"

GLFWwindow* WindowManager::windowPtr = nullptr;

WindowManager::WindowManager()
{
}
WindowManager::~WindowManager()
{
}

int WindowManager::init() {
	if (!glfwInit())
		return -1;

	windowPtr = glfwCreateWindow(800, 800, "Test", NULL, NULL);
	if (!windowPtr)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(windowPtr);
	if (glewInit() != GLEW_OK) return false;

	glfwSetMouseButtonCallback(windowPtr, GameWorld::mouseClick);
	glfwSetCursorPosCallback(windowPtr, GameWorld::mouseMove);

	GameWorld::init();

	while (!glfwWindowShouldClose(windowPtr))
	{
		GameWorld::update();
		GameWorld::draw();
		glfwSwapBuffers(windowPtr);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}