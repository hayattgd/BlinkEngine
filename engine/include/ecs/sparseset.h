#pragma once

#include <cstddef>
#include <vector>

namespace BlinkEngine::Engine::ECS {
template <typename T> class SparseSet {
public:
  T &Get(std::size_t e) { return packed[sparse[e]]; }

  void Add(std::size_t e, T component) {
    if (e >= sparse.size()) {
      sparse.resize(e + 1, invalidIndex);
    }
    sparse[e] = packed.size();
    entities.push_back(e);
    packed.push_back(component);
  }

  void Remove(std::size_t e) {
    if (e >= sparse.size()) {
      return;
    }
    size_t index = sparse[e];
    if (index == invalidIndex) {
      return;
    }
    size_t last = packed.size() - 1;
    if (index != last) {
      // swap packed index <-> last
      // now "index" points to data, which was at last of packed array
      // previously
      packed[index] = packed[last];
      // fix that swapped ones index
      sparse[entities[last]] = index;
      entities[index] = last;
    }
    packed.pop_back();
    entities.pop_back();
    sparse[e] = invalidIndex;
  }

private:
  static constexpr size_t invalidIndex = static_cast<size_t>(-1);
  // id -> packed
  std::vector<std::size_t> sparse;
  // packed idx -> id
  std::vector<std::size_t> entities;
  std::vector<T> packed;
};
} // namespace BlinkEngine::Engine::ECS
