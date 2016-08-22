
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

vec3 Rotate()
{
	vec3 answer = vec3(0, 0, 0);



	return answer;
}

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
	mat4 view = glm::lookAt(vec3(30, 30, 30), vec3(0), vec3(0, 1, 0));
	mat4 projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);

	// After checking, the rest of the code goes here.

	glClearColor(0.25f, 0.25f, 0.25f, 1);
	glEnable(GL_DEPTH_TEST); // enables the depth buffer

	//-----------------------------------------------------------------------------------------------------
	vec3 sun = vec3(0, 3, 0);
	vec3 merc = vec3(0, 3, 3);
	vec3 ven = vec3(0, 3, 6);
	vec3 earth = vec3(0, 3, 9);
	vec3 mars = vec3(0, 3, 12);
	vec3 jupt = vec3(0, 3, 15);
	vec3 sat = vec3(0, 3, 18);
	vec3 uran = vec3(0, 3, 21);
	vec3 nept = vec3(0, 3, 24);
	vec3 plut = vec3(0, 3, 27);
	float speed = 1.0f;
	float theta = 0;
	float PI = 3.14f;
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
		Gizmos::addSphere(sun, 3, 50, 50, vec4(1, 1, 0, 1), nullptr, 0.f, 360, -90, 90);
		// The Mercury
		Gizmos::addSphere(merc, 0.5f, 50, 50, vec4(.5f, .5f, 1, 1), nullptr, 0.f, 360, -90, 90);
		// The Venus
		Gizmos::addSphere(ven, .7f, 50, 50, vec4(1, .498f, .313f, 1), nullptr, 0.f, 360, -90, 90);
		// The Earth and Moon
		Gizmos::addSphere(earth, 0.7f, 50, 50, vec4(0, 0, 1, 1), nullptr, 0.f, 360, -90, 90);
		/*Gizmos::addSphere(vec3(0, 3, 0), 0.007f, 50, 50, vec4(1, 1, 1, 1), nullptr, 0.f, 360, -90, 90);*/
		// The Mars
		Gizmos::addSphere(mars, 0.6f, 50, 50, vec4(1, 0, 0, 1), nullptr, 0.f, 360, -90, 90);
		// The Jupiter
		Gizmos::addSphere(jupt, 1.0f, 50, 50, vec4(.5f, 0, 0, 1), nullptr, 0.f, 360, -90, 90);
		// The Saturn
		Gizmos::addSphere(sat, 1.0f, 50, 50, vec4(1, .843f, 0, 1), nullptr, 0.f, 360, -90, 90);
		// The Uranus
		Gizmos::addSphere(uran, 0.9f, 50, 50, vec4(0, 1, 1, 1), nullptr, 0.f, 360, -90, 90);
		// The Neptune
		Gizmos::addSphere(nept, 0.9f, 50, 50, vec4(0, 0, .5f, 1), nullptr, 0.f, 360, -90, 90);
		// The Pluto
		Gizmos::addSphere(plut, 0.05f, 50, 50, vec4(1, 1, 1, 1), nullptr, 0.f, 360, -90, 90);
	
		Gizmos::draw(projection * view);

		if (theta < (2 * PI))
		{
			float x = speed * cos(theta),
				y = speed * sin(theta);
			merc = vec3(merc.x + x, merc.y + y, merc.z);
			ven = vec3(ven.x + x, ven.y + y, ven.z);
			earth = vec3(earth.x + x, earth.y + y, earth.z);
			mars = vec3(mars.x + x, mars.y + y, mars.z);
			jupt = vec3(jupt.x + x, jupt.y + y, jupt.z);
			sat = vec3(sat.x + x, sat.y + y, sat.z);
			uran = vec3(uran.x + x, uran.y + y, uran.z);
			nept = vec3(nept.x + x, nept.y + y, nept.z);
			plut = vec3(nept.x + x, plut.y + y, plut.z);

			theta += 0.1;
		}
		else
		{
			theta = 0;
		}

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