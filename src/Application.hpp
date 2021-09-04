#pragma once

#define SDL_MAIN_HANDLED

#include "Core/AssetManager.hpp"
#include "Core/Common.hpp"
#include "Core/EventHandler.hpp"
#include "Entity/EntityManager.hpp"
#include "Rendering/Renderer.hpp"
#include "Window/Window.hpp"
#include "Wrappers/Fwd.hpp"

namespace BillyEngine {
class DrawableTexture;
class Application {
   public:
    Application(std::string_view title, i32 width, i32 height,
                const std::filesystem::path &assetsPath = "")
        : Application(title, {width, height}, assetsPath) {}
    Application(std::string_view title, glm::ivec2 size,
                const std::filesystem::path &assetsPath = "");
    ~Application();

   public:
    void Run();
    inline f32 GetFPS() const { return m_ActualFps; };
    DrawableTexture CreateDrawableTexture(glm::ivec2 size);
    void AskToStop();

   public:
    /*** EntityManager proxy ***/

    /**
     * @brief Create a Scriptable Entity
     *
     * @note
     * T must implement `void OnCreate()`, `void OnUpdate(f32)` and
     * `void OnDestroy()`
     *
     * @tparam T The type of the Scriptable Entity
     * @tparam Args The types of parameters for the constructor of T, deduced
     * @param name The name of the new entity (tag component)
     * @param args Other parameters for the constructor of T
     * @return The created Entity
     */
    template <typename T, typename... Args>
    inline Entity CreateScriptableEntity(const std::string &name,
                                         Args &&...args) {
        return m_EntityManager.CreateScriptableEntity<T>(
            name, std::forward<Args>(args)...);
    }

    /**
     * @brief Create a new Entity
     *
     * @param name The name of the new Entity (tag component)
     * @return The created entity
     */
    inline Entity CreateEntity(const std::string &name) {
        return m_EntityManager.CreateEntity(name);
    }

    /**
     * @brief Destroy an Entity
     *
     * @param entity The Entity to destroy
     */
    inline void DestroyEntity(Entity entity) {
        m_EntityManager.DestroyEntity(entity);
    }

   public:
    /*** AssetManager proxy ***/

    /**
     * @brief Set the assets folder
     *
     * When a call to functions which load assets is done (e.g.: `LoadFont` or
     * `LoadImage`) this will be used as base path.
     *
     * @note The path is relative to the executable location
     *
     * @param path The path to the folder (can be relative or absolute)
     */
    inline void SetAssetFolder(const std::filesystem::path &path) {
        m_AssetManager.SetAssetFolder(path);
    }

    /**
     * @brief Get the asset folder path
     *
     * This returns the current base path used when calling functions which load
     * assets (e.g.: `LoadFont` or `LoadImage`).
     *
     * @return std::filesystem::path The current assets path
     */
    inline std::filesystem::path GetAssetFolder() {
        return m_AssetManager.GetAssetFolder();
    }

    /**
     * @brief Load a TTF font
     *
     * @note path is relative to the assets folder
     *
     * @param path Relative path of the ttf file
     * @param name The name this font will have
     * @param size The size in pt
     * @return TTF_Font* The loaded font
     */
    inline Ref<Font> LoadFont(const std::filesystem::path &path,
                              const std::string &name, u32 size) {
        return m_AssetManager.LoadFont(path, name, size);
    }

    /**
     * @brief Get a font loaded previously using `LoadFont`
     *
     * @param name The name used when the font was loaded
     * @return TTF_Font* The font
     */
    inline Ref<Font> GetFont(const std::string &name) {
        return m_AssetManager.GetFont(name);
    }

    // TODO: maybe return a DrawableTexture?

    /**
     * @brief Load an image file (png or jpg)
     *
     * @param path Relative path to the image file
     * @param name The name this image will have
     * @return SDL_Surface* A surface containing the loaded image data
     */
    inline Ref<Surface> LoadImage(const std::filesystem::path &path,
                                  const std::string name) {
        return m_AssetManager.LoadImage(path, name);
    }

    /**
     * @brief Get a previously loaded image using `LoadImage`
     *
     * @param name The name used when the image was loaded
     * @return SDL_Surface* The image surface
     */
    inline Ref<Surface> GetImage(const std::string &name) {
        return m_AssetManager.GetImage(name);
    }

   public:
    /*** Window proxy ***/

    /**
     * @brief Get the window size
     *
     * @return const glm::ivec2 The window size
     */
    inline const glm::ivec2 GetSize() const { return m_Window.GetSize(); }

    /**
     * @brief Set the window title
     *
     * @param title The new title
     */
    inline void SetTitle(std::string_view title) { m_Window.SetTitle(title); }

   private:
    bool isRunning = false;
    void OnUpdate(f64);
    Ref<Renderer> GetRenderer();

   private:
    static constexpr f32 FPS = 60;
    static constexpr auto frameDelay =
        std::chrono::microseconds((u64)(1000000.0 / FPS));

    f64 m_ActualFps = 0;

   private:
    AssetManager m_AssetManager;
    Ref<Renderer> m_Renderer = nullptr;
    EventHandler m_EventHandler;
    EntityManager m_EntityManager;
    Window m_Window;

    friend class Entity;
    friend class EntityManager;
    friend class AssetManager;
};
}  // namespace BillyEngine