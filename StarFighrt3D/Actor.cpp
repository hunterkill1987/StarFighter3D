#include "stdafx.h"
#include "Actor.h"

Mesh::Mesh(const char* AssetPath)
{

	MeshScale = glm::vec3(1.f,1.f,1.f);

	if (!LoadAsset(AssetPath))
	{
		return;
	}
}

void Mesh::SetScale(float Scale)
{
	MeshScale.x = Scale;
	MeshScale.y = Scale;
	MeshScale.z = Scale;

	Size *= MeshScale;
}

glm::vec3 Mesh::GetScale()
{
	return MeshScale;
}


std::vector<glm::vec3> Mesh::GetVertics()
{
	return ActorVertics;
}

bool Mesh::LoadAsset(const char* AssetPath)
{
	std::ifstream in(AssetPath, std::ios::in);
	if (!in)
	{
		return false;
	}

	std::string line;

	while (getline(in, line))
	{
		if (line.substr(0, 2) == "v ")
		{
			std::istringstream s(line.substr(2));
			glm::vec3 v;
			s >> v.x; s >> v.y; s >> v.z;

			ActorVertics.push_back(v);
		}

		if (line.substr(0, 2) == "vn")
		{
			std::istringstream s(line.substr(2));
			glm::vec3 vn;
			s >> vn.x; s >> vn.y; s >> vn.z;
			ActorNormals.push_back(vn);
		}
		
		if (line.substr(0, 2) == "f ")
		{
			std::istringstream s(line.substr(2));
			unsigned int a, A, b, B, c, C;
			const char* chh = line.c_str();
			sscanf_s(chh, "f %i//%i %i//%i %i//%i", &a, &A, &b, &B, &c, &C);

			a--; A--;
			b--; B--;
			c--; C--;

			ActorElements.push_back(a);		ActorElementsNormal.push_back(A);
			ActorElements.push_back(b);		ActorElementsNormal.push_back(B);
			ActorElements.push_back(c);		ActorElementsNormal.push_back(C);
		}
	}
	

	InitBuffer();

	return true;
}

void Mesh::InitBuffer()
{
	NumElements = ActorElements.size();

	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cerr << "OpenGL error: " << err << std::endl;
	}
	glGenBuffers(1, &VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * ActorVertics.size(), &ActorVertics[0], GL_STATIC_DRAW);

	glGenBuffers(1, &ElementsBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementsBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ActorElements.size()*sizeof(unsigned short), &ActorElements[0], GL_STATIC_DRAW);

}

void Mesh::DrawMesh()
{
	glEnableClientState(GL_VERTEX_ARRAY);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementsBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,0, (void*)0);

	glDrawElements(GL_TRIANGLES, NumElements/sizeof(GLubyte), GL_UNSIGNED_SHORT, (void*)0);

	glDisableVertexAttribArray(0);
	glDisableClientState(GL_VERTEX_ARRAY);
}


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
