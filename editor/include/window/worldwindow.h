#pragma once

#include <string>

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

private:
  bool isopen = true;
  std::string path;
};
} // namespace BlinkEngine::Editor::Window
