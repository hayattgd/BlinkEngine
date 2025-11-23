#include "gui/windowmanager.h"

#include <algorithm>
#include <memory>
#include <utility>

#include "gui/iwindow.h"
#include "imgui.h"

namespace BlinkEngine::Engine::Gui {
  void WindowManager::AddWindow(std::unique_ptr<IWindow> window) {
    windows.push_back(std::move(window));
  }

  void WindowManager::RenderAll() {
    for (auto& w : windows) {
      bool open = true;
      ImGui::Begin(w->GetName(), &open);
      w->Render();
      ImGui::End();
      if (!open) {
        w->Close();
      }
    }

    windows.erase(
      std::remove_if(
        windows.begin(),
        windows.end(),
        [](auto& w){ return !w->IsOpen(); }
      ),
      windows.end()
    );
  }
}
