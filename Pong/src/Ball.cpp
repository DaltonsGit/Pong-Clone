#include "Ball.h"

#include <iostream>

Ball::Ball()
	: Entities() {}

Ball::Ball(glm::vec2 position, glm::vec2 size, glm::vec2 velocity, Textures sprite)
	: Entities(position, size, sprite, glm::vec3(1.0f), velocity) {

	this->intialSpeed = velocity;

}

glm::vec2 Ball::Move(float dt, unsigned int windowHeight) {


	//std::cout << this->ballVelocity;
	m_Position.y += m_Velocity.y * dt;
	m_Position.x += m_Velocity.x * dt;

	if (m_Position.y <= 0.0f) {


		m_Velocity.y *= -1;
		//m_Position.y = 0.0f;

	}

	else if (m_Position.y >= windowHeight) {

		m_Velocity.y *= -1;
		//m_Position.y = windowHeight;

	}

	else if (m_Position.x <= 0) {

		resetBall();
		this->rightScore = true;

	}

	else if (m_Position.x >= 800) {

		resetBall();
		this->leftScored = true;

	}


	 //this->ballVelocity;
	return m_Position;

}

void Ball::resetBall() {

	m_Position.y = 300;
	m_Position.x = 400;

	this->m_Velocity = this->intialSpeed;
	this->m_Hits = 0;

}



void Ball::increaseSpeed() {

	if (m_Velocity.x < 0.0f) {

		m_Velocity.x -= 10.0f;

	}

	else {

		m_Velocity.x += 10.0f;

	}

	if (m_Velocity.y < 0.0f) {

		m_Velocity.y -= 10.0f;

	}

	else {

		m_Velocity.y += 10.0f;

	}

	++m_Hits;

	std::cout << "ball velocity: " << this->m_Velocity.x << " " << this->m_Velocity.y;

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

/*void Ball::checkCollision(glm::vec2 objectLocation, glm::vec2 objectSize) {

	if(m_Position.y + m_Size.y)

}*/
