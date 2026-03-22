#pragma once

#include "ecs/entity.h"
#include "gui/iwindow.h"

namespace BlinkEngine::Editor::Window {
class WorldWindow : public Engine::Gui::IWindow {
public:
  WorldWindow();
  ~WorldWindow() override;
  const char *GetName() override;
  void Render() override;
  void Close() override;
  bool IsOpen() const override;
  static Engine::ECS::Entity GetSelectedEntity() { return selected_entity; }

private:
  bool isopen = true;
  inline static Engine::ECS::Entity selected_entity = 0;
};
} // namespace BlinkEngine::Editor::Window
