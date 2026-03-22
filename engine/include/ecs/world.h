#pragma once

#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>

#include "ecs/componentstorage.h"
#include "ecs/entity.h"
#include "ecs/icomponentstorage.h"

namespace BlinkEngine::Engine::ECS {
class World {
public:
  World() = default;
  World(const World&) = delete;
  World& operator=(const World&) = delete;
  World(World&&) = default;
  World& operator=(World&&) = default;

  Entity NewEntity();
  void DestroyEntity(Entity entity);
  const std::vector<Entity> &GetEntities();
  template <typename T> void AddComponent(Entity entity, T* component) {
    auto &storage = GetOrCreateComponentStorage<T>();
    if (!storage) {
        return;
    }
    std::shared_ptr<ComponentStorage<T>> ptr =
        std::static_pointer_cast<ComponentStorage<T>>(storage);
    ptr.get()->AddComponent(entity, component);
  }
  template <typename T> void RemoveComponent(Entity entity) {
    auto &storage = components.at(typeid(T));
    if (!storage) {
      return;
    }
    storage->RemoveComponent(entity);
  }
  template <typename T> T *GetComponent(Entity entity) {
    auto &storage = GetOrCreateComponentStorage<T>();
    if (!storage) {
      return nullptr;
    }
    std::shared_ptr<ComponentStorage<T>> ptr =
        std::static_pointer_cast<ComponentStorage<T>>(storage);
    return ptr.get()->GetComponent(entity);
  }

private:
template <typename T>

std::shared_ptr<IComponentStorage>& GetOrCreateComponentStorage()
{

  auto [it, inserted] = components.try_emplace(
    std::type_index(typeid(T)),
    std::make_shared<ComponentStorage<T>>()
  );

  return it->second;
}
  std::unordered_map<std::type_index, std::shared_ptr<IComponentStorage>>
      components;
  std::vector<Entity> freeEntities;
  std::vector<Entity> usedEntities;
  Entity next = 1;
};
} // namespace BlinkEngine::Engine::ECS
