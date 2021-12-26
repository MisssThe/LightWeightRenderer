//
// Created by MisThe on 2021/12/5.
//

#ifndef GAMEENGINE_INPUTCONTROLLER_H
#define GAMEENGINE_INPUTCONTROLLER_H


#include <glfw3.h>
#include <iostream>
#include "../../CommonUtils/CommonUtils.h"
#include "../EngineSetting.h"

class InputController
{
public:
    static void InitInput()
    {
        CommonUtils::TraverVector<int>(EngineSetting::GetInputSet(),[](int num){
            inputMap.insert(std::pair<int,int>(num,0));
        });
    }
    static void UpdateInput(GLFWwindow*window)
    {
        CommonUtils::TraverMap<int,int>(inputMap,[&window](int index,int key){
            inputMap[index] = glfwGetKey(window,index);
        });
    }
    static bool GetKey(int key)
    {
        return inputMap[key];
    }
private:
    static std::unordered_map<int,int> inputMap;
};


#endif //GAMEENGINE_INPUTCONTROLLER_H
