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

void TerrainGenerator::GenerateTerrain(int dimension)
{
	std::cout << "Terrain Generating" << std::endl;
	//std::cout << "Vertex Byte Size: " << vertexByteSize << std::endl;

	dimension++;
	GenerateVertices(dimension);
	GenerateIndices(dimension);

	TerrainManager();
	std::cout << "Terrain Generated\n" << std::endl;
}

glm::vec3 RandomColor()
{
	glm::vec3 colour;
	colour.x = rand() / (float)RAND_MAX;
	colour.y = rand() / (float)RAND_MAX;
	colour.z = rand() / (float)RAND_MAX;
	return colour;
}

void TerrainGenerator::GenerateVertices(int dimension)
{
	terrain.numberOfVertices = dimension * dimension;
	std::cout << "Number of Verts: " << terrain.numberOfVertices << std::endl; // For debugging purposes

	int halfDimension = dimension / 2;

	terrain.vertices = new Vertex[terrain.numberOfVertices];

	for (int i = 0; i < dimension; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			Vertex& currentVert = terrain.vertices[i * dimension + j];

			currentVert.position.x = (j - halfDimension) * gridSpacing;
			currentVert.position.y = 0.0f;//noise.GetNoise(col * .15f, row * .15f) * heightScale;
			currentVert.position.z = (i - halfDimension) * gridSpacing;

			currentVert.normals = glm::vec3(0.0f, 1.0f, 0.0f);

			currentVert.colour = glm::vec3(0.0f, 1.0f, 0.0f); //RandomColor();
		}
	}
	std::cout << "Terrain Vertices generated\n" << std::endl;
}


void TerrainGenerator::GenerateIndices(int dimension)
{
	terrain.numberOfIndices = (dimension - 1) * (dimension - 1) * 6;
	std::cout << "Number of Indices: " << terrain.numberOfIndices << std::endl; // For debugging purposes

	terrain.indices = new short[terrain.numberOfIndices];

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
