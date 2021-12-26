//
// Created by MisThe on 2021/11/15.
// 对ui做布局排列
//

#ifndef GAMEENGINE_UILAYOUT_H
#define GAMEENGINE_UILAYOUT_H


#include "../../CommonUtils/CommonUtils.h"
#include "BaseUI.h"
#include "ExtendUI/UIImage.h"
#include "ExtendUI/UIText.h"

class UILayout : public BaseUI
{
    struct LayoutStruct
    {
        bool  isPoint    = true;    //间隔距离是否按中心点计算
        float space      = 0;       //间隔距离
        bool  isVertical = true;    //是否垂直布局
    };
public:
    explicit UILayout(std::string name,int index = 0,bool needDestroy = false)
    {
        this->needDestroy = needDestroy;
        this->name = name;
        this->isFold = false;
        this->isAddUI = true;
        this->index = index;
    }
    void fold(bool flag)
    {
        this->isFold = flag;
    }
    void Use()
    {
        if (this->isFold)
        {
            CommonUtils::TraverVector<BaseUI*>(this->uiVec,[](BaseUI*ui)
            {
                ui->Use();
            });
        }
    }
    ~UILayout()
    {
        CommonUtils::TraverVector<BaseUI*>(this->uiVec,[](BaseUI*ui)
        {
            delete ui;
        });
        this->uiVec.clear();
    }
    //两种加载方法不可以在一个layout上同时使用
    void addUI(BaseUI* ui)
    {
        if (this->isAddUI) {
            if (ui != nullptr) {
                this->uiVec.push_back(ui);
            }
        } else
        {
            GameLog::LogError("LayoutAddUI","try to add ui in wrong way");
        }
    }
    void addImage()
    {
        this->addDestroyUI(new UIImage(index));
    }
    void addText()
    {
//        this->addDestroyUI(new UIText(index));
    }
private:
    std::vector<BaseUI*> uiVec;
    std::string name;
    bool needDestroy;
    bool isFold;
    bool isAddUI;
    int  index;
private:
    void addDestroyUI(BaseUI*ui)
    {
        this->isAddUI = true;
        this->addUI(ui);
        this->needDestroy = true;
        this->isAddUI = false;
    }
};

#endif
//GAMEENGINE_UILAYOUT_H