#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "render/mesh.h"

using namespace BlinkEngine::Render;

namespace BlinkEngine {
  bool LoadObj(const std::string& path, std::vector<Vertex>& out) {
    std::ifstream input(path);
    if (!input.is_open()) {
      return false;
    }

    std::vector<Vertex> vertices;

    std::string line;
    while (getline(input, line)) {
      std::istringstream ss(line);
      std::string prefix;
      ss >> prefix;

      if (prefix == "v") {

      }
    }
    return true;
  }
}
