#include <iostream>

#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#pragma once


class Program
{
public:
	Program();
	~Program();
	
	void Loop();

private:
	
	void Init();
	void CleanUp();
	void InputChecks();
	void Render();


	SDL_Window* window = nullptr;
	SDL_GLContext glContext = NULL;


	std::string windowName = "OpenGL Terrain";
	bool running = false;
};