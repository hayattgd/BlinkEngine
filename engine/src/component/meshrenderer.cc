#include "component/meshrenderer.h"

#include "component/camera.h"

namespace BlinkEngine::Engine::Component {
void MeshRenderer::Render(Camera *camera) {
  shader->UniformBlockBinding("Matrices", camera->GetUniformBufferBindingPoint());
  mesh->Draw(shader);
}
void MeshRenderer::SetMesh(Render::Mesh *mesh) { this->mesh = mesh; }
void MeshRenderer::SetShader(Render::Shader *shader) { this->shader = shader; }
const Render::Mesh &MeshRenderer::GetMesh() { return *mesh; }
} // namespace BlinkEngine::Engine::Component
