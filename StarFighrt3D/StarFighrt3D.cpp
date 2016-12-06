// StarFighrt3D.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Engine.h"
#include "World.h"

// TODO:: Test Only
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main()
{
	Engine* GEngine = Engine::GetInstance();

	World* GWorld = World::GetInstance();

	if (GWorld != nullptr && GEngine != nullptr)
	{
		GWorld->Init(GEngine);
	}

// TODO:: Test Only
	glfwSetKeyCallback(GEngine->window, key_callback);

	while (!glfwWindowShouldClose(GEngine->window))
	{
		GEngine->Render();
		
	}
	
	Engine::DeleteInstance();
	return 0;
}

