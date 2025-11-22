#include "component/camera.h"

#include <cmath>

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/geometric.hpp"
#include "glm/trigonometric.hpp"
#include "glm/ext/vector_float3.hpp"

namespace BlinkEngine::Engine::Component {
  Camera::Camera(glm::vec3 pos, float yaw, float pitch, float fov, float nearPlane, float farPlane) {
    this->position = pos;
    this->yaw = yaw;
    this->pitch = pitch;

    this->fov = fov;
    this->nearPlane = nearPlane;
    this->farPlane = farPlane;
  }

  void Camera::UpdateDirection() {
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);
  }

  glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(position, position + front, glm::vec3(0, 1, 0));
  }

  glm::mat4 Camera::GetProjectionMatrix() {
    return glm::perspective(glm::radians(fov), width / height, nearPlane, farPlane);
  }

  glm::vec3 Camera::GetFront() {
    UpdateDirection();
    return this->front;
  }

  glm::vec3 Camera::GetRight() {
    UpdateDirection();
    return glm::normalize(glm::cross(front, glm::vec3(0, 1, 0)));
  }
}
