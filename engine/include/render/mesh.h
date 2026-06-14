#pragma once

#include <string>
#include <vector>

#include "glm/ext/scalar_uint_sized.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/ext/vector_float2.hpp"

#include "render/shader.h"

namespace BlinkEngine::Engine::Render {
struct Vertex {
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec2 uv;
};

struct Texture {
  glm::uint32 id;
  std::string type;
};

class Mesh {
public:
  Mesh(std::vector<Vertex> vertices, std::vector<glm::uint32> indices, std::vector<Texture> textures);
  void Draw(Render::Shader* shader);
private:
  void SetupMesh();
  std::vector<Vertex> vertices;
  std::vector<glm::uint32> indices;
  std::vector<Texture> textures;

  glm::uint32 vao, vbo, ebo;
};
}
