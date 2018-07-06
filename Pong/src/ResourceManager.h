#pragma once

#include "Game.h"
#include <map>
#include <fstream>
#include <string>
#include "Shader.h"
#include "Textures.h"
#include "stb_image.h"
#include "Text.h"

class ResourceManager {

public:
	static std::map<std::string, Shader> m_Shaders;
	static std::map<std::string, Textures> m_Textures;
	static std::map<char, Text>m_Characters;

	static void loadShader(const char *shaderFile, std::string name);
	static Shader getShader(std::string name);
	
	static void loadTexture(const char *texFile, bool alpha, std::string name);
	static Textures getTexture(std::string name);

	static void loadCharacters(bool alpha);
	static Text getCharacters(char letter);

	//static void clear();

private:
	ResourceManager () {}
	static Shader loadShaderFromFile(const char *shaderFile);
	static Textures loadTextureFromFile(const char *texFile, bool alpha);
	


};