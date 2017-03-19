#include "game.h"
#include "resource_manager.h"
#include "sprite_renderer.h"
#include "game_object.h"

#include <glm/gtc/matrix_transform.hpp>

/* Game objects */
SpriteRenderer	*Renderer;	// Takes care of the rendering for background, levels, objects, etc.
GameObject		*Player;	// Player-controlled paddle

/* Player variables */
const glm::vec2 PLAYER_SIZE(200, 40);	// Initial size of the player-controlled paddle
const GLfloat PLAYER_VELOCITY(500.0f);	// Initial velocity of the player-controlled paddle

Game::Game(GLuint width, GLuint height)
	: State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{
}

Game::~Game()
{
	delete Renderer;
	delete Player;
}

void Game::Init()
{
	// Create a shader program from pre-loaded shader files
	ResourceManager::LoadShader("Shaders/Sprite.vs", "Shaders/Sprite.frag", nullptr, "sprite");

	// Set up projection matrix and send to the graphics pipeline (fragment shader)
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

	// Load textures
	ResourceManager::LoadTexture("Textures/puppy_background.jpg", GL_FALSE, "background");
	ResourceManager::LoadTexture("Textures/block.png", GL_FALSE, "block");
	ResourceManager::LoadTexture("Textures/block_solid.png", GL_FALSE, "block_solid");
	ResourceManager::LoadTexture("Textures/paddle.png", GL_TRUE, "paddle");

	// Set render-specific controls
	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

	// Load levels
	GameLevel one; one.Load("Levels/one.lvl", this->Width, static_cast<GLuint>(this->Height * 0.5));
	GameLevel two; two.Load("Levels/two.lvl", this->Width, static_cast<GLuint>(this->Height * 0.5));
	GameLevel three; three.Load("Levels/three.lvl", this->Width, static_cast<GLuint>(this->Height * 0.5));
	GameLevel four; four.Load("Levels/four.lvl", this->Width, static_cast<GLuint>(this->Height * 0.5));
	this->Levels.push_back(one);
	this->Levels.push_back(two);
	this->Levels.push_back(three);
	this->Levels.push_back(four);
	this->Level = 0; // Current level

	// Set player related settings
	glm::vec2 playerPos((this->Width - PLAYER_SIZE.x) / 2, this->Height - PLAYER_SIZE.y);
	Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));
}

void Game::ProcessInput(GLfloat dt)
{
	if (this->State == GAME_ACTIVE)
	{
		GLfloat velocity = PLAYER_VELOCITY * dt;
		// Move playerboard
		if (this->Keys[GLFW_KEY_A])
		{
			if (Player->Position.x >= 0)
				Player->Position.x -= velocity;
		}
		if (this->Keys[GLFW_KEY_D])
		{
			if (Player->Position.x <= this->Width - Player->Size.x)
				Player->Position.x += velocity;
		}
	}
}

void Game::Update(GLfloat dt)
{
}

void Game::Render()
{
	if (this->State == GAME_ACTIVE)
	{
		// Draw background
		Renderer->DrawSprite(ResourceManager::GetTexture("background"),
			glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f
		);
		// Draw level
		this->Levels[this->Level].Draw(*Renderer);
		Player->Draw(*Renderer);
	}
}