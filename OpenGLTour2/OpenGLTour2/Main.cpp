
#include "gl_core_4_4.h"
#include <GLFW/glfw3.h>
#include <iostream>
#define GLM_SWIZZLE
#define GLM_FORCE_PURE
#include "Gizmos.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "ObjectOriented.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;
using namespace std;

int main()
{
	if (glfwInit() == false)
	{
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(1280, 720, "OpenGLTour2", nullptr, nullptr);

	if (window == nullptr)
	{
		glfwTerminate();
		return -2;
	}

	glfwMakeContextCurrent(window);

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return -3;
	}

	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();
	printf("GL: %i.%i\n", major, minor);

	Gizmos::create();
	mat4 view = glm::lookAt(vec3(520, 520, 520), vec3(0), vec3(0, 1, 0));
	mat4 projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);

	// After checking, the rest of the code goes here.

	glClearColor(0.25f, 0.25f, 0.25f, 1);
	glEnable(GL_DEPTH_TEST); // enables the depth buffer


	/*static ObjectOriented Hierarchy[];*/
	//-----------------------------------------------------------------------------------------------------
	while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		// Updates, logic, and render code starts here!
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Gizmos::clear();
		Gizmos::addTransform(glm::mat4(1));
		vec4 white(1);
		vec4 black(0, 0, 0, 1);

		/*for (int i = 0; i < 21; i++)
		{
			Gizmos::addLine(vec3(-10 + i, 0, 10), vec3(-10 + i, 0, -10), i == 10 ? white : black);
			Gizmos::addLine(vec3(10, 0, -10 + i), vec3(-10, 0, -10 + i), i == 10 ? white : black);
		}*/

		// The Sun
		Gizmos::addSphere(vec3(0, 3, 0), 3, 50, 50, vec4(1, 1, 1, 1), nullptr, 0.f, 360, -90, 90);
		// The Mercury
		Gizmos::addSphere(vec3(0, 3, 5), 0.011f, 50, 50, vec4(1, 1, 1, 1), nullptr, 0.f, 360, -90, 90);
		// The Venus
		Gizmos::addSphere(vec3(0, 3, 9.3f), 0.026f, 50, 50, vec4(1, 1, 1, 1), nullptr, 0.f, 360, -90, 90);
		// The Earth and Moon
		Gizmos::addSphere(vec3(0, 3, 12.9f), 0.028f, 50, 50, vec4(1, 1, 1, 1), nullptr, 0.f, 360, -90, 90);
		/*Gizmos::addSphere(vec3(0, 3, 0), 0.007f, 50, 50, vec4(1, 1, 1, 1), nullptr, 0.f, 360, -90, 90);*/
		// The Mars
		Gizmos::addSphere(vec3(0, 3, 19.7f), 0.015, 50, 50, vec4(1, 1, 1, 1), nullptr, 0.f, 360, -90, 90);
		// The Jupiter
		Gizmos::addSphere(vec3(0, 3, 67.2f), 0.3, 50, 50, vec4(1, 1, 1, 1), nullptr, 0.f, 360, -90, 90);
		// The Saturn
		Gizmos::addSphere(vec3(0, 3, 123.2f), 0.26, 50, 50, vec4(1, 1, 1, 1), nullptr, 0.f, 360, -90, 90);
		// The Uranus
		Gizmos::addSphere(vec3(0, 3, 247.9f), 0.11, 50, 50, vec4(1, 1, 1, 1), nullptr, 0.f, 360, -90, 90);
		// The Neptune
		Gizmos::addSphere(vec3(0, 3, 388.3f), 0.11, 50, 50, vec4(1, 1, 1, 1), nullptr, 0.f, 360, -90, 90);
		// The Pluto
		Gizmos::addSphere(vec3(0, 3, 510.6f), 0.005, 50, 50, vec4(1, 1, 1, 1), nullptr, 0.f, 360, -90, 90);
	
		Gizmos::draw(projection * view);

		/*if (mouse_event(mous))*/

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//-----------------------------------------------------------------------------------------------------

	Gizmos::destroy();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}