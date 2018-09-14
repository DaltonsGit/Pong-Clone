#pragma once



#include "ResourceManager.h"
#include "Renderer.h"
#include "Textures.h"
#include "Shader.h"

#include "Ball.h"
#include "Paddles.h"
#include "Text.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION


const glm::vec2 player_Size(25, 100);
const float player_Velocity(100.0f);

class Game {

public:
	bool Keys[1024];

	Game(unsigned int width, unsigned int height);
	~Game();

	void setUpGame();
	void processInput(float dt);
	void update(float dt);

	void render();



private:
	unsigned int m_Width;
	unsigned int m_Height;

	Renderer *m_Renderer = new Renderer();
	Paddles *player1;
	Paddles *player2;
	Ball *ball;

	bool firstRound = false;

	void checkCollision();

	void whoScored();





};
