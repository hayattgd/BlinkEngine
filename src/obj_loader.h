#pragma once

#include <string>
#include <vector>

#include "render/mesh.h"

namespace BlinkEngine {
  bool LoadObj(const std::string& path, std::vector<BlinkEngine::Render::Vertex>& out);
}
