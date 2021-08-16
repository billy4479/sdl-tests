#pragma once

#include "../Core/Common.hpp"
#include "../Entity/ScriptableEntity.hpp"

namespace BillyEngine {

namespace Components {

struct ScriptComponent {
    std::function<void()> Instantiate;
    std::function<void()> DestroyInstance;

    std::function<void(ScriptableEntity*)> OnCreate;
    std::function<void(ScriptableEntity*, f32)> OnUpdate;
    std::function<void(ScriptableEntity*)> OnDestroy;

    ~ScriptComponent() {
        if (Instance != nullptr) DestroyInstance();
    }

    template <typename T, typename... Args>
    void Bind(Entity e, Args&&... args) {
        Instantiate = [&]() {
            assert(Instance == nullptr);
            Instance = new T(e, std::forward<Args>(args)...);
        };
        DestroyInstance = [&]() {
            assert(Instance != nullptr);

            OnDestroy(Instance);
            delete static_cast<T*>(Instance);
            Instance = nullptr;
        };

        OnCreate = [&](Entity* instance) {
            assert(Instance != nullptr);

            static_cast<T*>(instance)->OnCreate();
        };
        OnUpdate = [&](Entity* instance, f32 delta) {
            assert(Instance != nullptr);

            static_cast<T*>(instance)->OnUpdate(delta);
        };
        OnDestroy = [&](Entity* instance) {
            assert(Instance != nullptr);

            static_cast<T*>(instance)->OnDestroy();
        };
    }

    ScriptableEntity* Instance = nullptr;
};
}  // namespace Components
}  // namespace BillyEngine