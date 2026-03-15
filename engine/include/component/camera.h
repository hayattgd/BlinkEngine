#pragma once

#include "glm/ext/scalar_uint_sized.hpp"
#include "render/uniformbuffer.h"
#include <glm/ext/vector_float3.hpp>
#include <glm/fwd.hpp>

namespace BlinkEngine::Engine::Component {
class Camera {
public:
  Camera(glm::vec3 pos, float yaw, float pitch, float fov, float nearPlane,
         float farPlane);
  void UpdateDirection();
  void Render();
  glm::uint32 GetUniformBufferBindingPoint();
  glm::mat4 GetViewMatrix();
  glm::mat4 GetProjectionMatrix();
  glm::vec3 GetFront();
  glm::vec3 GetRight();
  glm::vec3 GetUp();
  glm::vec3 position;
  float yaw;
  float pitch;
  float fov;
  float width;
  float height;
  float nearPlane;
  float farPlane;

private:
  glm::vec3 front;
  Render::UniformBuffer* ubo;
};
} // namespace BlinkEngine::Engine::Component
