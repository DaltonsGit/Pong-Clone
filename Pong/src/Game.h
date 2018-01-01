#pragma once

//#include <GL/glew.h>
//#include <GLFW/glfw3.h>


#include "ResourceManager.h"
#include "Renderer.h"
#include "Textures.h"
#include "Shader.h"
#include "Entities.h"
#include "Paddles.h"


const glm::vec2 player_Size(25, 100);
const float player_Velocity(500.0f);

class Game {

public:
	bool Keys[1024];

	Game(unsigned int width, unsigned int height);
	~Game();

	void setUpGame();
	void processInput(float dt);
	void ballMovement(float dt);
	void aiMovement(float dt);
	void render();



private:
	unsigned int m_Width;
	unsigned int m_Height;

	float bd = 1.0;

	//const glm::vec2 player_Size = glm::vec2(200, 75);

	Renderer *m_Renderer = new Renderer();
	Paddles *player1;
	Paddles *player2;
	Entities *ball;

};
