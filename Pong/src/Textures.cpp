#include "Textures.h"
#include "Renderer.h"

Textures::Textures() 
	: m_Width(0), m_Height(0), internal_Format(GL_RGB), image_Format(GL_RGB), wrap_S(GL_REPEAT), wrap_T(GL_REPEAT), filter_Min(GL_LINEAR), filter_Max(GL_LINEAR){

	glGenTextures(1, &programID);

}

void Textures::generate(unsigned int width, unsigned int height, unsigned char* data) {

	m_Width = width;
	m_Height = height;

	GLCall(glBindTexture(GL_TEXTURE_2D, programID));
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, internal_Format, width, height, 0, image_Format, GL_UNSIGNED_BYTE, data));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_S));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_T));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter_Min));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter_Max));
	
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

}

void Textures::bind() const {

	GLCall(glBindTexture(GL_TEXTURE_2D, programID));

}