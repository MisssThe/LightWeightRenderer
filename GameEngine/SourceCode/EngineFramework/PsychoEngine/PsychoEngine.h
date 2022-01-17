//
// Created by MisThe on 2021/12/5.
// 管理游戏中的物理现象
//

#ifndef GAMEENGINE_PSYCHOENGINE_H
#define GAMEENGINE_PSYCHOENGINE_H


#include "../../CommonUtils/CommonUtils.h"
#include "../GraphEngine/GraphEngine.h"
#include "InputController.h"
#include "ShortcutController.h"

class PsychoEngine
{
public:
    static void Init()
    {
        InputController::Init();
    }
    static void Run()
    {
        CommonUtils::StartThread([](){
            CommonUtils::TraverQueue<GLFWwindow*>(GraphEngine::staticWindowQueue,[](GLFWwindow*window){
                if (window == nullptr)
                {
//                    GraphEngine::UpdateWindowQueue();
                    std::cout << "size:" << GraphEngine::staticWindowQueue.size() << std::endl;
                    return;
                }
                InputController::Update(window);
                ShortcutController::Update();
            });
        }, true);
    }
    static void Pause()
    {

    }
    static void Stop()
    {

    }
};


#endif //GAMEENGINE_PSYCHOENGINE_H
