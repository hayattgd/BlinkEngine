#include "render/uniformbuffer.h"

#include "glm/ext/scalar_uint_sized.hpp"
#include "glad/glad.h"

namespace BlinkEngine::Engine::Render {
  UniformBuffer::UniformBuffer(int size, int point) {
    glGenBuffers(1, &buf);
    glBindBuffer(GL_UNIFORM_BUFFER, buf);
    glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_STATIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, point, buf);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
  }

  UniformBuffer::~UniformBuffer() {
    glDeleteBuffers(1, &buf);
  }

  void UniformBuffer::BufferSubData(int offset, int size, const void* value) {
    glBindBuffer(GL_UNIFORM_BUFFER, buf);
    glBufferSubData(GL_UNIFORM_BUFFER, offset, size, value);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
  }

  glm::uint32 UniformBuffer::ReserveBindingPoint() {
    return last_binding_point++;
  }

  glm::uint32 UniformBuffer::GetId() {
    return buf;
  }
}
