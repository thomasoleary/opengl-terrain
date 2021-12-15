#ifndef PROGRAM_H
#define PROGRAM_H

#include <iostream>

#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <sstream>
#include <vector>

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

	// Window related
	SDL_Window* window = nullptr;
	SDL_GLContext glContext = NULL;
	std::string windowName = "OpenGL Terrain";

	// Shader related
	GLuint programID = NULL;
	GLuint mvpLocation;
	GLuint projectionLocation;

	// Camera related
	glm::mat4 mvp, view, projection;
	glm::mat4 model = glm::mat4(1.0f);
	glm::vec3 rotation;
	const float rotSpeed = 0.1f;

	// Misc
	bool running = false;
	int numberOfIndicies = 0;


};

#endif // !PROGRAM_H