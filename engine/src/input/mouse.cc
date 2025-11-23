#include "input/mouse.h"

#include "glm/ext/vector_float2.hpp"

namespace BlinkEngine::Engine::Input {
  void Mouse::Update() {
    lastX = currentX;
    lastY = currentY;
    relativeX = 0;
    relativeY = 0;
  }

  void Mouse::UpdatePosition(glm::vec2 pos) {
    currentX = pos.x;
    currentY = pos.y;
    if (lastX == -1) {
      lastX = currentX;
      lastY = currentY;
    }

    relativeX = currentX - lastX;
    relativeY = currentY - lastY;
  }

  glm::vec2 Mouse::GetCurrentPos() {
    return glm::vec2(currentX, currentY);
  }

  glm::vec2 Mouse::GetRelativePos() {
    return glm::vec2(relativeX, relativeY);
  }
}
