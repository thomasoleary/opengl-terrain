#include "Program.h"

Program::Program()
{
	Init();
}
Program::~Program()
{
	CleanUp();
}

void Program::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_Init failed", SDL_GetError(), NULL);
		return;
	}

	window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 640, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	if (window == nullptr)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_CreateWindow failed", SDL_GetError(), NULL);
		SDL_Quit();
		return;
	}

	SDL_SetRelativeMouseMode(SDL_TRUE);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	glContext = SDL_GL_CreateContext(window);

	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "GLEW Failed to Initialise", SDL_GetError(), NULL);
	}

	std::cout << "Program Initialised\n" << std::endl;

	running = true;
}

void Program::Update()
{
	terrainGenerator.GenerateTerrain(15);

	programID = LoadShaders("VertexShader.glsl", "FragmentShader.glsl");

	while (running)
	{
		InputChecks();
		Render();
	}
}

void Program::InputChecks()
{
	SDL_Event event;

	//https://wiki.libsdl.org/SDL_PollEvent
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			running = false;
			break;

		case SDL_MOUSEMOTION:
		{
			rotation.y -= event.motion.xrel * rotSpeed;
			rotation.x -= event.motion.yrel * rotSpeed;
			camera.GetMouseInput(rotation.x, rotation.y);
			break;
		}
		case SDL_KEYUP:
			switch (event.key.keysym.sym)
			{
			case SDLK_e:
				isWireFrameToggled = !isWireFrameToggled;
				WireFrameMode();
				break;
			}

		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				running = false;
				break;
			case SDLK_w:
				camera.MoveForward();
				break;
			case SDLK_s:
				camera.MoveBack();
				break;
			case SDLK_a:
				camera.StrafeRight();
				break;
			case SDLK_d:
				camera.StrafeLeft();
				break;
			}
		}
	}
}

void Program::Render()
{
	glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

	glUseProgram(programID);

	camera.Update(programID);
	
	glDrawElements(GL_TRIANGLES, terrainGenerator.terrain.numberOfIndices, GL_UNSIGNED_SHORT, (void*)0);

	SDL_GL_SwapWindow(window);
}

void Program::CleanUp()
{
	glUseProgram(0);
	glDeleteProgram(programID);

	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();

	std::cout << "Program Clean Up" << std::endl;
	return;
}

void Program::WireFrameMode()
{
	if (isWireFrameToggled)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}