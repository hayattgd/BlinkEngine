#include "window/worldwindow.h"

#include "glm/ext/vector_float3.hpp"
#include "imgui.h"

#include "application.h"
#include "component/meshrenderer.h"
#include "component/camera.h"
#include "import/obj_loader.h"
#include "render/mesh.h"
#include "render/shader.h"

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
    Engine::Import::LoadObj(path.data(), &mesh);
    meshrenderer->SetMesh(mesh);
    Engine::Render::Shader *shader = new Engine::Render::Shader("res/default.vert", "res/simple.frag");
    shader->Compile();
    meshrenderer->SetShader(shader);
    world.AddComponent(world.NewEntity(), meshrenderer);
  }

  if (ImGui::Button("Add Camera")) {
    auto &world = Engine::Application::GetInstance().GetWorld();
    auto *camera = new Engine::Component::Camera(glm::vec3(0, 0, 0), 0, 0, 60, 0.1f, 100.0f);
    world.AddComponent(world.NewEntity(), camera);
  }
}

void WorldWindow::Close() { isopen = false; }

bool WorldWindow::IsOpen() const { return isopen; }
} // namespace BlinkEngine::Editor::Window
