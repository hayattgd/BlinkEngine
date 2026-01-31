#pragma once

#include <algorithm>
#include <iostream>
#include <unordered_map>

#include "ecs/entity.h"
#include "ecs/icomponentstorage.h"

namespace BlinkEngine::Engine::ECS {
template <typename T> class ComponentStorage : public IComponentStorage {
public:
  T *GetComponent(Entity entity) {
	auto f = components.find(entity);
	if (f == components.end()) {
		return nullptr;
	}
	return components.at(entity);
  }

  void AddComponent(Entity entity, T* component) {
    std::cout << "[before] this=" << this
              << " &components=" << &components
              << " size=" << components.size()
              << "\n";

    auto [it, inserted] = components.try_emplace(
      entity,
      component
    );

    std::cout << "[after ] inserted=" << inserted
              << " size=" << components.size()
              << " key=" << it->first
              << " value=" << it->second
              << "\n";

    // 念のため本当に入ってるか
    auto f = components.find(entity);
    std::cout << "[find  ] " << (f != components.end())
              << "\n";
    }

  void RemoveComponent(Entity entity) override { components.erase(entity); }

private:
  std::unordered_map<Entity, T*> components;
};
} // namespace BlinkEngine::Engine::ECS
