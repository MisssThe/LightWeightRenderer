#include "EngineFramework/Engine.h"
#include "EngineFramework/ExtendEngine/Renderer.h"

int main()
{
    Engine::Set(new Renderer());
    Engine::Init();
    Engine::Run();
    return 0;
}