#include "TerrainGenerator.h"

TerrainGenerator::~TerrainGenerator()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glDeleteBuffers(1, &vertexBufferID);
	glDeleteBuffers(1, &indexArrayBufferID);
	glDeleteVertexArrays(1, &vertexArrayID);
	std::cout << "TerrainGenerator Destroyed" << std::endl;
}

bool TerrainGenerator::Init(int dimension)
{
	terrain.dimension = dimension;
	halfDimension = terrain.dimension / 2;

	terrain.numberOfVertices = terrain.dimension * terrain.dimension;
	std::cout << "Number of Verts: " << terrain.numberOfVertices << std::endl;
	terrain.vertices = new Vertex[terrain.numberOfVertices];
	
	terrain.numberOfIndices = (terrain.dimension - 1) * (terrain.dimension - 1) * 6;
	std::cout << "Number of Indices: " << terrain.numberOfIndices << std::endl;
	terrain.indices = new short[terrain.numberOfIndices];
	
	return GenerateIndices();
}

bool TerrainGenerator::Create(int dimension)
{
	return Init(++dimension);
}

bool TerrainGenerator::Generate()
{
	// something noise
	noise.GenerateSeed();
	return GenerateVertices();
}

bool TerrainGenerator::GenerateVertices()
{
	int index = 0;
	for (int i = 0; i < terrain.dimension; i++)
	{
		for (int j = 0; j < terrain.dimension; j++)
		{
			Vertex& currentVert = terrain.vertices[i * terrain.dimension + j];

			currentVert.position.x = static_cast<float>((j - halfDimension) * gridSpacing);
			currentVert.position.y = noise.ApplyNoise(i, j);
			currentVert.position.z = static_cast<float>((i - halfDimension) * gridSpacing);

			currentVert.colour = glm::vec3(0.0f, 1.0f, 0.0f);
			index++;
		}
	}
	assert(index == terrain.numberOfVertices);
	std::cout << "Terrain Vertices generated" << std::endl;

	return TerrainManager();
}

bool TerrainGenerator::GenerateIndices()
{
	int index = 0;
	for (int i = 0; i < terrain.dimension - 1; i++)
	{
		for (int j = 0; j < terrain.dimension - 1; j++)
		{
			// Triangle 1
			terrain.indices[index++] = terrain.dimension * i + j;
			terrain.indices[index++] = terrain.dimension * i + j + terrain.dimension;
			terrain.indices[index++] = terrain.dimension * i + j + terrain.dimension + 1;

			// Triangle 2
			terrain.indices[index++] = terrain.dimension * i + j;
			terrain.indices[index++] = terrain.dimension * i + j + 1;
			terrain.indices[index++] = terrain.dimension * i + j + terrain.dimension + 1;

		}
	}
	assert(index == terrain.numberOfIndices);
	std::cout << "Terrain Indices generated" << std::endl;

	return true;
}

bool TerrainGenerator::TerrainManager()
{
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, terrain.ReturnVertexBufferSize(), terrain.vertices, GL_DYNAMIC_DRAW);

	glGenBuffers(1, &indexArrayBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexArrayBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, terrain.ReturnIndexBufferSize(), terrain.indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexByteSize, (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexByteSize, (void*)(sizeof(float) * 3));

	return true;
}