
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

vec4 RotateAround(vec3 a, vec3 b, vec3 c)
{
	vec3 finalPos = a - b;
	finalPos = c * finalPos;
	finalPos += b;
	vec4 result = vec4(finalPos.x, finalPos.y, finalPos.z, 0);
	/*cout << result.x << endl << result.y << endl << result.z << endl;*/
	return result;
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
	mat4 sun;
	mat4 ven;
	mat4 moon;
	mat4 earth;

	mat4 rotation;
	rotation[0] = { 1,0,0,0 };
	rotation[1] = { 0,1,0,0 };
	rotation[2] = { 0,0,1,0 };
	rotation[3] = { 0,0,0,1 };

	const mat4* yaboi = &rotation;
	//-----------------------------------------------------------------------------------------------------

	sun[0] = {0,4,0,0};
	ven[0] = { 5,4,0,0 };
	moon[0] = { 10,4,0,0 };
	earth[0] = { 15,4,0,0 };

	//-----------------------------------------------------------------------------------------------------
	float speed = 1.0f;
	float theta = 0;
	float PI = 3.14f;
	float angle = 0.0f;
	//-----------------------------------------------------------------------------------------------------
	while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		// Updates, logic, and render code starts here!
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Gizmos::clear();
		Gizmos::addTransform(glm::mat4(1));
		vec4 white(1);
		vec4 black(0, 0, 0, 1);

		for (int i = 0; i < 21; i++)
		{
			Gizmos::addLine(vec3(-10 + i, 0, 10), vec3(-10 + i, 0, -10), i == 10 ? white : black);
			Gizmos::addLine(vec3(10, 0, -10 + i), vec3(-10, 0, -10 + i), i == 10 ? white : black);
		}

		// The Sun
		Gizmos::addSphere(vec3(sun[0]), 3, 20, 20, vec4(1, 1, 0, 1), nullptr, 0.f, 360, -90, 90);
		// The Venus
		Gizmos::addSphere(vec3(ven[0]), .7f, 20, 20, vec4(1, .498f, .313f, 1), nullptr, 0.f, 360, -90, 90);
		// The Earth and Moon
		Gizmos::addSphere(vec3(earth[0]), 0.7f, 20, 20, vec4(0, 0, 1, 1), nullptr, 0.f, 360, -90, 90);
		Gizmos::addSphere(vec3(moon[0]), 0.5f, 20, 20, vec4(.5f, .5f, 1, 1), nullptr, 0.f, 360, -90, 90);
	
		Gizmos::draw(projection * view);

		angle += 0.01f;
		mat4 Spin = rotate(angle, vec3(0, 1, 0));
		sun = mat4(1) * Spin;

		ven[0] = RotateAround(vec3(ven[0]), vec3(sun[0]), vec3(1, 0, 0));

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