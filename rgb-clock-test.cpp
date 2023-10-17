#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "util.h"
using namespace std;

unsigned int program;
GLint color1Loc;
GLint color2Loc;
GLint color3Loc;

float velocitySecondPointer = -6.0f / 2;  // 360 derajat / 60 detik  
float velocityMinutePointer = -0.1f / 2; // 360 derajat / 3600 detik
float velocityHourPointer = -0.00834f / 2; // 360 derajat / 86 400 detik * 2

float currentSecondPointer = 270.0f;   
float currentMinutePointer = 270.0f;
float currentHourPointer = 270.0f;

float lastTime = 0.0f;
float currentTime = 0.0f;
float deltaTime = 0.0f;

float speed = 1;
float color1[] = { 1.0, 0.0, 0.0, 1.0 };
float color2[] = { 0.0, 1.0, 0.0, 1.0 };
float color3[] = { 0.0, 0.0, 1.0, 1.0 };

void buttonFunction(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
		speed *= 2;
		cout << "key up pressed, speed = " << speed << endl;
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
		speed /= 2;
		cout << "key down pressed, speed = " << speed << endl;
	}
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		speed = 1;
		cout << "key Space pressed, speed = " << speed << endl;
	}
	if (key == GLFW_KEY_C && action == GLFW_PRESS) {
		for (int i = 0; i < 4; i++)
		{
			color1[i] = (rand() * 1.0f) / RAND_MAX;
			color2[i] = (rand() * 1.0f) / RAND_MAX;
			color3[i] = (rand() * 1.0f) / RAND_MAX;
		}
		glProgramUniform4f(program, color1Loc, color1[0], color1[1], color1[2], color1[3]);
		glProgramUniform4f(program, color2Loc, color2[0], color2[1], color2[2], color2[3]);
		glProgramUniform4f(program, color3Loc, color3[0], color3[1], color3[2], color3[3]);
		cout << "key C pressed, Color Change "<< endl;
	}
	if (key == GLFW_KEY_L && action == GLFW_PRESS) {
		glfwSetTime(currentTime + 3600);
		cout << "key L pressed, Fast Forwarding 1 Hour" << endl;
	}
	if (key == GLFW_KEY_J && action == GLFW_PRESS) {
		glfwSetTime(currentTime - 3600);
		cout << "key J pressed, Rewinding 1 Hour" << endl;
	}
	if (key == GLFW_KEY_I && action == GLFW_PRESS) {
		glfwSetTime(currentTime + 300);
		cout << "key I pressed, Fast Forwarding 5 Minutes" << endl;
	}
	if (key == GLFW_KEY_K && action == GLFW_PRESS) {
		glfwSetTime(currentTime - 300);
		cout << "key K pressed, Rewinding 5 Minutes" << endl;
	}
	if (key == GLFW_KEY_X && action == GLFW_PRESS) {
		float jam, menit;
		cout << "Jam : "; cin >> jam;
		cout << endl;

		cout << "Menit : "; cin >> menit;
		cout << endl;

		float hourInSecond = jam * 3600;
		float minuteInSecond = menit * 60;

		glfwSetTime(hourInSecond + minuteInSecond);
		cout << "Time Changed Successfully" << endl;
	}
}

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
	glfwSetKeyCallback(window, buttonFunction);

	GLenum err = glewInit();

	float vertices[] = {
		-1.0f,    1.0f,
		-1.0f,   -1.0f,
		 1.0f,   -1.0f,
		 1.0f,    1.0f
	};

	unsigned int position[] = {
		0, 1, 2, 
		0, 2, 3,
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

	color1Loc = glGetUniformLocation(program, "color1");
	glProgramUniform4f(program, color1Loc, color1[0], color1[1], color1[2], color1[3]);

	color2Loc = glGetUniformLocation(program, "color2");
	glProgramUniform4f(program, color2Loc, color2[0], color2[1], color2[2], color2[3]);

	color3Loc = glGetUniformLocation(program, "color3");
	glProgramUniform4f(program, color3Loc, color3[0], color3[1], color3[2], color3[3]);
	
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		currentTime = glfwGetTime();
		deltaTime = speed * (currentTime - lastTime);
		lastTime = currentTime;

		currentSecondPointer = currentSecondPointer +  (deltaTime * velocitySecondPointer);
		currentMinutePointer += deltaTime * velocityMinutePointer;
		currentHourPointer += deltaTime * velocityHourPointer;

		//cout <<" currentSecondPointer" << currentSecondPointer << endl;
		//cout <<" currentMinutePointer" << currentMinutePointer << endl;
		//cout <<" currentHourPointer" << currentHourPointer << endl;

		glUniform1f(currentSecondPointerLoc, currentSecondPointer * 3.14159265f / 180.0f );
		glUniform1f(currentMinutePointerLoc, currentMinutePointer * 3.14159265f / 180.0f);
		glUniform1f(currentHourPointerLoc, currentHourPointer * 3.14159265f / 180.0f);

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