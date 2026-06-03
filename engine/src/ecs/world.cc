#include "ecs/world.h"

#include "ecs/entity.h"
#include <algorithm>
#include <string>

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

  SetName(entity, "NewEntity");
  return entity;
}

void World::DestroyEntity(Entity entity) {
  auto entity_index = std::find(usedEntities.begin(), usedEntities.end(), entity);
  if (entity_index != usedEntities.end()) {
    freeEntities.push_back(entity);
    usedEntities.erase(entity_index);
  }
}

const std::vector<Entity> &World::GetEntities() { return usedEntities; }

void World::SetName(Entity entity, std::string name) { entityNames[entity] = name; }
const std::string &World::GetName(Entity entity) { return entityNames[entity]; }

} // namespace BlinkEngine::Engine::ECS
