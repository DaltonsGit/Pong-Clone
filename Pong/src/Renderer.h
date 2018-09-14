#pragma once

#include <GL/glew.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


#include "Shader.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "Textures.h"
#include "Text.h"

#include <map>
#include <vector>

class Renderer {

public:
	Renderer();
	Renderer(Shader &shader);
	Renderer(const Renderer&);
	~Renderer();

	void drawEntity(Textures &textures, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color, std::string VAOName);

	void initRenderData(std::vector <float> vertices, std::vector <unsigned int> indices, std::string name);

	void updateShader(Shader &shader);

	void drawText(std::map<char,Text> &character, std::string word, glm::vec2 position, float scale, glm::vec3 color);


private:
	Shader m_Shader;

	static std::map<std::string, unsigned int> m_quadVAO;

};

