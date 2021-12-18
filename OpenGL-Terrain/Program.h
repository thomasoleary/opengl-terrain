#ifndef PROGRAM_H
#define PROGRAM_H

#include <iostream>

#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
	void Start();
	void InputChecks();
	void Render();
	void CleanUp();

	void WireFrameMode();

	// Window related
	SDL_Window* window = nullptr;
	SDL_GLContext glContext = NULL;
	std::string windowName = "OpenGL Terrain";
	int windowWidth = 960;
	int windowHeight = 540;

	// Shader related
	GLuint programID = NULL;

	// Mouse related
	glm::vec3 rotation;
	const float rotSpeed = 0.1f;

	// Misc
	bool running = false;
	bool isWireFrameToggled = false;
	int numberOfIndicies = 0;


};

#endif // !PROGRAM_H