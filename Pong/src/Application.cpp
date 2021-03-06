//Gets all functions from gpu.
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Renderer.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Textures.h"




/*struct ShaderProgramSource {

	std::string VertexSource;
	std::string FragmentSource;

};


static ShaderProgramSource parseShader(const std::string& filepath) {

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


	return{ ss[0].str(), ss[1].str() };

}*/




int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	//glfwSwapInterval(1);


	if (glewInit() != GLEW_OK) {

		std::cout << "Error!" << std::endl;

	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	

	Shader shader("res/shaders/Basic.shader");

		//ShaderProgramSource source = parseShader("res/shaders/Basic.shader");
		//std::cout << source.VertexSource << std::endl;
		//::cout << source.FragmentSource << std::endl;

		

		//Shader shader(source.VertexSource, source.FragmentSource);
	shader.loadShader();


		int width; 
		int height;
		int nrChannels;

		unsigned char *data = stbi_load("res/textures/awesomeface.png", &width, &height, &nrChannels, 0);

			

		Textures wood;

		wood.generate(width, height, data);

		Renderer square(shader);
		Renderer square2(shader);




		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);


			square.drawEntity(wood, glm::vec2(774, 225), glm::vec2(25, 75), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			square2.drawEntity(wood, glm::vec2(0, 225), glm::vec2(25, 75), 0.0, glm::vec3(0.0f, 0.0f, 0.0f));

			
			
			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}

		//glDeleteProgram(shader);

	
	glfwTerminate();
	return 0;
}