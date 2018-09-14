#pragma once
#include <ft2build.h>
#include FT_FREETYPE_H

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <vector>
#include "Textures.h"

class Text 
{
public:
	Text();
    void generateCharacters(int characater);
	void generateTexture();

	glm::ivec2 getSize();
	glm::ivec2 getBearing();
	unsigned int getAdvance();
	unsigned int getTextureID();

	FT_Face getFace();

private:

	FT_Library ft;
	FT_Face face;

	unsigned int textureID;
	glm::ivec2 size;
	glm::ivec2 bearing;
	unsigned int advance;

};