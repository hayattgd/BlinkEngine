#pragma once

#include "glm/ext/scalar_uint_sized.hpp"

namespace BlinkEngine::Engine::Render {
class UniformBuffer {
public:
  UniformBuffer(int size, int point);
  ~UniformBuffer();

  void BufferSubData(int offset, int size, const void* value);
  static glm::uint32 ReserveBindingPoint();

  glm::uint32 GetId();

private:
  glm::uint32 buf;
  inline static glm::uint32 last_binding_point = 0;
};
}
