#include "Camera.h"

void Camera::GetMouseInput(float rotX, float rotY)
{
    viewRotate = glm::mat4(1.0f);
    viewRotate = glm::rotate(viewRotate, glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));
    viewRotate = glm::rotate(viewRotate, glm::radians(rotX), glm::vec3(1.0f, 0.0f, 0.0f));

    forward = glm::normalize(glm::vec3(viewRotate * cameraFace));
    strafe = glm::cross(forward, upVector);
}

glm::mat4 Camera::getWorldToView() const
{
    return glm::lookAt(position, position + forward, upVector);
}

void Camera::MoveForward()
{
    position += walkSpeed * forward;
}
void Camera::MoveBack()
{
    position -= walkSpeed * forward;
}

void Camera::StrafeLeft()
{
    position += walkSpeed * strafe;
}

void Camera::StrafeRight()
{
    position -= walkSpeed * strafe;
}