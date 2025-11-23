#pragma once

#include <memory>
#include <vector>

#include "gui/iwindow.h"

namespace BlinkEngine::Engine::Gui {
  class WindowManager {
    public:
      void AddWindow(std::unique_ptr<IWindow> window);
      void RenderAll();
    private:
      std::vector<std::unique_ptr<IWindow>> windows;
  };
}
