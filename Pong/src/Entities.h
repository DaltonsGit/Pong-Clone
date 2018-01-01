#pragma once

#include <GL/glew.h>
#include <glm.hpp>

#include "Textures.h"
#include "Renderer.h"

class Entities{

public:

	glm::vec2 m_Position;
	glm::vec2 m_Size;
	glm::vec2 m_Velocity;
	

	glm::vec3 m_Color;

	float m_Rotation;

	Textures m_Tex;


	Entities();
	Entities(glm::vec2 position, glm::vec2 size, Textures tex, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
	
	virtual void draw(Renderer &renderer);
};