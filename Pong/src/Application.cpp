//Gets all functions from gpu.
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <iostream>

#include "Renderer.h"
#include "Game.h"



void key_CallBack(GLFWwindow *window, int key, int scancode, int action, int mode);


Game game(800, 600);

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

	glfwSetKeyCallback(window, key_CallBack);


	if (glewInit() != GLEW_OK) {

		std::cout << "Error!" << std::endl;

	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	game.setUpGame();
	std::cout << "Finished setup" << std::endl;

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		float timeChange = 0.0f;
		float lastFrame = 0.0f;

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_Q) != GLFW_PRESS)
		{


			float currentFrame = glfwGetTime();
			timeChange = currentFrame - lastFrame;
			lastFrame = currentFrame;

			glfwPollEvents();

			game.processInput(timeChange);
			game.update(timeChange);
		
			/* Render here */
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			game.render();

			
			
			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}


	
	glfwTerminate();
	return 0;
}



void key_CallBack(GLFWwindow * window, int key, int scancode, int action, int mode) {

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	
	if (key >= 0 && key < 1024) {

		if (action == GLFW_PRESS) {
			game.Keys[key] = GL_TRUE;
		}
		else if (action == GLFW_RELEASE) {
			game.Keys[key] = GL_FALSE;
		}
	}

}