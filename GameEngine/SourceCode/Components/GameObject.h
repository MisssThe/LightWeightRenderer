//
// Created by MisThe on 2021/10/28.
// 游戏物体对象，所有组件的载体
// 存储组件方式（组件在运行过程中增减获取频率较高，用队列存储查找效率低但能保证有序，用map查找方便）（存储方式不会影响外界可以视情况修改）
//

#ifndef GAMEENGINE_GAMEOBJECT_H
#define GAMEENGINE_GAMEOBJECT_H

#include <queue>
#include "Component.h"

class GameObject
{
public:
    GameObject();
    ~GameObject();
    void useComponents()
    {
        //运行物体所有组件
        CommonUtils::TraverQueue<Component*>(this->comQueue,[](Component* com){
            if (com)
            {
                com->Use();
            }
            else
            {
                GameLog::LogError("UseComponents","try to use a destroyed component");
            }
        });
    }
    int addComponent(Component*com)
    {
        //添加物体组件
        return 0;
    }
    void deleteComponent(int index)
    {
        //删除物体组件
        CommonUtils::TraverQueueBool<Component*>(&this->comQueue,[&index](Component* com)->bool {
            if (com->getIndex() == index)
            {
                return false;
            }
            return true;
        });
    }
    Component* getComponent(int index)
    {
        //获取物体组件
        Component* temp = nullptr;
        CommonUtils::TraverQueue<Component*>(&this->comQueue,[&index, &temp](Component* com){
            if (com->getIndex() == index)
            {
                temp = com;
            }
        });
        return temp;
    }
    int length()
    {
        //获取组件长度
        return 0;
    }
    void destroy()
    {
        //销毁物体
        this->isAlive = false;
    }

    void Begin()
    {
        this->begin();
    }
    bool Update()
    {
        this->update();
        return this->isAlive;
    }
    void End()
    {
        this->end();
        this->destroyed = true;
    }
protected:
    //---------------生命周期--------------------
    virtual void begin() = 0;
    virtual void update() = 0;
    virtual void end() = 0;
    //---------------生命周期--------------------
private:
    std::queue<Component*> comQueue;
    bool isAlive = true;
    bool destroyed = false;
private:

};


#endif

//GAMEENGINE_GAMEOBJECT_H
