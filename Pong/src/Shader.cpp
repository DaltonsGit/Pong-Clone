#include "Shader.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Renderer.h"

Shader::Shader(){}

Shader::Shader(const char *shaderPath) {

	parseShader("Pong-Clone/Pong/res/shaders/Basic.shader");

}


void Shader::loadShader(std::string vShader, std::string fShader) {


	programID = glCreateProgram();
	unsigned int vs = compileShader(GL_VERTEX_SHADER, vShader);


	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fShader);


	glAttachShader(programID, vs);
	glAttachShader(programID, fs);
	glLinkProgram(programID);

	
	glValidateProgram(programID);

	glDeleteShader(vs);
	glDeleteShader(fs);

}

Shader::~Shader() {

}




 unsigned int Shader::compileShader(unsigned int type, const std::string& source) {

	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);



	std::cout << src << std::endl;


	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE) {

		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile" <<
			(type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
		std::cout << message << std::endl;

		glDeleteShader(id);
		return 0;
	}


	return id;
}

void Shader::parseShader(const std::string& filepath) {

	 std::ifstream stream(filepath);

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

 }



 void Shader::useShader() {

	 glUseProgram(programID);

 }

 unsigned int Shader::getProgramID() {

	 return programID;

 }

 void Shader::copy(const Shader &copyShader){

	 this->programID = copyShader.programID;



 }

 Shader& Shader::operator= (const Shader &equalShader) {

	 this->programID = equalShader.programID;

	 return *this;

 }



