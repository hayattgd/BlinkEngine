#include "window/propertywindow.h"
#include "application.h"
#include "imgui.h"
#include "window/worldwindow.h"
#include <cstring>
#include <string>

namespace BlinkEngine::Editor::Window {
PropertyWindow::PropertyWindow() {
  
}

PropertyWindow::~PropertyWindow() {

}

const char *PropertyWindow::GetName() { return "Property"; }

void PropertyWindow::Render() {
  if (WorldWindow::GetSelectedEntity() == 0) { return; }
  char *entity_name = new char[256]();
  std::strcpy(entity_name, Engine::Application::GetInstance().GetWorld().GetName(WorldWindow::GetSelectedEntity()).c_str());
  ImGui::Text("Name: ");
  ImGui::SameLine();
  ImGui::InputText("##NameInput", entity_name, 256);
  Engine::Application::GetInstance().GetWorld().SetName(WorldWindow::GetSelectedEntity(), std::string(entity_name));
}

void PropertyWindow::Close() { isopen = false; }

bool PropertyWindow::IsOpen() const { return isopen; }
}
