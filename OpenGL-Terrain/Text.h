#ifndef TEXT_H
#define TEXT_H

#include <iostream>
#include <map>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Shader.h"

// Holds all information relvent to a character
struct Character
{
	unsigned int textureID; // ID for glyph
	glm::ivec2 size;		// Size of glyph
	glm::ivec2 bearing;		// Offset of glyph
	unsigned int advance;	// Horizontal offset to next glyph
};

#pragma once
class Text
{
public:
	// Class Constructor
	Text(unsigned int width, unsigned int height);

	// List of pre-compiled characters
	std::map<char, Character> characters;

	// Pre-compiles the list of characters from a given font
	void Load(std::string font, unsigned int fontSize);

	// Renders a string of text using the pre-compiled list
	void Render(std::string text, float x, float y, float scale, glm::vec3 colour = glm::vec3(1.0f));

	GLuint textProgramID;
	GLuint projectionUInt;
	GLuint colourLocation;
	glm::mat4 projection;

private:
	unsigned int VAO, VBO;
};

#endif // !TEXT_H