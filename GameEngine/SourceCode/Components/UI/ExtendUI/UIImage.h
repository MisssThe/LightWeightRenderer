//
// Created by MisThe on 2021/11/15.
//

#ifndef GAMEENGINE_UIIMAGE_H
#define GAMEENGINE_UIIMAGE_H

#include "../BaseUI.h"


class UIImage : public BaseUI
{
public:
    UIImage(int index)
    {
        BasePipeline::AddRender(index,new Material(index,0,"UI","CoffeeCup"));
    }
    void Use()
    {

    }

private:
    Material* mat;
};


#endif //GAMEENGINE_UIIMAGE_H
