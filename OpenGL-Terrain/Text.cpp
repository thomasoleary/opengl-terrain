#include "Text.h"

Text::Text(float width, float height)
{
	if(!(textProgramID = LoadShaders("TextVertex.glsl", "TextFragment.glsl")))
		throw std::runtime_error("Failed to load Text Shaders");

	projection = glm::ortho(0.0f, width, 0.0f, height);
	glUseProgram(textProgramID);

	projectionUInt = glGetUniformLocation(textProgramID, "projection");
	glUniformMatrix4fv(projectionUInt, 1, GL_FALSE, glm::value_ptr(projection));
	
	textLocation = glGetUniformLocation(textProgramID, "text");
	glUniform1i(textProgramID, 0);
	
	colourLocation = glGetUniformLocation(textProgramID, "textColor");

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Text::~Text()
{
	glDisableVertexAttribArray(2);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glUseProgram(0);
	glDeleteProgram(textProgramID);

	std::cout << "Text Destroyed" << std::endl;
}

void Text::Load(std::string font, unsigned int fontSize)
{
	characters.clear();

	FT_Library ft;
	if (FT_Init_FreeType(&ft))
		throw std::runtime_error("ERROR: FREETYPE: Could not init FreeType Library");

	FT_Face face;
	if (FT_New_Face(ft, font.c_str(), 0, &face))
		throw std::runtime_error("ERROR: FREETYPE: Failed to load font");

	FT_Set_Pixel_Sizes(face, 0, fontSize);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for (GLubyte c = 0; c < 128; c++)
	{
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			throw std::runtime_error("ERROR: FREETYPE: Failed to load Glyph");
			continue;
		}

		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		characters.insert(std::pair<char, Character>(c, character));
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	std::cout << "Text Loaded\n" << std::endl;
}

void Text::Render(std::string text, float x, float y, float scale, glm::vec3 colour)
{
	glUseProgram(textProgramID);

	glUniform3f(colourLocation, colour.x, colour.y, colour.z);

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = characters[*c];

		float xpos = x + ch.bearing.x * scale;
		float ypos = y + (characters['H'].bearing.y - ch.bearing.y) * scale;

		float w = ch.size.x * scale;
		float h = ch.size.y * scale;

		float vertices[6][4] = {
			{ xpos,		ypos + h,	0.0f, 1.0f},
			{ xpos + w, ypos,		1.0f, 0.0f},
			{ xpos,		ypos,		0.0f, 0.0f},

			{ xpos,		ypos + h,	0.0f, 1.0f},
			{ xpos + w, ypos + h,	1.0f, 1.0f},
			{ xpos + w, ypos,		1.0f, 0.0f}
		};

		glBindTexture(GL_TEXTURE_2D, ch.textureID);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		x += (ch.advance >> 6) * scale;
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}