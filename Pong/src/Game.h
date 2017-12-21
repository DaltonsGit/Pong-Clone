#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"


class Game {

public:

	Game(unsigned int width, unsigned int height);
	~Game();

	void setUpGame();
	void processInput(float dt);
	void render();


private:
	unsigned int m_Width;
	unsigned int m_Height;

	Renderer *m_Renderer;
};
