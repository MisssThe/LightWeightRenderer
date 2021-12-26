//
// Created by MisThe on 2021/11/15.
// 负责渲染路径设置
// 实现gpu阶段剔除
//

#ifndef GAMEENGINE_BASEPIPELINE_H
#define GAMEENGINE_BASEPIPELINE_H


#include "../../../CommonUtils/CommonUtils.h"
#include "../Function/Material.h"
#include "../../EventCenter.h"

class BasePipeline
{
public:
    enum RenderType
    {
        Opaque,Transparent,End
    };

    static int AddRender(int index,Material*material)
    {
        if (materialQueue.size() > index) {
            if (material != nullptr) {
                {//添加到material queue中用于渲染循环
                    std::vector<std::queue<Material*>*>* vec = materialQueue[index];
                    int type = material->getType();
                    if (vec->size() > type && type >= 0) {
                        vec->at(type)->push(material);
                    } else
                    {
                        GameLog::LogError("AddRenderInPipeline","try to add a wrong material");
                    }
                }
                {//添加到material vector中用于查找
                    materialVec.push_back(material);
                }
            }
        }
        else
        {
            AddRenderQueue();
            AddRender(index,material);
        }
        return materialVec.size();
    }
    static Material* GetMaterial(int materialId)
    {
        return materialVec[materialId];
    }
    static void Render(int index)
    {
        if (index < materialQueue.size()) {
            CommonUtils::TraverVector<std::queue<Material*>*>(materialQueue[0],[](std::queue<Material*>* queue)
            {
                CommonUtils::TraverQueue<Material*>(queue,[](Material*material)
                {
                    material->render();
                });
            });
        }
    }
    static void clearPipeline()
    {

    }
    ~BasePipeline()
    {
        clearPipeline();
    }
//    void renderLoop()
//    {
//
//    }
private:
    static std::vector<std::vector<std::queue<Material*>*>*> materialQueue;
    static std::vector<Material*> materialVec;
private:
    static void AddRenderQueue()
    {
        std::vector<std::queue<Material*>*>* tempMaterialQueue = new std::vector<std::queue<Material*>*>();
        for (int i = 0; i < RenderType::End; ++i) {
            tempMaterialQueue->push_back(new std::queue<Material*>());
        }
        materialQueue.push_back(tempMaterialQueue);
    }
};


#endif //GAMEENGINE_BASEPIPELINE_H
