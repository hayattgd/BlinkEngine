#pragma once

#include <string>

#include "render/mesh.h"

namespace BlinkEngine {
  bool LoadObj(const std::string& path, BlinkEngine::Render::Mesh** out);
}
