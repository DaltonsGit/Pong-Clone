#include "Renderer.h"

#include <iostream>

#define GLM_ENABLE_EXPERIMENTAL
#include <gtx/string_cast.hpp>

std::map<std::string, unsigned int>       Renderer::m_quadVAO;

Renderer::Renderer() {}

Renderer::Renderer(const Renderer&) {}

Renderer::Renderer(Shader &shader) {

	m_Shader.programID = shader.getProgramID();

}

void Renderer::initRenderData(std::vector <float> vertices, std::vector <unsigned int> indices, std::string name) {

	unsigned int VAO;


	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);


	//Gives GPU data for the thing we want to draw.
	VertexBuffer vb(vertices, sizeof(vertices));


	//bind buffer
	IndexBuffer temp(indices, 6);


	//Layout of buffer (how to interpt data).
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
	glEnableVertexAttribArray(0);

	m_quadVAO[name] = VAO;

	vb.Unbind();
	glBindVertexArray(0);


}


void Renderer::updateShader(Shader &shader) {

	m_Shader.programID = shader.getProgramID();

}


void Renderer::drawText(std::map<char,Text> &characters, std::string word, glm::vec2 position, float scale, glm::vec3 color) {


	m_Shader.useShader();

	glActiveTexture(GL_TEXTURE0);

	unsigned int VAO;

	glGenVertexArrays(1, &VAO);

	VertexBuffer vb;

	glBindVertexArray(VAO);

	vb.Bind();


	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, 0);
	
	vb.Unbind();
	


	glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);

	int orth = glGetUniformLocation(m_Shader.getProgramID(), "projection2");
	glUniformMatrix4fv(orth, 1, GL_FALSE, glm::value_ptr(projection));


	int tex = glGetUniformLocation(m_Shader.getProgramID(), "textColor2");
	glUniform3f(tex, 0.5, 0.8f, 0.2f);


	for(int i = 0; i < word.length(); ++i) {


		Text temp = characters[word[i]];
		
		GLfloat x = position.x + temp.getBearing().x * scale;
		GLfloat y = position.y - (temp.getSize().y - temp.getBearing().y) * scale;

		GLfloat w = temp.getSize().x * scale;
		GLfloat h = temp.getSize().y * scale;

		std::vector <GLfloat> vertices = {

			x, y + h, 0.0f, 0.0f,
			x, y, 0.0f, 1.0f,
			x + w, y, 1.0f, 1.0f,

			x, y + h, 0.0f, 0.0f,
			x + w, y, 1.0f, 1.0f,
			x + w, y + h, 1.0f, 0.0f

		};

		glBindTexture(GL_TEXTURE_2D, temp.getTextureID());

		vb.Bind();
		vb.subData(vertices);

		vb.Unbind();

		glDrawArrays(GL_TRIANGLES, 0, 6);

		position.x += (temp.getAdvance() >> 6) * scale;

	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
		



}

void Renderer::drawEntity(Textures &texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color, std::string VAOName) {


	m_Shader.useShader();

	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(800),
		static_cast<GLfloat>(600), 0.0f, -1.0f, 1.0f);


	int orth = glGetUniformLocation(m_Shader.getProgramID(), "Projection");
	glUniformMatrix4fv(orth, 1, GL_FALSE, glm::value_ptr(projection));

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));


	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
	model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

	model = glm::scale(model, glm::vec3(size, 1.0f));

	int location = glGetUniformLocation(m_Shader.getProgramID(), "model");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(model));

	int colorLocation = glGetUniformLocation(m_Shader.getProgramID(), "u_color");
	glUniform3f(colorLocation, color.x, color.y, color.z);


	glActiveTexture(GL_TEXTURE0);
	texture.bind();

	glBindVertexArray(m_quadVAO[VAOName]);


	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);


}



Renderer::~Renderer() {

	
}