#include "Camera.h"

void Camera::GetMouseInput(float rotX, float rotY)
{
    viewRotate = glm::mat4(1.0f);
    viewRotate = glm::rotate(viewRotate, glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));
    viewRotate = glm::rotate(viewRotate, glm::radians(rotX), glm::vec3(1.0f, 0.0f, 0.0f));

    forward = glm::normalize(glm::vec3(viewRotate * cameraFace));
    strafe = glm::cross(forward, upVector);
}

glm::mat4 Camera::GetWorldToView() const
{
    return glm::lookAt(position, position + forward, upVector);
}

void Camera::Update(GLuint programID)
{
    view = GetWorldToView();
    projection = glm::perspective(glm::radians(45.f), 4.0f / 3.0f, 0.1f, 1000.0f);
    mvp = model * projection * view;

    mvpLocation = glGetUniformLocation(programID, "model");
    projectionLocation = glGetUniformLocation(programID, "projection");

    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(mvp));
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(model));
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