#include "stdafx.h"
#include "Engine.h"
#include "World.h"

World* World::Instance = nullptr;

World* World::GetInstance()
{
	if (Instance == nullptr)
	{
		Instance = new World();

	}
	return Instance;
}

void World::Update(float DeltaTime)
{

}

World::World()
{

}


void World::OnRestart()
{

}

void World::RestartGame()
{

}

void World::Init(Engine* _Engine)
{
	GEngine = _Engine;

	GActorManager = ActorManager::GetInstance();
	if (GActorManager != nullptr)
	{
		GActorManager->Init();
	}
	GEngine->GetEventManager()->Bind(this, &World::OnRestart, "Restart");
}

ActorManager* World::GetActorManager()
{
	return GActorManager;
}
World::~World()
{
}
