//
// Created by MisThe on 2021/11/29.
//

#ifndef GAMEENGINE_COFFEECUP_H
#define GAMEENGINE_COFFEECUP_H

#include "SceneObject.h"
#include "../../SourceCode/EngineFramework/GraphEngine/Controller/BasePipeline.h"

class CoffeeCup : public SceneObject
{
public:
    void load(int index)
    {
        BasePipeline::AddRender(index,new Material(index));
    }
private:
};


#endif //GAMEENGINE_COFFEECUP_H
