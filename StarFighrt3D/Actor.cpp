#include "stdafx.h"
#include "Actor.h"

Actor::Actor() :
Velocity(0.f, 0.f, 0.f ),
Position(0.f, 0.f, 0.f ),
Rotation(0.f, 0.f, 0.f) 
{
}

void Actor::Init()
{
	bIsAlive = true;

	this->CollisionBox = new BoundingBox(this);

	glm::vec3 BBsize = this->CollisionBox->GetSize();
	BBsize = BBsize * this->GetMesh()->GetScale();

	this->CollisionBox->Resize(BBsize);
}

void Actor::Update(float DeltaTime)
{   
	glm::vec3 velocity = this->GetActorVelocity();
	glm::vec3 pos = this->GetActorPosition();

	glm::vec3 NewPos = pos + velocity;

	this->SetActorPosition(NewPos);

	if (CollisionBox != nullptr)
	{
		this->CollisionBox->DoCollision();
	}

}
 
void Actor::SetActorVelocity(glm::vec3 NewVelocity)
{
	this->Velocity = NewVelocity;
}

void Actor::SetActorPosition(glm::vec3 NewPosition)
{
	this->Position = NewPosition;
}

void Actor::SetActorRotation(glm::vec3 NewRotation)
{
	this->Rotation = NewRotation;
}

glm::vec3 Actor::GetActorVelocity()
{
	return this->Velocity;
}

glm::vec3 Actor::GetActorPosition()
{
	return this->Position;
}

glm::vec3 Actor::GetActorRotation()
{
	return this->Rotation;
}

void Actor::OnHit(Actor* HitedActor)
{
	DestroyActor();
}

bool Actor::IsAlive()
{
	return bIsAlive;
}
void Actor::DestroyActor()
{
	bIsAlive = false;
}

Actor::~Actor()
{
}
