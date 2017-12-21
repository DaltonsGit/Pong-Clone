#pragma once

#include <string>


struct ShaderProgramSource {

	std::string VertexSource;
	std::string FragmentSource;

};

class Shader {

private:
	unsigned int compileShader(unsigned int type, const std::string& source);
	ShaderProgramSource parseShader(const std::string& filepath);


public:
	unsigned int programID;
	ShaderProgramSource source;

	Shader();
	Shader(const char *shaderPath);
	//void loadShader(const std::string& vertexShader, const std::string& fragmentShader);
	void loadShader();
	~Shader();


	void useShader();

	unsigned int getProgramID();

	 
};