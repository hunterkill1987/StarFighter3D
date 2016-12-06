#include "stdafx.h"
#include "BoundingBox.h"
#include "World.h"

BoundingBox::BoundingBox(Actor* NewOwner)
{
	Owner = NewOwner;

	GLfloat MinX, MinY, MinZ, MaxX, MaxY, MaxZ;

	std::vector<glm::vec3> Vertics = Owner->GetMesh()->GetVertics();

	MinX = MaxX = Vertics[0].x;
	MinY = MaxY = Vertics[0].y;
	MinZ = MaxZ = Vertics[0].z;

	for (glm::vec3 Vertex : Vertics)
	{
		if (Vertex.x < MinX) MinX = Vertex.x;
		if (Vertex.x > MaxX) MaxX = Vertex.x;
		if (Vertex.y < MinY) MinY = Vertex.y;
		if (Vertex.y > MaxY) MaxY = Vertex.y;
		if (Vertex.z < MinZ) MinZ = Vertex.z;
		if (Vertex.z > MaxZ) MaxZ = Vertex.z;
	}

	Size = glm::vec3(MaxX - MinX, MaxY - MinY, MaxZ - MinZ);
	Center = glm::vec3((MaxX + MinX) / 2, (MaxY + MinY) / 2, (MaxZ + MinZ) / 2);
}


void BoundingBox::Resize(glm::vec3 NewSize)
{
	Size = NewSize;
}

void BoundingBox::DoCollision()
{
	//TODO::
	/*for (Actor* OtherActor : World::GetInstance()->GetActorsItr())
	{
		if (CheckCollision(OtherActor) && OtherActor != Owner)
		{
				OtherActor->OnHit(Owner);
				Owner->OnHit(OtherActor);
		}
	}
	*/
}

bool BoundingBox::CheckCollision(Actor* OtherActor)
{
	BoundingBox* OtherActorBB = OtherActor->CollisionBox;

	if (OtherActorBB == nullptr && Owner == nullptr && OtherActor == nullptr)
	{
		return false;
	}

	bool CollisionX = this->Owner->GetActorPosition().x + this->Size.x >= OtherActor->GetActorPosition().x &&  
					  OtherActor->GetActorPosition().x + OtherActorBB->GetSize().x >= this->Owner->GetActorPosition().x;
	bool CollisionY = this->Owner->GetActorPosition().y + this->Size.y >= OtherActor->GetActorPosition().y && 
		              OtherActor->GetActorPosition().y + OtherActorBB->GetSize().y >= this->Owner->GetActorPosition().y;

	return CollisionX && CollisionY;
}


BoundingBox::~BoundingBox()
{
}
