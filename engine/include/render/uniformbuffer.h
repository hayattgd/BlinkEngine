#pragma once

#include "glm/ext/scalar_uint_sized.hpp"

namespace BlinkEngine::Engine::Render {
class UniformBuffer {
public:
  UniformBuffer(int size, int point);
  ~UniformBuffer();

  void BufferSubData(int offset, int size, const void* value);

  glm::uint32 GetId();

private:
  glm::uint32 buf;
};
}
