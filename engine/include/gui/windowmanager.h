#pragma once

#include <memory>
#include <vector>

#include "gui/iwindow.h"

namespace BlinkEngine::Engine::Gui {
  class WindowManager {
    public:
      void AddWindow(std::unique_ptr<IWindow> window);
      void RenderAll();
      std::vector<std::unique_ptr<IWindow>> &GetWindows();
    private:
      std::vector<std::unique_ptr<IWindow>> windows;
  };
}
