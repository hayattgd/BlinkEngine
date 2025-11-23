#pragma once

#include "glm/ext/vector_float2.hpp"

namespace BlinkEngine::Engine::Input {
  class Mouse {
    public:
      void Update();
      void UpdatePosition(glm::vec2 pos);
      glm::vec2 GetCurrentPos();
      glm::vec2 GetRelativePos();
    private:
      float lastX = -1;
      float lastY;
      float currentX;
      float currentY;
      float relativeX;
      float relativeY;
  };
}
