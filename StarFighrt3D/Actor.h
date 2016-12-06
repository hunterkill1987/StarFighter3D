#pragma once
#include <vector>
#include "Engine.h"
#include "BoundingBox.h"

class BoundingBox;
//Mesh Class
class Mesh
{
public:
	Mesh(const char* AssetPath);
	~Mesh(){};

private:
	
	static const unsigned int BUFFERS = 4;

	bool LoadAsset(const char* AssetPath);

	void InitBuffer();

	std::vector<glm::vec3> ActorVertics;
	std::vector<glm::vec3>  ActorNormals;
	std::vector<unsigned short>  ActorElements;
	std::vector<unsigned short>  ActorElementsNormal;

	GLuint VertexBuffer;
	GLuint ElementsBuffer;

	glm::vec3 MeshScale;

	glm::vec3 Size;  
	glm::vec3 Center;
	unsigned int NumElements;

public:

	//Scale Mesh 
	void SetScale(float Scale);
	glm::vec3 GetScale();
	std::vector<glm::vec3> GetVertics();

	void DrawMesh();
};

class Actor 
{
private:

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

