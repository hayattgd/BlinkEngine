#pragma once

#include "glm/ext/scalar_uint_sized.hpp"

#include "gui/iwindow.h"

namespace BlinkEngine::Editor::Window {
class SceneWindow : public Engine::Gui::IWindow {
public:
  SceneWindow();
  ~SceneWindow() override;
  const char *GetName() override;
  void Render() override;
  void Close() override;
  bool IsOpen() const override;

private:
  bool isopen = true;
  void ResizeFrameBuffer(int w, int h);
  int width = 0;
  int height = 0;

  glm::uint32 fbo;
  glm::uint32 colorTex;
  glm::uint32 rbo;
};
} // namespace BlinkEngine::Editor::Window
