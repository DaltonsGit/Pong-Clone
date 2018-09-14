#include "Text.h"
#include <iostream>
#include "Textures.h"


Text::Text() {

	if (FT_Init_FreeType(&ft)) {

		std::cout << "ERROR: Could not initialize FreeType Library" << std::endl;

	}

	if (FT_New_Face(this->ft, "res/arial.ttf", 0, &face)) {

		std::cout << "ERROR: Failed to load font" << std::endl;

	}

	FT_Set_Pixel_Sizes(face, 0, 48);


}

void Text::generateCharacters(int character){
	
	


		if (FT_Load_Char(this->face, character, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			
		}

		else {

			size = glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
			bearing = glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top);
			advance = face->glyph->advance.x;
			generateTexture();

		}

}

void Text::generateTexture() {


	Textures tex;
	tex.wrap_S = GL_CLAMP_TO_EDGE;
	tex.wrap_T = GL_CLAMP_TO_EDGE;
	tex.filter_Min = GL_LINEAR;
	tex.filter_Max = GL_LINEAR;
	tex.generate(face->glyph->bitmap.width, face->glyph->bitmap.rows, face->glyph->bitmap.buffer, GL_RED, GL_RED);

	textureID = tex.programID;

}

glm::ivec2 Text::getSize()
{
	return size;
}

glm::ivec2 Text::getBearing()
{
	return bearing;
}

unsigned int Text::getAdvance()
{
	return advance;
}

unsigned int Text::getTextureID()
{
	return textureID;
}

FT_Face Text::getFace() {

	return this->face;

}

