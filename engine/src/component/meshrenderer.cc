#include "component/meshrenderer.h"

#include "component/camera.h"

namespace BlinkEngine::Engine::Component {
void MeshRenderer::Render(Camera *camera) {
    mesh->Draw();
}
void MeshRenderer::SetMesh(Render::Mesh *mesh) { this->mesh = mesh; }
const Render::Mesh &MeshRenderer::GetMesh() { return *mesh; }
} // namespace BlinkEngine::Engine::Component
