#include "Game.h"
#include <iostream>
#include <gtc/reciprocal.hpp>



Game::Game(unsigned int width, unsigned int height)
	: m_Width(width), m_Height(height){

}


//Sets up the game by loading the shaders/textures from file for the paddles/ball, and initalizing the players and ball objects.
void Game::setUpGame() {

	ResourceManager::loadShader("res/shaders/Basic.shader", "sprite");
	ResourceManager::loadShader("res/shaders/Text.shader", "text");
	ResourceManager::loadTexture("res/textures/t1.jpg", GL_FALSE, "t1");
	ResourceManager::loadCharacters(true);


	glm::vec2 p1pos = glm::vec2(1, 275);
	glm::vec2 p2pos = glm::vec2(780, 275);

	player1 = new Paddles(p1pos, player_Size, ResourceManager::getTexture("t1"));
	player2 = new Paddles(p2pos, player_Size, ResourceManager::getTexture("t1"));
	ball = new Ball(glm::vec2(this->m_Width / 2, this->m_Height / 2), glm::vec2(20, 20), glm::vec2(400, 400), ResourceManager::getTexture("t1"));

	m_Renderer = new Renderer(ResourceManager::getShader("sprite"));
	m_Renderer->initRenderData(player1->getPaddleVertices(), player1->getPaddlesIndices(), "player1");
	m_Renderer->initRenderData(player2->getPaddleVertices(), player2->getPaddlesIndices(), "player2");
	m_Renderer->initRenderData(ball->getBallVertices(), ball->getBallIndices(), "ball");

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


	else if (Keys[GLFW_KEY_R]) {

		player1->resetScore();
		player2->resetScore();
		ball->resetBall();

	}

	player2->aiMovement(this->ball->m_Position.y, m_Height, dt);

}


void Game::render() {

	m_Renderer->updateShader(ResourceManager::getShader("sprite"));
	player1->draw(*m_Renderer, "player1");
	player2->draw(*m_Renderer, "player2");
	ball->draw(*m_Renderer, "ball");
	
	m_Renderer->updateShader(ResourceManager::getShader("text"));
	m_Renderer->drawText(ResourceManager::m_Characters, std::to_string(player1->getScore()), glm::vec2(275, 550), 0.75f, glm::vec3(1.0f, 1.0f, 1.0f));
	m_Renderer->drawText(ResourceManager::m_Characters, std::to_string(player2->getScore()), glm::vec2(500, 550), 0.75f, glm::vec3(1.0f, 1.0f, 1.0f));

	m_Renderer->drawText(ResourceManager::m_Characters, "Press R to reset game.", glm::vec2(1, 590), 0.25f, glm::vec3(1.0f, 1.0f, 1.0f));
	m_Renderer->drawText(ResourceManager::m_Characters, "Press Q to exit game.", glm::vec2(1, 575), 0.25f, glm::vec3(1.0f, 1.0f, 1.0f));

}



void Game::checkCollision() {


	if (ball->m_Position.x + ball->m_Size.x >= player2->m_Position.x && (ball->m_Position.y + ball->m_Size.y >= player2->m_Position.y && ball->m_Position.y <= player2->m_Position.y + player2->m_Size.y)) {

		if (ball->m_Velocity.x > 0) {

			//Calculates the center of the paddle, and where the ball hit the paddle relative to it. Then normalizes so that we can use the calculated angle to make the ball go off the paddle at different angles.
			//Could have just had the ball's x/y vel change between negative/positive after each hit, but after finding this solution, seemed like a more interesting choice. 

			float centerPaddle = player2->m_Position.y + (player2->m_Size.y / 2);
			float realtive = centerPaddle - ball->m_Position.y;

			float normalized = realtive / (player2->m_Size.y / 2);
			float percent = normalized * (glm::pi<float>() / 3);
			
	
			ball->m_Velocity.y = ball->getCurrentSpeed().y * glm::cos(percent);
			ball->m_Velocity.x = ball->getCurrentSpeed().x * -glm::sin(percent);

			//Used for quality of life to make the ball move to the other side quicker if its velocity in the x direction is too low. 
			if (ball->m_Velocity.x > -100.0f) {

				ball->m_Velocity.x = -200.0f;
			}
	

		}


	}

		else if (ball->m_Position.x <= player1->m_Position.x + player1->m_Size.x && (ball->m_Position.y + ball->m_Size.y >= player1->m_Position.y && ball->m_Position.y <= player1->m_Position.y + player1->m_Size.y)) {

			if (ball->m_Velocity.x < 0) {


				float centerPaddle = player1->m_Position.y + (player1->m_Size.y / 2);
				float realtive = centerPaddle - ball->m_Position.y;

				float normalized = realtive / (player1->m_Size.y / 2);
			
				float percent = normalized * (glm::pi<float>()  / 3);



				ball->m_Velocity.y = ball->getCurrentSpeed().y * glm::cos(percent);
				ball->m_Velocity.x = ball->getCurrentSpeed().x * -glm::sin(percent);


				if (ball->m_Velocity.x < 100.0f) {

					ball->m_Velocity.x = 200.0f;

				}
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

}





Game::~Game() {

	delete m_Renderer;
	delete player1;
	delete player2;
	delete ball;

}