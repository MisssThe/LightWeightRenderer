//
// Created by MisThe on 2021/11/15.
// UI抽象类
//

#ifndef GAMEENGINE_BASEUI_H
#define GAMEENGINE_BASEUI_H

#include "../../EngineFramework/GraphEngine/Function/Material.h"
#include "../../EngineFramework/GraphEngine/Controller/BasePipeline.h"
#include "../../EngineFramework/GraphEngine/Controller/ShaderController.h"
#include "../Component.h"

class BaseUI : public Component
{
public:
    virtual ~BaseUI()
    {

    }
};

#endif //GAMEENGINE_BASEUI_H
