#pragma once

// #include "../Components/ScriptComponent.hpp"
#include "../Core/Common.hpp"
#include "../Rendering/Renderer.hpp"
// #include "Entity.hpp"

namespace BillyEngine {
class Application;
class Entity;
class EntityManager {
   public:
    explicit EntityManager(Application *application);
    ~EntityManager();

    BE_NON_COPY_CONSTRUTIBLE(EntityManager)

    void Update(f64 delta);
    Entity CreateEntity(const std::string &name);
    void DestroyEntity(Entity entity);

    // template <typename T, typename... Args>
    // Entity CreateScriptableEntity(const std::string &name, Args &&...args) {
    //     auto e = CreateEntity(name);
    //     e.AddComponent<Components::Script>().Bind<T, Args...>(
    //         e, std::forward<Args>(args)...);
    //     return e;
    // }

   private:
    entt::registry m_Registry;
    Application *m_Application = nullptr;

    friend class Application;
    friend class Entity;
    friend class ScriptableEntity;
};
}  // namespace BillyEngine