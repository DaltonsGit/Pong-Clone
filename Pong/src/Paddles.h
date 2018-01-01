#pragma once

#include "Entities.h"

class Paddles : public Entities
{
public:
	Paddles();
	Paddles(glm::vec2 pos, glm::vec2 size, Textures sprite);

	void humanMovement(int direction, int height, float dt);
	void aiMovement(float ballLocation, float dt);

private:
	float playerVelocity = 500.0f;

};
