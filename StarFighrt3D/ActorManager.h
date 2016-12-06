#pragma once
#include "Engine.h"
#include "Actor.h"

class ActorManager
{
private:

	//TODO:: Remove PoolSize;
	static ActorManager* Instance;

	std::vector<Actor*> ActiveActor;

	std::vector<Actor*> DeadActor;

	static const int PoolSize = 1000;

public:

	const std::vector<Actor*> GetActorsItr();

	static ActorManager* GetInstance();

	static void DeleteInstance();

	void Init();

	ActorManager();
	~ActorManager();
};

