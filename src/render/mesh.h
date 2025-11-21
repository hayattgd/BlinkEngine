#pragma once

#include <string>
#include <vector>

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/ext/scalar_uint_sized.hpp>

namespace BlinkEngine::Render {
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
      void Draw();
    private:
      void SetupMesh();
      std::vector<Vertex> vertices;
      std::vector<glm::uint32> indices;
      std::vector<Texture> textures;

      glm::uint32 vao, vbo, ebo;
  };
}
