#include "Game.h"
#include <iostream>



Game::Game(unsigned int width, unsigned int height)
	: m_Width(width), m_Height(height){

}

void Game::setUpGame() {

	ResourceManager::loadShader("D:/Programming/C++/Pong/Pong-Clone/Pong/res/shaders/Basic.shader", "sprite");

	std::cout << "1" << std::endl;
	m_Renderer = new Renderer(ResourceManager::getShader("sprite"));
	std::cout << "2" << std::endl;

	glm::vec2 p1pos = glm::vec2(1, 275);
	glm::vec2 p2pos = glm::vec2(780, 275);

	ResourceManager::loadTexture("D:/Programming/C++/Pong/Pong-Clone/Pong/res/textures/awesome_face.jpg", GL_FALSE, "face");

	player1 = new Paddles(p1pos, player_Size, ResourceManager::getTexture("face"));
	player2 = new Paddles(p2pos, player_Size, ResourceManager::getTexture("face"));
	ball = new Entities(glm::vec2(this->m_Width / 2, this->m_Height / 2), glm::vec2(20, 20), ResourceManager::getTexture("face"));


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

void Game::ballMovement(float dt) {

	float velociy = player_Velocity * dt;

	 float movement = 100.0f * dt * bd;

	if (ball->m_Position.y <= 0 || ball->m_Position.y >= this->m_Height) {

		
		movement *= -1.0f;

	}

	std::cout << bd << std::endl;
	std::cout << ball->m_Position.y << std::endl;

	ball->m_Position.y += movement;


}

void Game::aiMovement(float dt) {



}



void Game::render() {

	//m_Renderer->drawEntity(ResourceManager::getTexture("face"), glm::vec2(200, 200), glm::vec2(300, 400), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	player1->draw(*m_Renderer);
	player2->draw(*m_Renderer);
	ball->draw(*m_Renderer);
}

Game::~Game() {

	delete m_Renderer;
	delete player1;
	delete player2;

}