#include "Entities.h"

Entities::Entities()
	: m_Position(0,0), m_Size(1,1), m_Velocity(0.0f), m_Color(1.0f), m_Rotation(0.0f), m_Tex() {}

Entities::Entities(glm::vec2 position, glm::vec2 size, Textures tex, glm::vec3 color, glm::vec2 velocity)
	: m_Position(position), m_Size(size), m_Velocity(velocity), m_Color(color), m_Rotation(0.0f), m_Tex(tex) {}

void Entities::draw(Renderer &renderer, std::string VAOName) {

	renderer.drawEntity(this->m_Tex, this->m_Position, this->m_Size, this->m_Rotation, this->m_Color, VAOName);

}