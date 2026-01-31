#include <memory>

#include "glad/glad.h"
#include "imgui.h"

#include "application.h"
#include "ecs/world.h"
#include "gui/windowmanager.h"
#include "window/scenewindow.h"
#include "window/worldwindow.h"

using namespace BlinkEngine::Engine;
using namespace BlinkEngine::Editor;

Gui::WindowManager *windowmanager = new Gui::WindowManager();

void MenuBar(Application &app) {
  ImGui::BeginMainMenuBar();
  if (ImGui::BeginMenu("File")) {
    if (ImGui::MenuItem("Exit", "Alt + F4")) {
      app.Exit();
    }
    ImGui::EndMenu();
  }

  if (ImGui::BeginMenu("Window")) {
    if (ImGui::MenuItem("Scene")) {
      auto window = std::make_unique<Window::SceneWindow>();
      windowmanager->AddWindow(std::move(window));
    }
    if (ImGui::MenuItem("World")) {
      auto window = std::make_unique<Window::WorldWindow>();
      windowmanager->AddWindow(std::move(window));
    }
    ImGui::EndMenu();
  }

  if (ImGui::IsKeyChordPressed(ImGuiMod_Alt | ImGuiKey_F4)) {
    app.Exit();
  }
  ImGui::EndMainMenuBar();
}

int main() {
  Application::Initialize(800, 600, "BlinkEngine Editor");
  Application &app = Application::GetInstance();

  ECS::World *world = new ECS::World();

  while (app.IsRunning()) {
    ImGui::DockSpaceOverViewport();
    MenuBar(app);
    windowmanager->RenderAll();
    app.Update();
  }

  Application::Destroy();
}
