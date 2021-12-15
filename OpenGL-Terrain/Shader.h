#pragma once

#include <iostream>
#include <gl\glew.h>
#include <SDL_opengl.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);