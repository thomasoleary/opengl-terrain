#ifndef CAMERA_H
#define CAMERA_H

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>


class Camera
{
public:
	void Update(GLuint programID);

	void MoveForward();
	void MoveBack();
	void StrafeRight();
	void StrafeLeft();

	void GetMouseInput(float rotX, float rotY);

	glm::mat4 GetWorldToView() const;

	glm::mat4 mvp, view, projection;
	glm::mat4 model = glm::mat4(1.0f);

	GLuint mvpLocation;
	GLuint projectionLocation;

	glm::mat4 viewRotate;
	glm::vec3 forward, strafe;

	glm::vec4 cameraFace = glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);
	glm::vec3 position = glm::vec3(0.0f, 5.0f, 0.0f);
	glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);

	const glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);

	const float walkSpeed = 0.5f;
};
#endif // !CAMERA_H