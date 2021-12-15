#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 vertexColour;

uniform mat4 model;
uniform mat4 projection;


out vec3 colour;

void main()
{

	gl_Position = model * vec4(position, 1.0f);

	colour = vertexColour;
}