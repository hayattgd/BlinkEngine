#include "window/worldwindow.h"

#include "glm/ext/vector_float3.hpp"
#include "imgui.h"

#include "application.h"
#include "component/meshrenderer.h"
#include "component/camera.h"
#include "import/obj_loader.h"
#include "render/mesh.h"

namespace BlinkEngine::Editor::Window {
WorldWindow::WorldWindow() {
  path = "";
}

WorldWindow::~WorldWindow() {
}
const char *WorldWindow::GetName() { return "World"; }

void WorldWindow::Render() {
  ImGui::InputText(".obj File", path.data(), 256);
  if (ImGui::Button("Add mesh")) {
    auto &world = Engine::Application::GetInstance().GetWorld();
    auto *meshrenderer = new Engine::Component::MeshRenderer();
    Engine::Render::Mesh *mesh;
    Engine::Import::LoadObj(path, &mesh);
    meshrenderer->SetMesh(mesh);
    world.AddComponent(world.NewEntity(), meshrenderer);
  }

  if (ImGui::Button("Add Camera")) {
    auto &world = Engine::Application::GetInstance().GetWorld();
    auto *camera = new Engine::Component::Camera(glm::vec3(0, 0, 0), 0, 0, 60, 0.01f, 1000);
    world.AddComponent(world.NewEntity(), camera);
  }
}

void WorldWindow::Close() { isopen = false; }

bool WorldWindow::IsOpen() const { return isopen; }
} // namespace BlinkEngine::Editor::Window
