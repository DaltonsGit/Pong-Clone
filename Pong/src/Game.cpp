#include "Game.h"
#include <iostream>



Game::Game(unsigned int width, unsigned int height)
	: m_Width(width), m_Height(height){

}


//Sets up the game by loading the shaders/textures from file for the paddles/ball, and initalizing the players and ball objects.
void Game::setUpGame() {

	ResourceManager::loadShader("U:/Coding/C++/Real Pong/Pong/Pong/Pong/res/shaders/Basic.shader", "sprite");

	std::cout << "1" << std::endl;
	m_Renderer = new Renderer(ResourceManager::getShader("sprite"));
	std::cout << "2" << std::endl;

	glm::vec2 p1pos = glm::vec2(1, 275);
	glm::vec2 p2pos = glm::vec2(780, 275);

	ResourceManager::loadTexture("U:/Coding/C++/Real Pong/Pong/Pong/Pong/res/textures/awesome_face.jpg", GL_FALSE, "face");

	player1 = new Paddles(p1pos, player_Size, ResourceManager::getTexture("face"));
	player2 = new Paddles(p2pos, player_Size, ResourceManager::getTexture("face"));
	ball = new Ball(glm::vec2(this->m_Width / 2, this->m_Height / 2), glm::vec2(20, 20), glm::vec2(150,150), ResourceManager::getTexture("face"));


	std::cout << "ball position x: " << ball->m_Position.x << "paddle position x: " << player1->m_Position.x << std::endl <<
		"ball position y: " << ball->m_Position.y << "paddle position y: " << player1->m_Position.y <<  std::endl <<
		"ball size x: " << ball->m_Size.x << "paddle size x: " << player1->m_Size.x << std::endl <<
		"ball size y: " << ball->m_Size.y << "paddle size y: " << player1->m_Size.y << std::endl;

	std::cout << "Player2 actual size: " << player2->m_Position.x + player2->m_Size.x;

}





void Game::update(float dt) {

	if (firstRound == false) {

		ball->Move(dt, m_Height);

	}

	
	checkCollision();
	whoScored();


	ball->Move(dt, m_Height);

	
	
	
}

void Game::processInput(float dt) {

	float velociy = player_Velocity * dt;

	if (Keys[GLFW_KEY_W]) {

		player1->humanMovement(1, this->m_Height, dt);
	}

	else if (Keys[GLFW_KEY_S]) {

		player1->humanMovement(-1, this->m_Height, dt);
	}


	player2->aiMovement(this->ball->m_Position.y, dt);

	/*if (Keys[GLFW_KEY_W]) {
		if (player1->m_Position.y >= 0) {
			player1->m_Position.y -= velociy;
		}
	}
	else if (Keys[GLFW_KEY_S]) {
		if (player1->m_Position.y <= this->m_Height - player1->m_Size.y) {
			player1->m_Position.y += velociy;
		}
	}*/

}





void Game::render() {

	if (player2->m_Position.x <= ball->m_Position.x + ball->m_Size.x) {

		//std::cout << "paddle y: " << player2->m_Position.y << " ball y: " << ball->m_Position.y << std::endl;

	}

	//m_Renderer->drawEntity(ResourceManager::getTexture("face"), glm::vec2(200, 200), glm::vec2(300, 400), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	player1->draw(*m_Renderer);
	player2->draw(*m_Renderer);
	ball->draw(*m_Renderer);

}



void Game::checkCollision() {

	if (ball->m_Position.x + ball->m_Size.x >= player2->m_Position.x && (ball->m_Position.y + ball->m_Size.y >= player2->m_Position.y && ball->m_Position.y <= player2->m_Position.y + player2->m_Size.y)) {

		float centerPaddle = player2->m_Position.y + (player2->m_Size.y / 2);
		float distance = (ball->m_Position.y + ball->m_Size.y ) - centerPaddle;
		float percent = distance / (player2->m_Size.y / 2);


		float power = 2.0f;
		
		glm::vec2 oldVel = ball->m_Velocity;
		ball->m_Position = glm::vec2(player2->m_Position.x -player2->m_Size.x - 1.0, ball->m_Position.y);
		ball->m_Velocity.y = 100.0f * percent * power * player2->getDirection();
		ball->m_Velocity.x = abs(ball->m_Velocity.x) * -1;
		ball->m_Velocity = glm::normalize(ball->m_Velocity) * glm::length(oldVel);

		if (ball->getHits() < 5)
		{

			ball->increaseSpeed();

		}



	}

	else if (ball->m_Position.x <= player1->m_Position.x + player1->m_Size.x && (ball->m_Position.y + ball->m_Size.y >= player1->m_Position.y && ball->m_Position.y <= player1->m_Position.y + player1->m_Size.y)) {

		float centerPaddle = player1->m_Position.y + (player1->m_Size.y / 2);
		float distance = (ball->m_Position.y + ball->m_Size.y) - centerPaddle;
		float percent = distance / (player2->m_Size.y / 2);



		float power = 2.0f;
		glm::vec2 oldVel = ball->m_Velocity;
		ball->m_Position = glm::vec2(player1->m_Position.x + player1->m_Size.x + 1.0, ball->m_Position.y);
		ball->m_Velocity.y = 100.0f * percent * power * player1->getDirection();
		ball->m_Velocity.x = abs(ball->m_Velocity.x);
		ball->m_Velocity = glm::normalize(ball->m_Velocity) * glm::length(oldVel);

		if (ball->getHits() < 5)
		{

			ball->increaseSpeed();

		}

	}

}

void Game::whoScored() {

	if (ball->leftScored == true) {

		player1->increaseScore();
		ball->leftScored = false;

	}

	else if (ball->rightScore == true) {

		player2->increaseScore();
		ball->rightScore = false;

	}

	if (player1->getScore() == this->winnerScore || player2->getScore() == this->winnerScore) {

		this->gameOver = true;

	}

}

bool Game::getGameOver() {

	return this->gameOver;

}


Game::~Game() {

	delete m_Renderer;
	delete player1;
	delete player2;

}