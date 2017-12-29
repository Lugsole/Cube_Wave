#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <GL/glew.h>
#include <glfw3.h>
GLFWwindow* window;

#include <glm/glm.hpp>
using namespace glm;
using namespace std; // Including the C++ Standard Library.




double M_PI = 3.1415926;
/*Ripple*/
float function1(float x, float y, float s)
{
	return sin(sqrt(x * x + y * y) * M_PI * 2 + s * -M_PI) / 4 + .5;
}

static void error_callback(int error, const char *description)
{
	fputs(description, stderr);
}

int function_num = 1;

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
{
	cout << endl
		<< "Mouse Position: (" << xpos << "," << ypos << ")" << endl;
}

float function(float x, float y)
{
	return sin(sqrt(x * x + y * y) * M_PI * 2 + glfwGetTime() * -M_PI / 4);
}

int main(void)
{
	GLFWwindow *window;
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		exit(EXIT_FAILURE);

	/* Get window from the primary monitor */
	const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	int WIDTH = mode->width;
	int HEIGHT = mode->height;
	/* Create a window on the primary monitor, screen size, and with a name of "My example" */
	window = glfwCreateWindow(WIDTH, HEIGHT, "My example", glfwGetPrimaryMonitor(), NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	/*  */
	glfwMakeContextCurrent(window);

	/* Tell where to send key events */
	glfwSetKeyCallback(window, key_callback);

	glfwSetCursorPosCallback(window, cursor_position_callback);

	/* Make cursor hidden */
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	/* define the projection transformation */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float scale_w = ((float)WIDTH / HEIGHT);
	glOrtho(-scale_w * 1.1, scale_w * 1.1, -1.0 * 1.1, 1.0 * 1.1, -2.0, 20.0);

	/* define the viewing transformation */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	/* Set the graph scale */
	float increment = .1;
	double last_time = 0;

	/* Create hexagon */
	float Pos_X = 1;
	float Pos_Y = 1;
	float* list;
	while (!glfwWindowShouldClose(window))
	{
		/* get the current time */
		double now = glfwGetTime();
		float ratio;

		glMatrixMode(GL_MODELVIEW);

		/* Clear screen */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/* Set to draw lines */
		glBegin(GL_LINES);
		/* Draw Red line */
		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(0.f, 0.f, 0.f);
		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(1.f, 0.f, 0.f);

		/* Draw Green line */
		glColor3f(0.f, 1.f, 0.f);
		glVertex3f(0.f, 0.f, 0.f);
		glColor3f(0.f, 1.f, 0.f);
		glVertex3f(0.f, 1.f, 0.f);

		/* Draw Blue line */
		glColor3f(0.f, 0.f, 1.f);
		glVertex3f(0.f, 0.f, 0.f);
		glColor3f(0.f, 0.f, 1.f);
		glVertex3f(0.f, 0.f, 1.f);

		/* Change color to wight */
		glColor3f(1.f, 1.f, 1.f);
		glEnd();
		glBegin(GL_TRIANGLES);
		for (float x = -1; x < 1; x += increment)
			for (float y = -1; y < 1; y += increment) {
				float H_I = increment / 2;
				float z = function1(x + H_I, y + H_I, now);
				/* set color */
				glColor4f(.5, .733, .70, 1);
				/* draw triangle */
				glVertex3f(x, z, y);
				glVertex3f(x + increment, z, y);
				glVertex3f(x, z, y + increment);
				/* draw triangle */
				glVertex3f(x + increment, z, y);
				glVertex3f(x, z, y + increment);
				glVertex3f(x + increment, z, y + increment);
				/* set color */
				glColor4f(.9, .89, .70, 1);
				/* draw triangle */
				glVertex3f(x + increment, z, y);
				glVertex3f(x + increment, -z, y);
				glVertex3f(x + increment, z, y + increment);
				/* draw triangle */
				glVertex3f(x + increment, z, y + increment);
				glVertex3f(x + increment, -z, y);
				glVertex3f(x + increment, -z, y + increment);
				/* set color */
				glColor4f(.25, .33, .52, 1);
				/* draw triangle */
				glVertex3f(x, z, y + increment);
				glVertex3f(x, -z, y + increment);
				glVertex3f(x + increment, z, y + increment);
				/* draw triangle */
				glVertex3f(x + increment, z, y + increment);
				glVertex3f(x, -z, y + increment);
				glVertex3f(x + increment, -z, y + increment);
			}
		glEnd();

		/* define the projection transformation */
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		float scale_w = ((float)WIDTH / HEIGHT);

		float distance = 1.5f;
		glOrtho(-scale_w * distance, scale_w * distance, -1.0 * distance, 1.0 * distance, -2.0, 20.0);

		/* define the viewing transformation */
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(distance, distance, distance, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);



		/* Draw to screen */
		glfwSwapBuffers(window);

		/* Receive window events */
		glfwPollEvents();
		/* print the FPS */
		cout << 1 / (now - last_time) << ",";
		last_time = now;
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
