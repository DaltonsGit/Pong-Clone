#pragma once

#include <GL/glew.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


#include "Shader.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "Textures.h"
#include <map>
#include <vector>



#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError(); 

bool GLLogCall(const char* function, const char* file, int line); 

class Renderer {

public:
	Renderer();
	Renderer(Shader &shader);
	Renderer(const Renderer&);
	~Renderer();

	void drawEntity(Textures &textures, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color, std::string VAOName);

	void initRenderData(std::vector <float> vertices, std::vector <unsigned int> indices, std::string name);

private:
	Shader m_Shader;
	//unsigned int m_quadVAO;

	//void initRenderData();
	static std::map<std::string, unsigned int> m_quadVAO;

};

