#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "util.h"
using namespace std;

unsigned int program;

float velocitySecondPointer = -6;
float velocityMinutePointer = -0.1;
float velocityHourPointer = -0.00417;

float currentSecondPointer = -188.4f;
float currentMinutePointer = -188.4f;
float currentHourPointer = -188.4f;

float lastTime = 0.0f;
float currentTime = 0.0f;
float deltaTime = 0.0f;

float speed = 1;

int main(void){
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 640, "Ground", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);


	GLenum err = glewInit();

	float vertices[] = {
		-1.0f,    1.0f,
		-1.0f,   -1.0f,
		 1.0f,   -1.0f,
		 1.0f,    1.0f
	};

	unsigned int position[] = {
		0, 1, 2, 0, 2, 3
	};

	unsigned int vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), vertices, GL_STATIC_DRAW);


	unsigned int indexBuffer;
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(int), position, GL_STATIC_DRAW);


	glEnableVertexAttribArray(0);       
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	program = glCreateProgram();

	string vertexString = readFile("vertex.vert");
	string fragmentString = readFile("fragment.frag");

	const char* vertexChar = vertexString.c_str();
	const char* fragmentChar = fragmentString.c_str();

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader, 1, &vertexChar, nullptr);
	glShaderSource(fragmentShader, 1, &fragmentChar, nullptr);

	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	GLint currentSecondPointerLoc = glGetUniformLocation(program, "currentSecondPointer");
	GLint currentMinutePointerLoc = glGetUniformLocation(program, "currentMinutePointer");
	GLint currentHourPointerLoc = glGetUniformLocation(program, "currentHourPointer");
	
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		currentTime = glfwGetTime();
		deltaTime = speed * (currentTime - lastTime);
		lastTime = currentTime;

		currentSecondPointer += deltaTime * velocitySecondPointer;
		currentMinutePointer += deltaTime * velocityMinutePointer;
		currentHourPointer += deltaTime * velocityHourPointer;

		//cout <<" currentSecondPointer" << currentSecondPointer << endl;
		//cout <<" currentMinutePointer" << currentMinutePointer << endl;
		//cout <<" currentHourPointer" << currentHourPointer << endl;

		glUniform1f(currentSecondPointerLoc, currentSecondPointer/120.0f);
		glUniform1f(currentMinutePointerLoc, currentMinutePointer / 120.0f);
		glUniform1f(currentHourPointerLoc, currentHourPointer / 120.0f);

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(program);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}