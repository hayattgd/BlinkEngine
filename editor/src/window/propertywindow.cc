#include "window/propertywindow.h"
#include "application.h"
#include "imgui.h"
#include "window/worldwindow.h"
#include <string>

namespace BlinkEngine::Editor::Window {
PropertyWindow::PropertyWindow() {
  
}

PropertyWindow::~PropertyWindow() {

}

const char *PropertyWindow::GetName() { return "Property"; }

void PropertyWindow::Render() {
  ImGui::Text("%s", Engine::Application::GetInstance().GetWorld().GetName(WorldWindow::GetSelectedEntity()).c_str());
}

void PropertyWindow::Close() { isopen = false; }

bool PropertyWindow::IsOpen() const { return isopen; }
}
