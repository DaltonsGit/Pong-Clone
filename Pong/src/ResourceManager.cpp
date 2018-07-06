#include "ResourceManager.h"


#include <iostream>

std::map<std::string, Textures>    ResourceManager::m_Textures;
std::map<std::string, Shader>       ResourceManager::m_Shaders;

//Stores each shader location into memory.
void ResourceManager::loadShader(const char *shaderFile, std::string name) {

	m_Shaders[name] = loadShaderFromFile(shaderFile);

}

//Retreives the shader specified from memory.
Shader ResourceManager::getShader(std::string name) {

	Shader a;
	std::cout << a.programID << std::endl;
	std::cout << m_Shaders[name].programID << std::endl;
	//Copies the shader being retrived.
	a.copy(m_Shaders[name]);
	std::cout << a.programID << std::endl;

	return a;
	
	//return m_Shaders[name];
	
}

//Stores each texture location into memory.
void ResourceManager::loadTexture(const char *textureFile, bool alpha, std::string name) {


		m_Textures[name] = loadTextureFromFile(textureFile, alpha);

}

//Retrives the texture specified from memory
Textures ResourceManager::getTexture(std::string name) {

	return m_Textures[name];
}


void ResourceManager::loadCharacters(bool alpha) {

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for (int i = 0; i < 128; ++i) {

		Text x;

		x.generateCharacters(i);
		m_Characters[i] = x;
	}

	
}


//Retrives each shader from the shader file at the specified location and generates a shader object.
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

		//If #shader does not equal to not found (aka #shader is in the file)
		if (line.find("#shader") != std::string::npos) {

			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}

		//Stores shader data for each shader type based on what the type variable currently equals.
		else {

			ss[(int)type] << line << '\n';

		}
	}

	std::string vShader = ss[0].str();
	std::string fShader = ss[1].str();

	//Generates shader.
	Shader shader;
	shader.loadShader(vShader, fShader);

	return shader;



}

//Retrives the texture from a texture file at the specified location and generates a texture object.
Textures ResourceManager::loadTextureFromFile(const char *texFile, bool alpha) {

	Textures texture;

	if (alpha == true) {

		texture.internal_Format = GL_RGBA;
		texture.image_Format = GL_RGBA;

	}

	int width;
	int height;
	int nrChannels;

	unsigned char *data = stbi_load(texFile, &width, &height, &nrChannels, 0);


	texture.generate(width, height, data);

	stbi_image_free(data);

	return texture;


}


