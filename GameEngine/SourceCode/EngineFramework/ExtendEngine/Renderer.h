//
// Created by MisThe on 2021/12/18.
// 实现渲染器基本功能
// 由两个场景构成（展示场景以及面板场景）
//

#ifndef GAMEENGINE_RENDERER_H
#define GAMEENGINE_RENDERER_H


#include "BaseEngine.h"
#include "../../Components/UI/ExtendUI/UIImage.h"
#include "../GraphEngine/GraphEngine.h"

//物体面板展示场景
class AttriWindow
{
public:
    AttriWindow()
    {
        this->index = GraphEngine::AddWindow(1);
        UIImage image(this->index);
    }

private:
    int index;
};

//物体展示场景
class ShowWindow
{
public:
    ShowWindow()
    {
        this->index = GraphEngine::AddWindow(0);
        UIImage uiImage(this->index);
    }
    void AddObject(GameObject obj)
    {

    }
public:
    int index;
};

class Renderer : public BaseEngine
{
protected:
    void init() override {
        ShowWindow sw;
        AttriWindow aw;
    }

    void run() override {

    }

    void pause() override {

    }

    void stop() override {

    }
};


#endif //GAMEENGINE_RENDERER_H
