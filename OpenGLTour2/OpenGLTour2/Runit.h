#pragma once
#include "gl_core_4_4.h"
#include <GLFW/glfw3.h>
#include <iostream>
#define GLM_SWIZZLE
#define GLM_FORCE_PURE
#include "Gizmos.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;

class Runit
{
public:
	virtual int Start() = 0;
	virtual bool Update() = 0;
	virtual void Draw() = 0;
	virtual void Stop() = 0;
};

class App : public Runit
{
public:
	App();
	int Start() override;
	bool Update() override;
	void Draw() override;
	void Stop() override;

private:
	mat4 sun;
	mat4 ven;
	mat4 moon;
	mat4 earth;

	mat4 view;
	mat4 projection;

	GLFWwindow* window;
};