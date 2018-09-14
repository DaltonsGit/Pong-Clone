#pragma once

#include "Entities.h"
#include <vector>

class Ball : public Entities
{

public:
	Ball();
	Ball(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, Textures sprite);
	
	glm::vec2 Move(float dt, unsigned int windowHeight);
	void increaseSpeed();

	int getHits();
	bool leftScored = false;
	bool rightScore = false;

	std::vector <float>  getBallVertices();
	std::vector <unsigned int>  getBallIndices();
	glm::vec2 getCurrentSpeed();

	void resetBall();
	

private:

	glm::vec2 intialSpeed;
	glm::vec2 currentSpeed; 
	bool start = false;
	int m_Hits = 0;


	std::vector <float> ballVertices = {
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 1.0f

	};

	std::vector <unsigned int>  ballIndices = {
		0, 1, 2,
		1, 3, 0

	};



};