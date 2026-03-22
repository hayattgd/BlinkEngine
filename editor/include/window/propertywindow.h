#pragma once

#include "gui/iwindow.h"

namespace BlinkEngine::Editor::Window {
class PropertyWindow : public Engine::Gui::IWindow {
public:
  PropertyWindow();
  ~PropertyWindow();
  const char *GetName() override;
  void Render() override;
  void Close() override;
  bool IsOpen() const override;

private:
  bool isopen = true;
};
}
