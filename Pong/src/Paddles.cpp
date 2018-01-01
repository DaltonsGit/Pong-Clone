#include "Paddles.h"

Paddles::Paddles()
	: Entities() {}

Paddles::Paddles(glm::vec2 position, glm::vec2 size, Textures tex)
	: Entities(position, size, tex, glm::vec3(1.0f), glm::vec2(1.0f)) {}

void Paddles::humanMovement(int direction, int height, float dt) {

	if (direction == 1) {
		
		if (this->m_Position.y >= 0) {
			this->m_Position.y -= (playerVelocity * dt);
		}
	}
	else if (direction == -1) {
		if (this->m_Position.y <= height - this->m_Size.y) {
			this->m_Position.y += (playerVelocity * dt);
		}

	}

}

void Paddles::aiMovement(float ballLocation, float dt) {

	if (ballLocation < this->m_Position.y) {

		this->m_Position.y -= (playerVelocity * dt);
	}

	else if (ballLocation > this->m_Position.y) {

		this->m_Position.y += (playerVelocity * dt);
	}

}