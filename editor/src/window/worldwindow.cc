#include "window/worldwindow.h"

#include <string>

#include "component/camera.h"
#include "component/meshrenderer.h"
#include "default.h"
#include "glm/ext/vector_float3.hpp"
#include "imgui.h"

#include "ecs/world.h"
#include "application.h"
#include "import/obj_loader.h"
#include "render/mesh.h"
#include "render/shader.h"

namespace BlinkEngine::Editor::Window {
WorldWindow::WorldWindow() {
}

WorldWindow::~WorldWindow() {
}
const char *WorldWindow::GetName() { return "World"; }

void AddMesh(Engine::ECS::World& world, const std::string& data) {
  auto *meshrenderer = new Engine::Component::MeshRenderer();
  Engine::Render::Mesh *mesh;
  Engine::Import::LoadObj(data, &mesh);
  meshrenderer->SetMesh(mesh);
  auto *shader = new Engine::Render::Shader("res/default.vert", "res/simple.frag");
  shader->Compile();
  meshrenderer->SetShader(shader);
  world.AddComponent(world.NewEntity(), meshrenderer);
}

void WorldWindow::Render() {
  auto &app = Engine::Application::GetInstance();
  auto &world = app.GetWorld();

  if (ImGui::BeginPopupContextItem("right click")) {
    if (ImGui::BeginMenu("Add")) {
      if (ImGui::MenuItem("Camera")) {
	auto *camera = new Engine::Component::Camera(glm::vec3(0, 0, 0), 0, 0, 60, 0.01f, 1000.0f);
        world.AddComponent(world.NewEntity(), camera);
      }
      if (ImGui::BeginMenu("Mesh")) {
        if (ImGui::MenuItem("Cube")) {
	  AddMesh(world, CUBE_OBJ);
	}
        ImGui::EndMenu();
      }
      ImGui::EndMenu();
    }
    if (ImGui::MenuItem("Delete")) {
      world.DestroyEntity(selected_entity);
    }
    ImGui::EndPopup();
  }
  if (ImGui::IsMouseReleased(ImGuiMouseButton_Right)) {
    if (ImGui::IsWindowHovered()) {
      ImGui::OpenPopup("right click");
    }
  }
  for (auto entity : world.GetEntities()) {
    if (ImGui::Selectable(std::to_string(entity).c_str(), entity == selected_entity)) {
      selected_entity = entity;
    }
  }
}

void WorldWindow::Close() { isopen = false; }

bool WorldWindow::IsOpen() const { return isopen; }
} // namespace BlinkEngine::Editor::Window
