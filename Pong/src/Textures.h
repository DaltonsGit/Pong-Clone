#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>



class Textures
{
public:
	unsigned int programID;

	unsigned int m_Width;
	unsigned int m_Height;

	unsigned int internal_Format;
	unsigned int image_Format;

	unsigned int wrap_S;
	unsigned int wrap_T;
	unsigned int filter_Min;
	unsigned int filter_Max;

	Textures();

	void generate(unsigned int width, unsigned int height, unsigned char *date);

	void bind() const;

};
