#pragma once

#include "render/mesh.h"
#include "component/camera.h"

namespace BlinkEngine::Engine::Component {
class MeshRenderer {
public:
  void Render(Camera *camera);
  void SetMesh(Render::Mesh *mesh);
  const Render::Mesh &GetMesh();

private:
  Render::Mesh *mesh;
};
} // namespace BlinkEngine::Engine::Component
