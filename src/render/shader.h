#pragma once

#include <string>

#include "glm/ext/scalar_uint_sized.hpp"

namespace BlinkEngine::Render {
  class Shader {
    public:
      Shader(std::string vertpath, std::string fragpath);
      void Use();
      glm::uint32 GetId();
      void Compile();
    private:
      std::string vert;
      std::string frag;
      glm::uint32 id;
  };
}
