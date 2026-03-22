#include <fstream>
#include <iostream>
#include <memory>

#include "glad/glad.h"
#include "imgui.h"

#include "application.h"
#include "ecs/world.h"
#include "gui/windowmanager.h"
#include "window/scenewindow.h"
#include "window/worldwindow.h"
#include "window/propertywindow.h"

using namespace BlinkEngine::Engine;
using namespace BlinkEngine::Editor;

Gui::WindowManager *windowmanager = new Gui::WindowManager();

template <typename T> void AddWindow() {
  auto window = std::make_unique<T>();
  windowmanager->AddWindow(std::move(window));
}

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
      AddWindow<Window::SceneWindow>();
    }
    if (ImGui::MenuItem("World")) {
      AddWindow<Window::WorldWindow>();
    }
    if (ImGui::MenuItem("Property")) {
      AddWindow<Window::PropertyWindow>();
    }
    ImGui::EndMenu();
  }

  if (ImGui::IsKeyChordPressed(ImGuiMod_Alt | ImGuiKey_F4)) {
    app.Exit();
  }
  ImGui::EndMainMenuBar();
}

void SaveShownWindow() {
  auto &windows = windowmanager->GetWindows();
  auto output = std::ofstream("window");
  for (const auto &window : windows) {
    output << window->GetName() << std::endl;
  }
}

void RestoreWindow() {
  auto input = std::ifstream("window");
  std::string line;
  while (getline(input, line)) {
    if (line == "Scene") {
      AddWindow<Window::SceneWindow>();
    }
    else if (line == "World") {
      AddWindow<Window::WorldWindow>();
    } else if (line == "Property") {
      AddWindow<Window::PropertyWindow>();
    }
  }
}

int main() {
  Application::Initialize(800, 600, "BlinkEngine Editor");
  Application &app = Application::GetInstance();

  ECS::World *world = new ECS::World();

  RestoreWindow();

  while (app.IsRunning()) {
    ImGui::DockSpaceOverViewport();
    MenuBar(app);
    windowmanager->RenderAll();
    app.Update();
  }

  SaveShownWindow();

  Application::Destroy();
}
