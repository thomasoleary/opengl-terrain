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

void TerrainGenerator::InitValues(int dimension)
{
	terrain.dimension = dimension;
	halfDimension = dimension / 2;

	terrain.numberOfVertices = dimension * dimension;
	std::cout << "Number of Verts: " << terrain.numberOfVertices << std::endl;
	terrain.vertices = new Vertex[terrain.numberOfVertices];

	terrain.numberOfIndices = (dimension - 1) * (dimension - 1) * 6;
	std::cout << "Number of Indices: " << terrain.numberOfIndices << std::endl;
	terrain.indices = new short[terrain.numberOfIndices];
}

void TerrainGenerator::GenerateTerrain(int dimension)
{
	dimension++;
	InitValues(dimension);

	GenerateVertices(dimension);
	GenerateIndices(dimension);

	TerrainManager();
	std::cout << "Terrain Generated\n" << std::endl;
}

void TerrainGenerator::GenerateVertices(int dimension)
{
	for (int i = 0; i < dimension; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			Vertex& currentVert = terrain.vertices[i * dimension + j];

			currentVert.position.x = (j - halfDimension) * gridSpacing;
			currentVert.position.y = 0.0f;// noise.ApplyNoise(i, j);
			currentVert.position.z = (i - halfDimension) * gridSpacing;

			currentVert.colour = glm::vec3(0.0f, 1.0f, 0.0f);
		}
	}
	std::cout << "Terrain Vertices generated" << std::endl;
}


void TerrainGenerator::GenerateIndices(int dimension)
{
	int index = 0;

	for (int i = 0; i < dimension - 1; i++)
	{
		for (int j = 0; j < dimension - 1; j++)
		{
			// Triangle 1
			terrain.indices[index++] = dimension * i + j;
			terrain.indices[index++] = dimension * i + j + dimension;
			terrain.indices[index++] = dimension * i + j + dimension + 1;

			// Triangle 2
			terrain.indices[index++] = dimension * i + j;
			terrain.indices[index++] = dimension * i + j + 1;
			terrain.indices[index++] = dimension * i + j + dimension + 1;

		}
	}
	assert(index == terrain.numberOfIndices);
	std::cout << "Terrain Indices generated\n" << std::endl;
}

void TerrainGenerator::ApplyNoise(int dimension)
{
	std::cout << "Apply noise" << std::endl;

	noise.GenerateSeed();

	for (int i = 0; i < dimension; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			Vertex& currentVert = terrain.vertices[i * dimension + j];

			currentVert.position.y = noise.ApplyNoise(i, j);
		}
	}
}

void TerrainGenerator::TerrainManager()
{
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, terrain.ReturnVertexBufferSize(), terrain.vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &indexArrayBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexArrayBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, terrain.ReturnIndexBufferSize(), terrain.indices, GL_STATIC_DRAW);


	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexByteSize, (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexByteSize, (void*)(sizeof(float) * 3));

}
