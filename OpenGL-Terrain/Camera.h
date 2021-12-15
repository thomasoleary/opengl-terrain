#ifndef CAMERA_H
#define CAMERA_H

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	void MoveForward();
	void MoveBack();
	void StrafeRight();
	void StrafeLeft();

	void GetMouseInput(float rotX, float rotY);

	glm::mat4 getWorldToView() const;

	glm::mat4 viewRotate;
	glm::vec3 forward, strafe;

	glm::vec4 cameraFace = glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);
	glm::vec3 position = glm::vec3(0.0f, 5.0f, 25.0f);

	const glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);

	const float walkSpeed = 0.5f;
};
#endif // !CAMERA_H