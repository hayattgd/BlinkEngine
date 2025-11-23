#include "glad/glad.h"

#include "imgui.h"
#include "application.h"

using namespace BlinkEngine::Engine;

int main() {
  Application::Initialize(800, 600, "BlinkEngine Editor");
  Application& app = Application::GetInstance();

  while (app.IsRunning()) {
    ImGui::ShowDemoWindow();
    app.Update();
  }

  Application::Quit();
}
