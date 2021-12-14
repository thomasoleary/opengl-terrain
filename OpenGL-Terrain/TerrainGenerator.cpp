#include "TerrainGenerator.h"

void TerrainGenerator::GenerateTerrain(int dimension)
{
	Dimension = dimension;
	GenerateVertices(Dimension);
	GenerateIndices(Dimension);
}

void TerrainGenerator::GenerateVertices(int dimension)
{
	terrain.numberOfVertices = dimension * dimension;
	std::cout << "Number of Vertices: " << terrain.numberOfVertices << std::endl;

	int halfDimension = dimension / 2;

	terrain.vertices = new Vertex[terrain.numberOfVertices];

	for (int i = 0; i < dimension; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			Vertex& currentVertice = terrain.vertices[i * dimension + j];

			currentVertice.position.x = (i - halfDimension) * gridSpacing;
			currentVertice.position.y = 1.0f;
			currentVertice.position.z = (j - halfDimension) * gridSpacing;

			currentVertice.normals = glm::vec3(0.0f, 1.0f, 0.0f);

			currentVertice.colour = glm::vec3(1.0f, 1.0f, 0.0f);

		}
	}
}

void TerrainGenerator::GenerateIndices(int dimension)
{
	terrain.numberOfIndices = (dimension - 1) * (dimension - 1) * 6;
	std::cout << "Number of Indices: " << terrain.numberOfIndices << std::endl;

	terrain.indices = new GLshort[terrain.numberOfIndices];

	int vertice = 0;

	for (int i = 0; i < dimension - 1; i++)
	{
		for (int j = 0; j < dimension - 1; j++)
		{
			// Triangle 1
			terrain.indices[vertice++] = dimension * i + j;
			terrain.indices[vertice++] = dimension * i + j + dimension;
			terrain.indices[vertice++] = dimension * i + j + dimension + 1;
			
			// Triangle 2
			terrain.indices[vertice++] = dimension * i + j;
			terrain.indices[vertice++] = dimension * i + j + 1;
			terrain.indices[vertice++] = dimension * i + j + dimension + 1;
		}
	}

}
