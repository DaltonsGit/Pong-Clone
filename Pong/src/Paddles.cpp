#include "Paddles.h"

Paddles::Paddles()
	: Entities() {}

Paddles::Paddles(glm::vec2 position, glm::vec2 size, Textures tex)
	: Entities(position, size, tex, glm::vec3(1.0f), glm::vec2(1.0f)) {}

void Paddles::humanMovement(int direction, int height, float dt) {

	if (direction == 1) {
		
		if (this->m_Position.y >= 0) {
			this->m_Position.y -= (playerVelocity * dt);
			this->direction = direction;
		}
	}
	else if (direction == -1) {
		if (this->m_Position.y <= height - this->m_Size.y) {
			this->m_Position.y += (playerVelocity * dt);
			this->direction = direction;
		}

	}

}

void Paddles::aiMovement(float ballLocation, float dt) {

	if (ballLocation < this->m_Position.y) {

		this->m_Position.y -= (playerVelocity * dt);
		this->direction = -1;
	}

	else if (ballLocation > this->m_Position.y) {

		this->m_Position.y += (playerVelocity * dt);
		this->direction = 1;
	}

}

float Paddles::getDirection() {

	return this->direction;

}

void Paddles::increaseScore() {

	++this->score;

}

int Paddles::getScore() {

	return this->score;

}

std::vector <float> Paddles::getPaddleVertices() {

	
	return paddleVertices;

}

std::vector <unsigned int> Paddles::getPaddlesIndices() {

	return paddlesIndices;

}