#ifndef GAME_H
#define GAME_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <vector>

#include "game_level.h"

// Represents the current state of the game
enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

class Game
{
public:
	// Game state
	GameState State;				// Menu | Active | Win
	GLboolean Keys[1024];			// Keeps track of the states of the keyboard keys
	GLuint Width, Height;			// Dimensions required to format the screen
	std::vector<GameLevel> Levels;	// A collection of levels to be loaded
	GLuint Level;					// The current level

	// Constructor/Destructor
	Game(GLuint width, GLuint height);
	~Game();

	// Initialize game state (load all shaders/textures/levels)
	void Init();

	// Game loop functions
	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render();
};
#endif
