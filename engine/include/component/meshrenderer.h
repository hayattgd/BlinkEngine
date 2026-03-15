#pragma once

#include "render/mesh.h"
#include "component/camera.h"
#include "render/shader.h"

namespace BlinkEngine::Engine::Component {
class MeshRenderer {
public:
  void Render(Camera *camera);
  void SetMesh(Render::Mesh *mesh);
  void SetShader(Render::Shader *shader);
  const Render::Mesh &GetMesh();

private:
  Render::Mesh *mesh;
  Render::Shader *shader;
};
} // namespace BlinkEngine::Engine::Component
