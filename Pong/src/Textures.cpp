#include "Textures.h"
#include "Renderer.h"

Textures::Textures() 
	: m_Width(0), m_Height(0), internal_Format(GL_RGBA), image_Format(GL_RGBA), wrap_S(GL_REPEAT), wrap_T(GL_REPEAT), filter_Min(GL_LINEAR), filter_Max(GL_LINEAR){

	glGenTextures(1, &programID);

}

void Textures::generate(unsigned int width, unsigned int height, unsigned char* data, unsigned int intern, unsigned int image) {

	m_Width = width;
	m_Height = height;

	internal_Format = intern;
	image_Format = image;

	glBindTexture(GL_TEXTURE_2D, programID);
	glTexImage2D(GL_TEXTURE_2D, 0, internal_Format, width, height, 0, image_Format, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_S);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_T);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter_Min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter_Max);
	
	glBindTexture(GL_TEXTURE_2D, 0);

}

void Textures::bind() const {

	glBindTexture(GL_TEXTURE_2D, programID);

}