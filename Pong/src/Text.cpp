#include "Text.h"
#include <iostream>
#include "Textures.h"


Text::Text() {

	if (FT_Init_FreeType(&ft)) {

		std::cout << "ERROR: Could not initialize FreeType Library" << std::endl;

	}

	if (FT_New_Face(this->ft, "fonts/arial.ttf", 0, &face)) {

		std::cout << "ERROR: Failed to load font" << std::endl;

	}

	FT_Set_Pixel_Sizes(this->face, 0, 48);


}

void Text::generateCharacters(int character){
	
	

		if (FT_Load_Char(this->face, character, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			
		}

		else {

			Textures tex;
			tex.generate(face->glyph->bitmap.width, face->glyph->bitmap.rows, face->glyph->bitmap.buffer);

			textureID = tex.programID;
			size = glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
			bearing = glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top);
			advance = face->glyph->advance.x;

		}




}

FT_Face Text::getFace() {

	return this->face;

}

