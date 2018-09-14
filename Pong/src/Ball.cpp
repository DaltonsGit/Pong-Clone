#include "Ball.h"

#include <iostream>

Ball::Ball()
	: Entities() {}

Ball::Ball(glm::vec2 position, glm::vec2 size, glm::vec2 velocity, Textures sprite)
	: Entities(position, size, sprite, glm::vec3(1.0f), velocity) {

	this->intialSpeed = velocity;
	currentSpeed = intialSpeed;

}

glm::vec2 Ball::Move(float dt, unsigned int windowHeight) {

	m_Position.y += m_Velocity.y * dt;
	m_Position.x += m_Velocity.x * dt;

	if (m_Position.y <= 0.0f) {


		m_Velocity.y *= -1;

	}

	else if (m_Position.y >= windowHeight) {

		m_Velocity.y *= -1;

	}

	else if (m_Position.x <= 0) {

		resetBall();
		this->rightScore = true;

	}

	else if (m_Position.x >= 800) {

		resetBall();
		this->leftScored = true;

	}

	return m_Position;

}

void Ball::resetBall() {

	m_Position.y = 300;
	m_Position.x = 400;

	this->m_Velocity = this->intialSpeed;
	this->m_Hits = 0;

}



void Ball::increaseSpeed() {

	currentSpeed.x += 10.0f;
	currentSpeed.y += 10.0f;

	++m_Hits;

}

int Ball::getHits() {

	return this->m_Hits;

}

std::vector <float> Ball::getBallVertices() {

	return ballVertices;

}

std::vector <unsigned int> Ball::getBallIndices() {

	return ballIndices;

}

glm::vec2 Ball::getCurrentSpeed() {

	return currentSpeed;
}