#include "component/camera.h"

#include <cmath>

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/trigonometric.hpp"

#include "application.h"
#include "component/meshrenderer.h"
#include "render/uniformbuffer.h"

namespace BlinkEngine::Engine::Component {
Camera::Camera(glm::vec3 pos, float yaw, float pitch, float fov,
               float nearPlane, float farPlane) {
  this->position = pos;
  this->yaw = yaw;
  this->pitch = pitch;

  this->width = 1;
  this->height = 1;

  this->fov = fov;
  this->nearPlane = nearPlane;
  this->farPlane = farPlane;
  this->ubo = new Render::UniformBuffer(sizeof(glm::mat4)*2, 1);
}

void Camera::UpdateDirection() {
  front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  front.y = sin(glm::radians(pitch));
  front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  front = glm::normalize(front);
}

void Camera::Render() {
  ubo->BufferSubData(0, sizeof(glm::mat4), glm::value_ptr(GetViewMatrix()));
  ubo->BufferSubData(sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(GetProjectionMatrix()));

  for (auto &e : Application::GetInstance().GetWorld().GetEntities()) {
    auto *component =
        Application::GetInstance().GetWorld().GetComponent<MeshRenderer>(e);
    if (component != nullptr) {
      component->Render(this);
    }
  }
}

glm::uint32 Camera::GetUniformBufferBindingPoint() {
  return 1;
}

glm::mat4 Camera::GetViewMatrix() {
  return glm::lookAt(position, position + front, glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 Camera::GetProjectionMatrix() {
  return glm::perspective(glm::radians(fov), width / height, nearPlane,
                          farPlane);
}

glm::vec3 Camera::GetFront() {
  UpdateDirection();
  return this->front;
}

glm::vec3 Camera::GetRight() {
  UpdateDirection();
  return glm::normalize(glm::cross(glm::vec3(0, 1, 0), front));
}

glm::vec3 Camera::GetUp() {
  return glm::cross(front, GetRight());
}
} // namespace BlinkEngine::Engine::Component
