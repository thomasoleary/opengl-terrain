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
#include "Text.h"
#include "Shader.h"

#pragma once

class Program
{
public:
	Program();
	~Program();

	Camera camera;
	TerrainGenerator terrainGenerator;
	Text* text;
	Text* moreText;

	void Update();
	
private:
	// Initialise
	void Init();
	void InitWindow();
	void InitGLEW();
	void InitText();

	void Start();
	void Create();
	void Generate();

	void InputChecks();
	void Render();
	void RenderFrame();
	void RenderText();
	void CleanUp();

	void WireFrameMode();

	// Window related
	SDL_Window* window = nullptr;
	SDL_GLContext glContext = NULL;
	std::string windowName = "OpenGL Terrain";
	glm::vec2 windowRes = glm::vec2(960, 540);

	// Shader related
	GLuint programID = NULL;

	// Mouse related
	glm::vec3 rotation;
	const float rotSpeed = 0.1f;

	// Misc
	bool running = false;
	bool isWireFrameToggled = false;
};

#endif // !PROGRAM_H