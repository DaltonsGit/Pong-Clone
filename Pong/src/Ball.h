#pragma once

#include "Entities.h"

class Ball : public Entities
{

public:
	Ball();
	Ball(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, Textures sprite);
	
	glm::vec2 Move(float dt, unsigned int windowHeight);
	void increaseSpeed();

	int getHits();
	//void checkCollision(glm::vec2 objectLocation, glm::vec2 objectSize);
	bool leftScored = false;
	bool rightScore = false;


	

private:

	glm::vec2 intialSpeed;
	bool start = false;
	int m_Hits = 0;

	void resetBall();



};