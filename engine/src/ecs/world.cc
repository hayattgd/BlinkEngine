#include "ecs/world.h"

#include "ecs/entity.h"
#include <algorithm>

namespace BlinkEngine::Engine::ECS {
Entity World::NewEntity() {
  Entity entity;
  if (!freeEntities.empty()) {
    usedEntities.push_back(freeEntities.back());
    entity = freeEntities.back();
    freeEntities.pop_back();
  } else {
    usedEntities.push_back(next);
    entity = next++;
  }

  return entity;
}

void World::DestroyEntity(Entity entity) {
  freeEntities.push_back(entity);
  usedEntities.erase(
      std::find(usedEntities.begin(), usedEntities.end(), entity));
}

const std::vector<Entity> &World::GetEntities() { return usedEntities; }

} // namespace BlinkEngine::Engine::ECS
