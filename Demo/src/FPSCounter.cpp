#include "FPSCounter.hpp"

void FPSCounter::OnCreate() {
    AddComponent<BillyEngine::Components::Text>("", App().GetFont("OpenSans"));
    auto &t = GetComponent<BillyEngine::Components::Transform>();
    t.Position = {App().GetSize().x - 10, 5};

    App().RegisterEventListenerFor<BillyEngine::WindowResizeEvent>(
        [&](BillyEngine::WindowResizeEvent &) -> bool {
            GetComponent<BillyEngine::Components::Transform>().Position = {
                App().GetSize().x - 10, 5};
            return false;
        });

    t.Anchor = BillyEngine::CenterPoint::TOP_RIGHT;
}

void FPSCounter::OnUpdate(f32) {
    std::stringstream ss;
    ss << "FPS: " << App().GetFPS();

    GetComponent<BillyEngine::Components::Text>().SetText(ss.str());
}