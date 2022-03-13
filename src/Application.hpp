#pragma once

#include "Core/Types.hpp"

namespace BillyEngine {

class Window;
class Renderer;
class EventManager;
class Input;
class AssetManager;

class Application {
   public:
    Application();
    ~Application();

    void Run();
    void Quit();

   private:
    Scope<Window> m_Window;
    Scope<Renderer> m_Renderer;
    Scope<EventManager> m_EventManager;
    Scope<Input> m_Input;
    Scope<AssetManager> m_AssetManager;
};

}  // namespace BillyEngine