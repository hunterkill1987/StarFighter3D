#pragma once

#define GLEW_STATIC 
#pragma comment (lib, "glew32s.lib")


#include <Windows.h>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <random>

#include "gl/glew/include/glew.h"
#include "gl/glfw/include/glfw3.h"

#include "gl/glm/glm.hpp"
#include "gl/glm/gtc/matrix_transform.hpp"
#include "gl/glm/gtc/type_ptr.hpp"
#include "gl/glm/gtx/euler_angles.hpp"

#include <stdlib.h>
#include <stdio.h>

#include "EventManager.h"
#define WIDTH 800
#define HEIGHT 600

#define EPSILON 0.005

static const GLchar* vertexSource =

"#version 330 core \n"

"layout (location = 0) in vec3 position;\n"

"uniform mat4 model;"
"uniform mat4 projection;"

"void main()"
"{"
"	gl_Position = projection * model * vec4(position, 1.0f);"
"}";

static const GLchar* fragmentSource =
"#version 330 core \n"

"out vec4 color;"

"void main()"
"{"
"	color = vec4(1,1,1,1); "
"}";

class World;

class Engine
{

friend class Actor;

private:

	static Engine* Instance;

	std::random_device  random;

	Engine();

	float DeltaTime;

	float OldTime;

	float NewTime;

	EventManager* EventMgr;

public:

	float cameraAngleX;
	GLuint shaderProgram;
	GLFWwindow* window;

	World* CurrentWorld;

	static Engine* GetInstance();

	static void DeleteInstance(); 

	void Render();

	float GetDeltaTime() const;

	EventManager* GetEventManager() const;

	float RandToFloat(float a, float b);
	
	static bool IsNear(float A, float B, float Epsilon);


	template<typename T>T Clamp(const T& x,const T& min,const T& max)
	{
		if (x <= min)
		{
			return min;
		}
		else if (x >= max)
		{
			return max;
		}
		return x;
	}

	void Exit();
	~Engine();
};

