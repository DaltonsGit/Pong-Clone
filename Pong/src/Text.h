#pragma once
#include <ft2build.h>
#include FT_FREETYPE_H

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Text 
{
public:
	Text();
    void generateCharacters(int characater);

	FT_Face getFace();

private:

	FT_Library ft;
	FT_Face face;

	unsigned int textureID;
	glm::ivec2 size;
	glm::ivec2 bearing;
	unsigned int advance;

};