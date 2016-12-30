#pragma once
#include <vector>
#include "BoundingBox.h"
#include "Mesh.h"

class Actor 
{
private:

	//const int id;
	glm::vec3 Velocity;
	glm::vec3 Position;
	glm::vec3 Rotation;

	Actor* Owner = nullptr;

	bool bIsAlive = false;

	glm::mat4 Transform;

public:
	
	Mesh* ActorMesh = nullptr;
	BoundingBox* CollisionBox = nullptr;
	Actor* GetOwner() { return Owner; };

	virtual Mesh* GetMesh() { return ActorMesh; };
	virtual void Init();


	virtual void Update(float DeltaTime);
	void DestroyActor();

	//Check Collision for Actor
	virtual void OnHit(Actor* HitedActor);

	//Check if Actor is still Alive
	virtual bool IsAlive();

	virtual void SetActorVelocity(glm::vec3 NewVelocity);
	virtual void SetActorPosition(glm::vec3 NewPosition);
	virtual void SetActorRotation(glm::vec3 NewRotation);

	virtual glm::vec3 GetActorRotation();
	virtual glm::vec3 GetActorVelocity();
	virtual glm::vec3 GetActorPosition();

	Actor();
	~Actor();
};

