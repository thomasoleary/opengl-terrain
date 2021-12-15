#include <iostream>

#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "TerrainGenerator.h"
#include "Shader.h"

#pragma once

class Program
{
public:
	Program();
	~Program();

	Camera camera;
	TerrainGenerator terrainGenerator;
	void Update();
	
private:
	
	void Init();
	void InputChecks();
	void Render();
	void CleanUp();


	SDL_Window* window = nullptr;
	SDL_GLContext glContext = NULL;

	GLuint programID = NULL;
	GLuint mvpLocation;
	GLuint projectionLocation;

	// Camera related variables
	glm::mat4 mvp, view, projection;
	glm::mat4 model = glm::mat4(1.0f);
	glm::vec3 rotation;
	const float rotSpeed = 0.1f;


	std::string windowName = "OpenGL Terrain";
	bool running = false;

};

