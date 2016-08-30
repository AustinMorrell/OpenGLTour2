#include "Runit.h"

App::App()
{

}

float angle = 0.0f;

mat4 RotateAround(mat4 a, mat4 b, vec3 c)
{
	mat4 result;
	mat4 newPlanetPos = glm::translate(c);
	result = b * newPlanetPos * glm::rotate(angle, glm::vec3(0, 1, 0));
	return result;
}

int App::Start()
{
	if (glfwInit() == false)
	{
		return -1;
	}

	window = glfwCreateWindow(1280, 720, "OpenGLTour2", nullptr, nullptr);

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
	view = glm::lookAt(vec3(30, 30, 30), vec3(0), vec3(0, 1, 0));
	projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);

	// After checking, the rest of the code goes here.

	glClearColor(0.25f, 0.25f, 0.25f, 1);
	glEnable(GL_DEPTH_TEST); // enables the depth buffer

	mat4 sun = mat4(1);
	mat4 ven = mat4(1);
	mat4 moon = mat4(1);
	mat4 earth = mat4(1);

	mat4 rotation;
	rotation[0] = { 1,0,0,0 };
	rotation[1] = { 0,1,0,0 };
	rotation[2] = { 0,0,1,0 };
	rotation[3] = { 0,0,0,1 };

	const mat4* yaboi = &rotation;

	sun[3] = { 0,4,0,0 };
	ven[3] = { 5,4,0,0 };
	moon[3] = { 10,4,0,0 };
	earth[3] = { 15,4,0,0 };

	float speed = 1.0f;
	float theta = 0;
	float PI = 3.14f;

	return 1;
}

void App::Draw()
{
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
	Gizmos::addSphere(vec3(sun[3]), 3, 20, 20, vec4(1, 1, 0, 1), &sun);
	// The Venus
	Gizmos::addSphere(vec3(ven[3]), .7f, 20, 20, vec4(1, .498f, .313f, 1), &ven);
	// The Earth and Moon
	Gizmos::addSphere(vec3(earth[3]), 0.7f, 20, 20, vec4(0, 0, 1, 1), &earth);
	Gizmos::addSphere(vec3(moon[3]), 0.5f, 20, 20, vec4(.5f, .5f, 1, 1), &moon);

	Gizmos::draw(projection * view);
	glfwSwapBuffers(window);
	glfwPollEvents();
}

bool App::Update()
{
	while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		angle += .01f;
		mat4 sunrot = glm::rotate(angle, glm::vec3(0, 1, 0));
		sun = mat4(1) * sunrot;

		ven = RotateAround(ven, sun, vec3(5, 0, 0));
		earth = RotateAround(earth, sun, vec3(10, 0, 0));
		moon = RotateAround(moon, earth, vec3(2, 0, 0));
		return true;
	}
	return false;
}

void App::Stop()
{
	Gizmos::destroy();
	glfwDestroyWindow(window);
	glfwTerminate();
}