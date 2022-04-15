#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include <map>
#include <string>

#include <iostream>
#include <sstream>
#include <fstream>

#include "Shader.h"

class ShaderManager
{
public:
	static std::map <std::string, Shader> Shaders;

	static Shader LoadShader(const char* vShaderFile, const char* fShaderFile, std::string name);

	static Shader GetShader(std::string name);

	static void Clear();
private:
	ShaderManager() { }
	static Shader LoadShaderFromFile(const char* vShaderFile, const char* fShaderFile);
};

#endif // !SHADER_MANAGER_H