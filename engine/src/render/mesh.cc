#include "render/mesh.h"

#include <cstddef>
#include <string>
#include <vector>

#include "glad/glad.h"
#include <GL/gl.h>
#include <GL/glext.h>
#include "glm/ext/scalar_uint_sized.hpp"

namespace BlinkEngine::Engine::Render {
  Mesh::Mesh(std::vector<Vertex> vertices, std::vector<glm::uint32> indices, std::vector<Texture> textures) {
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    SetupMesh();
  }

  void Mesh::SetupMesh() {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(glm::uint32), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
    glEnableVertexAttribArray(2);
  }

  void Mesh::Draw() {
    glm::uint32 diffuse_nr = 1;
    glm::uint32 specular_nr = 1;
    for (unsigned int i = 0; i < textures.size(); i++) {
      glActiveTexture(GL_TEXTURE0 + i);

      std::string number;
      std::string name = textures[i].type;
      if(name == "texture_diffuse") {
        number = std::to_string(diffuse_nr++);
      } else if(name == "texture_specular") {
        number = std::to_string(specular_nr++);
      }

      glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    glActiveTexture(GL_TEXTURE0);
    glEnableClientState(GL_VERTEX_ARRAY);

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
  }
}
