#include "ResourceManager.h"


#include <iostream>

std::map<std::string, Textures>    ResourceManager::m_Textures;
std::map<std::string, Shader>       ResourceManager::m_Shaders;

void ResourceManager::loadShader(const char *shaderFile, std::string name) {

	m_Shaders[name] = loadShaderFromFile(shaderFile);

}

Shader ResourceManager::getShader(std::string name) {

	Shader a;
	std::cout << a.programID << std::endl;
	std::cout << m_Shaders[name].programID << std::endl;
	a.copy(m_Shaders[name]);
	std::cout << a.programID << std::endl;
	return a;

	//return m_Shaders[name];

}

void ResourceManager::loadTexture(const char *textureFile, bool alpha, std::string name) {

	m_Textures[name] = loadTextureFromFile(textureFile, alpha);
	std::cout << "lmao" << std::endl;

}

Textures ResourceManager::getTexture(std::string name) {

	return m_Textures[name];
}


Shader ResourceManager::loadShaderFromFile(const char *shaderFile) {

	std::ifstream stream(shaderFile);

	enum class ShaderType {

		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1

	};


	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line)) {

		if (line.find("#shader") != std::string::npos) {

			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}

		else {

			ss[(int)type] << line << '\n';

		}
	}

	std::string vShader = ss[0].str();
	std::string fShader = ss[1].str();

	Shader shader;
	shader.loadShader(vShader, fShader);

	return shader;



}

Textures ResourceManager::loadTextureFromFile(const char *texFile, bool alpha) {

	Textures texture;
	if (alpha == true) {

		texture.internal_Format = GL_RGBA;
		texture.image_Format = GL_RGBA;

	}

	std::cout << "Tex made 1" << std::endl;

	int width;
	int height;
	int nrChannels;

	unsigned char *data = stbi_load(texFile, &width, &height, &nrChannels, 0);

	std::cout << "Tex made 2" << std::endl;

	texture.generate(width, height, data);

	std::cout << "Tex made 3" << std::endl;

	stbi_image_free(data);

	std::cout << "lol" << std::endl;

	return texture;


}

