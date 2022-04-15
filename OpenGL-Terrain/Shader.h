#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <gl\glew.h>
#include <SDL_opengl.h>
#include <string>

//#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <sstream>
#include <vector>

class Shader
{
public:
	unsigned int ID;

	Shader() { }
	Shader& Use();

	void Compile(const char* vertexSource, const char* fragmentSource);

	void SetFloat(const char* name, float value, bool useShader = false);
	void SetInteger(const char* name, int value, bool useShader = false);

	void SetVector2f(const char* name, float x, float y, bool useShader = false);
	void SetVector2f(const char* name, const glm::vec2& value, bool useShader = false);
	
	void SetVector3f(const char* name, float x, float y, float z, bool useShader = false);
	void SetVector3f(const char* name, const glm::vec3& value, bool useShader = false);
	
	void SetVector4f(const char* name, float x, float y, float z, float w, bool useShader = false);
	void SetVector4f(const char* name, const glm::vec4& value, bool useShader = false);

	void SetMatrix4(const char* name, const glm::mat4& matrix, bool useShader = false);
private:
	void checkCompileErrors(unsigned int object, std::string type);
};

GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);

#endif // !SHADER_H