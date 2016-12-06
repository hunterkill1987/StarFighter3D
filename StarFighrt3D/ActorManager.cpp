#include "stdafx.h"
#include "ActorManager.h"

ActorManager* ActorManager::Instance = 0;

ActorManager* ActorManager::GetInstance()
{
	if (Instance == 0)
	{
		Instance = new ActorManager();
	}
	return Instance;
}

void ActorManager::DeleteInstance()
{

	delete Instance;
	Instance = nullptr;
}

void ActorManager::Init()
{
	ActiveActor.reserve(PoolSize);
	DeadActor.reserve(PoolSize);
	for (int i = 0; i < PoolSize; i++)
	{
		DeadActor.push_back(new Actor());
	}
}

const std::vector<Actor*> ActorManager::GetActorsItr()
{
	return ActiveActor;
}

ActorManager::ActorManager()
{
}


ActorManager::~ActorManager()
{
}
