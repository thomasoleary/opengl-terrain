#include "Program.h"

const int TERRAIN_SIZE = 50;

Program::Program()
{
	this->Init();
}
Program::~Program()
{
	this->CleanUp();
}

void Program::Init()
{
	InitWindow();
	InitGLEW();

	Start();
	
	std::cout << "Program Initialised\n" << std::endl;
}
void Program::InitWindow()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_Init failed", SDL_GetError(), NULL);
		return;
	}

	window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, (int)windowRes.x, (int)windowRes.y, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

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
}
void Program::InitGLEW()
{
	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "GLEW Failed to Initialise", SDL_GetError(), NULL);
	}
}

void Program::Start()
{
	if (!(programID = LoadShaders("VertexShader.glsl", "FragmentShader.glsl")))
		throw std::runtime_error("Failed to load shaders");
	
	Create();

	Generate();
	

	running = true;
}

void Program::Update()
{
	while (running)
	{
		InputChecks();
		Render();
	}
}

void Program::InputChecks()
{
	SDL_Event event;

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
			case SDLK_SPACE:
				Generate();
				//std::cout << "Space bar" << std::endl;
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
	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, (int)windowRes.x, (int)windowRes.y);
	glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


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

void Program::Create()
{
	if (!terrainGenerator.Create(TERRAIN_SIZE))
		throw std::runtime_error("Failed to create terrain.");
}

void Program::Generate()
{
	if (!terrainGenerator.Generate())
		throw std::runtime_error("Failed to generate terrain.");
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