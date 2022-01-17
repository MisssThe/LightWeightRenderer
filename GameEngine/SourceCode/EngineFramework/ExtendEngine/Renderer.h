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
#include "../PsychoEngine/InputController.h"

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

public:
    int index;
};

class Renderer : public BaseEngine
{
protected:
    void init() override {
        //创建基础窗口
        this->index1 = GraphEngine::AddWindow(0);
        this->index2 = GraphEngine::AddWindow(1);
        //设置按键回调
        InputController::AddMouseCallBackLeftPress([](int pos_x,int pos_y){
            std::cout << "0";
        });
    }

    void run() override {

    }

    void pause() override {

    }

    void stop() override {

    }
private:
    int index1,index2;
};


#endif //GAMEENGINE_RENDERER_H
