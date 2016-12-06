#pragma once
#include "Math.h"
#include "Actor.h"
#include "ActorManager.h"

class Engine;

class World
{
private:

	static World* Instance;

	static bool RemoveActor(Actor* CheckActor);
	bool CheckActorIsAliave(Actor* CheckActor);
	
	ActorManager* GActorManager = nullptr;

public:
	
	Engine* GEngine = nullptr;

	ActorManager* GetActorManager();

	static World* GetInstance();

	void Init(Engine* _Engine);

	void Update(float DeltaTime);

	void OnRestart();

	void RestartGame();

	template<typename TargetT>
	TargetT* SpawnActor(glm::vec3 NewPos, Actor* Owner)
	{
		Actor* NewActor = nullptr;
		if (NewActor == nullptr)
		{
			if (!this->DeadActor.empty())
			{
				NewActor = this->DeadActor.back();
				this->DeadActor.pop_back();
				if (NewActor != nullptr)
				{
					Actor* tmpActor(new TargetT);
					NewActor = tmpActor;
				}
			}
			NewActor->Init();
			NewActor->SetActorPosition(NewPos);

			this->ActiveActor.push_back(NewActor);
			return dynamic_cast<TargetT*>(NewActor);
		}
		return nullptr;
	}

	

	World();
	~World();
};

