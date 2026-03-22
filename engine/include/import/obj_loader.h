#pragma once

#include <string>

#include "render/mesh.h"

namespace BlinkEngine::Engine::Import {
  bool LoadObjFromPath(const std::string &path, BlinkEngine::Engine::Render::Mesh **out);
  bool LoadObj(const std::string &data, BlinkEngine::Engine::Render::Mesh **out);
}
