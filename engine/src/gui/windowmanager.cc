#include "gui/windowmanager.h"

#include <algorithm>
#include <memory>
#include <string>
#include <utility>

#include "gui/iwindow.h"
#include "imgui.h"

namespace BlinkEngine::Engine::Gui {
  void WindowManager::AddWindow(std::unique_ptr<IWindow> window) {
    windows.push_back(std::move(window));
  }

  void WindowManager::RenderAll() {
    int i = 0;
    for (auto& w : windows) {
      bool open = true;
      ImGui::PushID(i);
      std::string name(w->GetName());
      std::string name_with_id(name + "##" + std::to_string(i));
      if (ImGui::Begin(name_with_id.c_str(), &open)) {
        w->Render();
      }
      ImGui::End();
      ImGui::PopID();
      if (!open) {
        w->Close();
      }
      i++;
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
