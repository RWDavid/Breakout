#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "game.h"
#include "resource_manager.h"


// GLFW function declarations
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// The width of the screen
const GLuint SCREEN_WIDTH = 1600;
// The height of the screen
const GLuint SCREEN_HEIGHT = 1200;

Game Breakout(SCREEN_WIDTH, SCREEN_HEIGHT);

int main(int argc, char *argv[])
{
	// Settings for the GLFW window are set here: OpenGL Core Version 3.3
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Breakout", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// glewExperimental is set to true so that glew can use modern techniques to retrieve OpenGL functions
	glewExperimental = GL_TRUE;
	glewInit();
	glGetError(); // Called once to catch glewInit() bug, all other errors are now from the application

	// Keyboard callback function is registered so that the user can input data from their keyboard
	glfwSetKeyCallback(window, key_callback);

	// OpenGL configuration
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Initialize all the settings for our game
	Breakout.Init();

	// DeltaTime variables are used to ensure graphics are displayed at a constant speed across different hardware
	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	// The game is started and put into the menu state
	Breakout.State = GAME_ACTIVE;

	while (!glfwWindowShouldClose(window))
	{
		// time between frames is used to calculate delta time, which is used to make sure graphics run at the same speed on different hardware
		GLfloat currentFrame = GLfloat(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();

		//deltaTime = 0.001f;
		// All user input is processed
		Breakout.ProcessInput(deltaTime);

		// The logic surrounding the state of the game is updated
		Breakout.Update(deltaTime);

		// Rendering
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		Breakout.Render();

		glfwSwapBuffers(window);
	}

	// Delete all loaded resources allocated by the ResourceManager
	ResourceManager::Clear();

	glfwTerminate();
	return 0;
}

/* Keyboard callback function: user input from the keyboard is logged
 *
 * ESCAPE : Closes the game
 *
 *
 *
 */
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			Breakout.Keys[key] = GL_TRUE;
		else if (action == GLFW_RELEASE)
			Breakout.Keys[key] = GL_FALSE;
	}
}