#pragma once

#include <string>

#include "render/mesh.h"

namespace BlinkEngine::Engine::Import {
  bool LoadObj(const std::string& path, BlinkEngine::Engine::Render::Mesh** out);
}
