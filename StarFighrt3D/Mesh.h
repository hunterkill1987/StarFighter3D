#pragma once
#include "Engine.h"

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
