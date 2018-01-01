#include "Renderer.h"

#include <iostream>

#define GLM_ENABLE_EXPERIMENTAL
#include <gtx/string_cast.hpp>

void GLClearError() {

	while (glGetError() != GL_NO_ERROR);

}

bool GLLogCall(const char* function, const char* file, int line) {

	while (GLenum error = glGetError()) {

		std::cout << "[OpenGl Error] (" << error << ")" << function
			<< " " << file << ":" << line << std::endl;
		return false;

	}
	return true;
}

Renderer::Renderer() {
	
	std::cout << "made it lol" << std::endl;

}

Renderer::Renderer(const Renderer&) {

	std::cout << "dask" << std::endl;
}

Renderer::Renderer(Shader &shader) {

	this->m_Shader = shader;
	this->initRenderData();

}

void Renderer::initRenderData() {


	float vertices[] = {
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		//0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f
		//1.0f, 0.0f, 1.0f, 0.0f
	};

	unsigned int indices[] = {
		0, 1, 2,
		1, 3, 0

	};

	
	GLCall(glGenVertexArrays(1, &m_quadVAO));
	GLCall(glBindVertexArray(m_quadVAO));


	//Gives GPU data for the thing we want to draw.
	
	//VertexBuffer vb(vertices, 3 * 2 * sizeof(float));
	VertexBuffer vb(vertices, sizeof(vertices));


	//bind buffer
	GLCall(IndexBuffer temp(indices, 6));


	//Layout of buffer (how to interpt data).
	
	GLCall(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0));
	GLCall(glEnableVertexAttribArray(0));


	vb.Unbind();
	glBindVertexArray(0);

	



}

void Renderer::drawEntity(Textures &texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color ) {


	m_Shader.useShader();

	GLCall(glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(800),
		static_cast<GLfloat>(600), 0.0f, -1.0f, 1.0f));


	int orth = glGetUniformLocation(m_Shader.getProgramID(), "Projection");
	GLCall(glUniformMatrix4fv(orth, 1, GL_FALSE, glm::value_ptr(projection)));

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));


	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
	model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

	model = glm::scale(model, glm::vec3(size, 1.0f));

	int location = glGetUniformLocation(m_Shader.getProgramID(), "model");
	GLCall(glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(model)));

	int colorLocation = glGetUniformLocation(m_Shader.getProgramID(), "u_color");
	GLCall(glUniform3f(colorLocation, color.x, color.y, color.z));


	glActiveTexture(GL_TEXTURE0);
	texture.bind();

	GLCall(glBindVertexArray(m_quadVAO));
	//m_ebo.Bind();

	GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
	//GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
	GLCall(glBindVertexArray(0));


}



Renderer::~Renderer() {

	glDeleteVertexArrays(1, &m_quadVAO);

}