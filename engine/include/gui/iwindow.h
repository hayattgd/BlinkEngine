#pragma once

namespace BlinkEngine::Engine::Gui {
  class IWindow {
    public:
      virtual ~IWindow() = default;
      virtual const char* GetName() = 0;
      virtual void Render() = 0;
      virtual void Close() = 0;
      virtual bool IsOpen() const = 0;
  };
}
