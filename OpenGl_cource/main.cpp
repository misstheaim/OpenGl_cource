#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "shader_s.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

//const char* vertexShaderSource = "#version 330 core\n"
//	"layout (location = 0) in vec3 aPos;\n"
//	"layout (location = 1) in vec3 aColor;"
//	"out vec3 ourColor;"
//	"void main()\n"
//	"{\n"
//	"   gl_Position = vec4(aPos, 1.0f);\n"
//	"	ourColor = aColor;"
//	"}\0";
//const char* fragmentShaderSource = "#version 330 core\n"
//	"out vec4 FragColor;\n"
//	"in vec3 ourColor;"
//	"void main()\n"
//	"{\n"
//	"	FragColor = vec4 (ourColor, 1.0f);//vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//	"}\0";

int main() {


	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



	GLFWwindow* window = glfwCreateWindow(800, 600, "LearOpenGl", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}


	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	//Creating Shaders
	/*unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);*/
	Shader ourShader("vertex.vs", "fragment.fs");
	//---------------


	// Creating a buffer of vertices
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f
	};
	unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3
	};

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO); //Do this before Buffers binding and setting attributes

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	//-----------

	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.1f, 0.7f, 0.7f, 0);
		glClear(GL_COLOR_BUFFER_BIT);

		/*float timeValue = glfwGetTime();
		float greenValue = sin(timeValue / 2.0f) + 0.5f;
		int ourColorLocation = glGetUniformLocation(shaderProgram, "ourColor");*/

		//glUseProgram(shaderProgram);
		ourShader.use();
		//glUniform4f(ourColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		glBindVertexArray(VAO);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		//glDrawArrays(GL_TRIANGLES, 0, 3);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	//glDeleteProgram(shaderProgram);




	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

