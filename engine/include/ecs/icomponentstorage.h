#pragma once

#include "ecs/entity.h"

namespace BlinkEngine::Engine::ECS {
class IComponentStorage {
public:
  virtual ~IComponentStorage() = default;
  virtual void RemoveComponent(Entity entity) = 0;
};
} // namespace BlinkEngine::Engine::ECS
