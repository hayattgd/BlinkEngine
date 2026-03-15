#pragma once

#include <string>

#include "glm/ext/scalar_uint_sized.hpp"

namespace BlinkEngine::Engine::Render {
class Shader {
public:
  Shader(std::string vertpath, std::string fragpath);
  void Use();
  void UniformBlockBinding(const char* uniform_name, glm::uint32 binding_point);
  glm::uint32 GetId();
  void Compile();

private:
  std::string vert;
  std::string frag;
  glm::uint32 id;
};
} // namespace BlinkEngine::Engine::Render
