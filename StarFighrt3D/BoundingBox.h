#pragma once
#include "Engine.h"

class BoundingBox
{
private:

		Actor* Owner;

		glm::vec3 Size;
		glm::vec3 Center;

		//Check Collision AABB-AABB
		bool CheckCollision(Actor* OtherActor);
public:

	BoundingBox(Actor* NewOwner);

	//Check Collision every Tick
	void DoCollision();

	glm::vec3 GetCenterOfMass();
	glm::vec3 GetSize() { return this->Size; };
	
	void Resize(glm::vec3 NewSize);

	void AddIgnored(Actor* Ignored);

	~BoundingBox();
};

