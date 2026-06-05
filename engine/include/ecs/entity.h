#pragma once

#include <cstdint>

namespace BlinkEngine::Engine::ECS {
  // Entity Id starts from 1
  // 0 = No reference
  using Entity = std::uint32_t;
}
