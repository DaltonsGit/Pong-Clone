#pragma once
#include "Entities.h"
#include <vector>


class Paddles : public Entities
{
public:
	Paddles();
	Paddles(glm::vec2 pos, glm::vec2 size, Textures sprite);

	void humanMovement(int direction, int height, float dt);
	void aiMovement(float ballLocation, float dt);
	float getDirection();
	void increaseScore();
	int getScore();

	std::vector <float>  getPaddleVertices();
	 std::vector <unsigned int>  getPaddlesIndices();

private:
	int score = 0;
	float playerVelocity = 300.0f;
	int direction = 0;

	std::vector <float> paddleVertices = {
		//x, y, z, w
		0.0f, 1.0f, 0.0f, 1.0f, 
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		//0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f
		//1.0f, 0.0f, 1.0f, 0.0f
	};

	std::vector <unsigned int>  paddlesIndices = {
		0, 1, 2,
		1, 3, 0

	};

};
