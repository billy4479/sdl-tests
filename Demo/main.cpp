#include <BillyEngine.hpp>

#include "TestEntity.hpp"

int main() {
    BillyEngine::Application app("Test", {1280, 720}, "assets");
    app.LoadFont("OpenSans-Regular.ttf", "OpenSans", 28);
    app.LoadFont("JetBrains Mono Regular Nerd Font Complete Mono.ttf",
                 "JetBrainsMono", 34);

    app.CreateScriptableEntity<TestEntity>("");

    auto e = app.CreateEntity("");
    e.AddComponent<BillyEngine::Components::Text>("Fixed Position",
                                                  app.GetFont("JetBrainsMono"));
    auto& t = e.GetComponent<BillyEngine::Components::Transform>();
    t.Position = app.GetSize() / 2;
    t.Anchor = BillyEngine::CenterPoint::CENTER_CENTER;

    app.Run();

    return 0;
}
