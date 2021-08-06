#pragma once

#include <SDL2/SDL.h>

#include <stdexcept>

#include "Core/AssetManager.hpp"
#include "Core/Common.hpp"
#include "Core/EventHandler.hpp"
#include "Rendering/Renderer.hpp"

class Application {
   public:
    Application(std::string, i32 width, i32 height);
    ~Application();

    void Run();
    Rendering::Renderer *GetRenderer();
    AssetManager *GetAssetManager();

   private:
    bool isRunning = false;
    void AskToStop();

    static constexpr i32 FPS = 60;
    static constexpr i32 frameDelay = 1000 / FPS;

    i32 m_Height, m_Width;
    std::string m_Title;

    SDL_Window *m_Window;
    AssetManager m_AssetManager;
    Rendering::Renderer m_Renderer;
    EventHandler m_EventHandler;
};