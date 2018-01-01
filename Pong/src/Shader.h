#pragma once

#include <GL/glew.h>
#include <string>
#include <sstream>


struct ShaderProgramSource {

	std::string VertexSource;
	std::string FragmentSource;

};

class Shader {

private:
	unsigned int compileShader(unsigned int type, const std::string& source);
	void parseShader(const std::string& filepath);


public:

	unsigned int programID;
	std::stringstream source;

	Shader();
	//Shader(const Shader&);
	Shader(const char *shaderPath);
	//void loadShader(const std::string& vertexShader, const std::string& fragmentShader);
	void loadShader(std::string vShader, std::string fShader);
	~Shader();



	void copy(const Shader &copyShader);
	Shader(const Shader&) = default;
	Shader(Shader&&) = default;
	Shader& operator= (const Shader &equalShader);
	//Shader& operator=(const Shader&);


	void useShader();

	unsigned int getProgramID();

	 
};