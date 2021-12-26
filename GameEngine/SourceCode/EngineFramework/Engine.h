//
// Created by MisThe on 2021/10/28.
// 包含基础图形绘制功能
// 对OpenGL功能进行封装
//

#ifndef GAMEENGINE_ENGINE_H
#define GAMEENGINE_ENGINE_H

#include "EngineSetting.h"
#include "../Components/GameObject.h"
#include "../CommonUtils/CommonUtils.h"
#include "../CommonUtils/GameLog.h"
#include "GraphEngine/GraphEngine.h"
#include "PsychoEngine/PsychoEngine.h"
#include "ExtendEngine/BaseEngine.h"

class Engine
{
public:
    static void Set(BaseEngine* engine)
    {
        baseEngine = engine;
        if (baseEngine)
            isLock = false;
    }
    static void Init()
    {
        CheckState();
        EngineSetting::RefreshEngineSetting();
        EngineSetting::RefreshEngineSetting();
        PsychoEngine::Init();
        baseEngine->use(UseType::INIT);
    }
    static void Run()
    {
        CheckState();
        baseEngine->use(UseType::RUN);
        PsychoEngine::Run();
        GraphEngine::Run();
    }
    static void Pause()
    {
        CheckState();
        baseEngine->use(UseType::PAUSE);
    }
    static void Stop()
    {
        CheckState();
        baseEngine->use(UseType::STOP);
    }
private:
    Engine(){}
    static void CheckState()
    {
        if (isLock)
        {
            GameLog::LogError("Engine","base engine is not ready");
        }
    }
private:
    static Engine*engine;
    static BaseEngine*baseEngine;
    static bool isLock;
};

#endif
//GAMEENGINE_ENGINE_H
