//
// Created by MisThe on 2021/12/5.
//

#ifndef GAMEENGINE_INPUTCONTROLLER_H
#define GAMEENGINE_INPUTCONTROLLER_H


#include <glfw3.h>
#include <iostream>
#include "../../CommonUtils/CommonUtils.h"
#include "../EngineSetting.h"
#include "../../CommonUtils/CommonMath.h"

//管理鼠标输入
class Mouse
{
private:
    enum MoveType
    {
        SLIDE,DRAG,STOP
    };
    enum ClickType
    {
        RELEASE,LOOSE,PRESS,HOLD
    };
    static MoveType moveType;
    static ClickType clickType;
    struct ClickState
    {
        ClickType oldClick,newClick;
    };
    std::queue<std::function<void(int pos_x,int pos_y)>> clickLeftCallBack;         //鼠标左键点击回调
    std::queue<std::function<void(int pos_x,int pos_y)>> releaseLeftCallBack;       //鼠标左键松开回调
    std::queue<std::function<void(int pos_x,int pos_y)>> clickRightCallback;        //鼠标右键点击回调
    std::queue<std::function<void(int pos_x,int pos_y)>> releaseRightCallBack;      //鼠标右键松开回调
    std::queue<std::function<void(int pos_x,int pos_y)>> dragCallBack;              //鼠标拖动回调
    std::queue<std::function<void(int pos_x,int pos_y)>> sliderCallBack;            //鼠标滑动回调
    std::queue<std::function<void(int distance)>> rollCallBack;                     //鼠标滚轮回调
    std::unordered_map<int,ClickState> mouseMap;
    MoveType mouseMoveType;
    int middleClickType;
    int oldPos_x,oldPos_y,newPos_x,newPos_y;
    static Mouse*mouse;
public:
    enum ClickCallBackType
    {
        LEFT_PRESS,RIGHT_PRESS,LEFT_RELEASE,RIGHT_RELEASE
    };
public:
    static ClickType GetClick(int index)
    {
        check();
        mouse->getClick(index);
        return ClickType::RELEASE;
    }
    static void GetMousePos(int *pos_x,int *pos_y)
    {
        check();
        mouse->getMousePos(pos_x,pos_y);
    }
    static MoveType GetMouseMove()
    {
        check();
        return mouse->getMouseMove();
    }
private:
    Mouse(GLFWwindow*window)
    {
        this->mouseMap.insert(std::pair<int,ClickState>(0,{ClickType::LOOSE,ClickType::LOOSE}));    //鼠标左键
        this->mouseMap.insert(std::pair<int,ClickState>(1,{ClickType::LOOSE,ClickType::LOOSE}));    //鼠标右键
        this->middleClickType = ClickType::PRESS;
//        if (window)
//            glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
    }
    static void check(GLFWwindow*window = nullptr)
    {
        if (!mouse)
            mouse = new Mouse(window);
    }
    void update(GLFWwindow*window)
    {
        this->updateClick(window);
        this->updateClickCallBack();
//        this->updateMoveCallBack(window);
    }
    void runCallBack(std::queue<std::function<void(int pos_x,int pos_y)>> *callBackQueue)
    {
        //在update click call back里调用call back queue会报错要封装一层，不知道为啥
        if (callBackQueue)
        {
            CommonUtils::TraverQueue<std::function<void(int pos_x,int pos_y)>>(callBackQueue,[this](std::function<void(int pos_x,int pos_y)> func){
                CommonUtils::SafeCall(func, this->newPos_x, this->newPos_y);
            });
        }
    }
    void updateClick(GLFWwindow*window)
    {

        CommonUtils::TraverMap<int,ClickState>(this->mouseMap,[&window, this](int index,ClickState state){
            int click = glfwGetMouseButton(window,index);
            int oldClick = mouseMap[index].newClick;
            int newClick = click?(oldClick < ClickType::PRESS?ClickType::PRESS:ClickType::HOLD):(oldClick > ClickType::LOOSE?ClickType::RELEASE:ClickType::LOOSE);
            mouseMap[index].oldClick = ClickType(oldClick);
            mouseMap[index].newClick = ClickType(newClick);
            });
        glfwGetWindowPos(window,&this->newPos_x,&this->oldPos_y);
    }
    void updateClickCallBack()
    {
        std::queue<std::function<void(int pos_x,int pos_y)>> *leftTempQueue = nullptr,*rightTempQueue = nullptr;
        if (this->mouseMap[0].newClick == ClickType::PRESS && this->mouseMap[0].oldClick != ClickType::PRESS)
            leftTempQueue = &this->clickLeftCallBack;
        else if (this->mouseMap[0].newClick == ClickType::RELEASE && this->mouseMap[0].oldClick != ClickType::RELEASE)
            leftTempQueue = &this->releaseLeftCallBack;

        if (this->mouseMap[1].newClick == ClickType::PRESS && this->mouseMap[1].oldClick != ClickType::PRESS)
            rightTempQueue = &this->clickRightCallback;
        else if (this->mouseMap[1].newClick == ClickType::RELEASE && this->mouseMap[1].oldClick != ClickType::RELEASE)
            rightTempQueue = &this->releaseRightCallBack;

        this->runCallBack(leftTempQueue);
        this->runCallBack(rightTempQueue);
    }
    void updateMoveCallBack(GLFWwindow*window)
    {
        this->mouseMoveType = MoveType::STOP;
        if (this->oldPos_x != this->newPos_x || this->oldPos_y != this->newPos_y)
        {
            if (mouseMap[0].newClick == ClickType::HOLD)
            {
                this->mouseMoveType = MoveType::DRAG;
                CommonUtils::TraverQueue<std::function<void(int pos_x, int pos_y)>>(&dragCallBack,[this](std::function<void(int pos_x,int pos_y)> func) {
                    CommonUtils::SafeCall(func, this->oldPos_x - this->newPos_x, this->oldPos_y - this->newPos_y);
                });
            }
            else
            {
                this->mouseMoveType = MoveType::SLIDE;
                CommonUtils::TraverQueue<std::function<void(int pos_x, int pos_y)>>(&sliderCallBack,[this](std::function<void(int pos_x,int pos_y)> func) {
                    CommonUtils::SafeCall(func,this->oldPos_x - this->newPos_x,this->oldPos_y - this->newPos_y);
                });
            }
            this->oldPos_x = this->newPos_x;
            this->oldPos_y = this->newPos_y;
        }
    }
    ClickType getClick(int index)
    {
        if (this->mouseMap.find(index) != this->mouseMap.end())
        {
            return this->mouseMap[index].newClick;
        }
    }
    void getMousePos(int*pos_x,int*pos_y)
    {
        *pos_x = this->newPos_x;
        *pos_y = this->newPos_y;
    }
    MoveType getMouseMove()
    {
        return this->mouseMoveType;
    }
protected:
    static void AddClickCallBack(ClickCallBackType type,std::function<void(int pos_x,int pos_y)> func)
    {
        check();
        switch (type) {
            case ClickCallBackType::LEFT_PRESS:
                mouse->clickLeftCallBack.push(func);
                break;
            case ClickCallBackType::RIGHT_PRESS:
                mouse->clickRightCallback.push(func);
                break;
            case ClickCallBackType::LEFT_RELEASE:
                mouse->releaseLeftCallBack.push(func);
                break;
            case ClickCallBackType::RIGHT_RELEASE:
                mouse->releaseRightCallBack.push(func);
                break;
            default:
                GameLog::LogError("AddMouseCallBack","invalid mouse call back type");
        }
    }
    static void PrivateUpdate(GLFWwindow*window)
    {
        //根据鼠标状态调用回调
        check(window);
        mouse->update(window);
    }
};
//管理键盘输入
class KeyBoard
{

};
//管理用户输入
class InputController
{
public:
    static void Init()
    {
    }
    static void Update(GLFWwindow*window)
    {
        PrivateMouse::Update(window);
    }
    static bool GetKey(int key)
    {
//        return keyboardInputMap[key];
    }
    static void AddMouseCallBackLeftPress(std::function<void(int pos_x,int pos_y)> func)
    {
        PrivateMouse::AddCallBack(PrivateMouse::ClickCallBackType::LEFT_PRESS,func);
    }
    static void AddMouseCallBackRightPress(std::function<void(int pos_x,int pos_y)> func)
    {
        PrivateMouse::AddCallBack(PrivateMouse::ClickCallBackType::RIGHT_PRESS,func);
    }
    static void AddMouseCallBackLeftRelease(std::function<void(int pos_x,int pos_y)> func)
    {
        PrivateMouse::AddCallBack(PrivateMouse::ClickCallBackType::LEFT_RELEASE,func);
    }
    static void AddMouseCallBackRightRelease(std::function<void(int pos_x,int pos_y)> func)
    {
        PrivateMouse::AddCallBack(PrivateMouse::ClickCallBackType::RIGHT_RELEASE,func);
    }
private:
    static std::unordered_map<int,int> keyboardInputMap;
    static std::unordered_map<int,int> mouseInputMap;
    class PrivateMouse : public Mouse
    {
    public:
        static void AddCallBack(ClickCallBackType type,std::function<void(int pos_x,int pos_y)> func)
        {
            AddClickCallBack(type,func);
        }
        static void Update(GLFWwindow*window)
        {
            PrivateUpdate(window);
        }
    };
    class privateKeyBoard : public KeyBoard
    {

    };
};


#endif //GAMEENGINE_INPUTCONTROLLER_H
