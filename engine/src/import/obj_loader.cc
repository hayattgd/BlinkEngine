#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "glm/ext/scalar_uint_sized.hpp"
#include "glm/ext/vector_float3.hpp"
#include "render/mesh.h"

using namespace BlinkEngine::Engine::Render;

namespace BlinkEngine::Engine::Import {
  bool LoadObj(const std::string& path, Mesh** out) {
    std::ifstream input(path);
    if (!input.is_open()) {
      return false;
    }

    std::vector<glm::vec3> pos;
    std::vector<glm::vec3> normal;
    std::vector<glm::vec2> uv;
    std::vector<Vertex> vertices;
    std::vector<glm::uint32> indices;

    std::string line;
    while (getline(input, line)) {
      std::istringstream ss(line);
      std::string prefix;
      ss >> prefix;

      if (prefix == "v") {
        std::string xstr;
        ss >> xstr;
        float x = std::stof(xstr);
        std::string ystr;
        ss >> ystr;
        float y = std::stof(ystr);
        std::string zstr;
        ss >> zstr;
        float z = std::stof(zstr);
        pos.emplace_back(glm::vec3(x,y,z));
      }
      else if (prefix == "vn") {
        std::string xstr;
        ss >> xstr;
        float x = std::stof(xstr);
        std::string ystr;
        ss >> ystr;
        float y = std::stof(ystr);
        std::string zstr;
        ss >> zstr;
        float z = std::stof(zstr);
        normal.emplace_back(glm::vec3(x,y,z));
      }
      else if (prefix == "vt") {
        std::string xstr;
        ss >> xstr;
        float x = std::stof(xstr);
        std::string ystr;
        ss >> ystr;
        float y = std::stof(ystr);
        uv.emplace_back(glm::vec2(x,y));
      }
      else if (prefix == "f") {
        for (int i = 0; i < 3; i++) {
          std::string vertex;
          ss >> vertex;

          std::replace(vertex.begin(), vertex.end(), '/', ' ');
          std::istringstream vs(vertex);

          int vi, ti, ni;
          vs >> vi >> ti >> ni;

          Vertex v;
          v.position = pos[vi-1];
          v.uv = uv[ti-1];
          v.normal = normal[ni-1];

          vertices.emplace_back(v);
          indices.emplace_back(vertices.size()-1);
        }
      }
    }

    *out = new Mesh(
      vertices,
      indices,
      {}
    );
    return true;
  }
}
