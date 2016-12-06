#include "stdafx.h"
#include <stdlib.h>
#include "Engine.h"
#include "World.h"


Engine* Engine::Instance = nullptr;

Engine* Engine::GetInstance()
{
	if (Instance == nullptr)
	{
		Instance = new Engine();
	}
	return Instance;
}

Engine::Engine()
{
	if (!glfwInit())
		exit(EXIT_FAILURE);


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Test", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();

	if (glewError != GLEW_OK)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}


	EventMgr = EventManager::GetInstance();

	glfwSwapInterval(1); 		

	glEnable(GL_BLEND);		
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLint Success;
	GLchar InfoLog[512];

	GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShader, 1, &vertexSource, NULL);
	glCompileShader(VertexShader);
	glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &Success);
	if (!Success)
	{
		glGetShaderInfoLog(VertexShader, 512, NULL, InfoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << InfoLog << std::endl;
	};

	GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(FragmentShader);

	glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &Success);
	if (!Success)
	{
		glGetShaderInfoLog(FragmentShader, 512, NULL, InfoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << InfoLog << std::endl;
	};

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, VertexShader);
	glAttachShader(shaderProgram, FragmentShader);
	//glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);


	glm::mat4 view;
	glm::mat4 projection;
	view = glm::translate(view, glm::vec3(0.0f, 5.0f, 0.f));
	projection = glm::perspective(45.f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

	GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
	GLint projLoc = glGetUniformLocation(shaderProgram, "projection");

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glLineWidth(1.0f);		
}

void Engine::Render()
{
	OldTime = NewTime;
	
	static World* GWorld = World::GetInstance();

	float ratio;
	int width, height;

	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float)height;
	glViewport(0, 0, width, height);
	
	glClear(GL_COLOR_BUFFER_BIT);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (GWorld != nullptr)
	{
		for (Actor* ActorItr : GWorld->GetActorManager()->GetActorsItr())
		{
			if (ActorItr->IsAlive())
			{
				Mesh* ActorMesh = ActorItr->GetMesh();
				if (ActorMesh != nullptr)
				{
					glm::mat4 model;
					model = glm::translate(model, ActorItr->GetActorPosition());

					model = glm::rotate(model, ActorItr->GetActorRotation().x, glm::vec3(1.0f, 0.0f, 0.0f));
					model = glm::rotate(model, ActorItr->GetActorRotation().y, glm::vec3(0.0f, 1.0f, 0.0f));
					model = glm::rotate(model, ActorItr->GetActorRotation().z, glm::vec3(0.0f, 0.0f, 1.0f));
				
					model = glm::scale(model, ActorMesh->GetScale());

					GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
					glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
					ActorMesh->DrawMesh();
				}
			}
		}
	}
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	cameraAngleX += 0.1f;

	glfwSwapBuffers(window);
	glfwPollEvents();

	NewTime = (float)glfwGetTime();

	DeltaTime = NewTime - OldTime;
}

float Engine::RandToFloat(float min, float max)
{
	std::mt19937		gen(random());
	std::uniform_real_distribution<float> dis(min, max);

	return dis(gen);
}

float Engine::GetDeltaTime() const
{
	return DeltaTime;
}


bool Engine::IsNear(float A, float B, float Epsilon)
{
	float NewEpsilon = (float)EPSILON;
	if (Epsilon != 0.f)
	{
		NewEpsilon = Epsilon;
	}
	if ((fabs(A - B) < NewEpsilon))
	{
		return true;
	}
	return false;
}

EventManager* Engine::GetEventManager() const
{
	return EventMgr;
}

void Engine::Exit()
{
}

void Engine::DeleteInstance()
{
	EventManager::DeleteInstance();
	delete Instance;
	Instance = nullptr;
}

Engine::~Engine()
{
}
