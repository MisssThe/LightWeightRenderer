//
// Created by MisThe on 2021/11/15.
//

#include "ShaderController.h"

//std::unordered_map<std::string,Shader*> ShaderController::shaderMap;
ShaderController* ShaderController::shaderController = nullptr;
int ShaderController::errorNum = 0;
std::vector<std::unordered_map<std::string,Shader*>*> ShaderController::shaderVec;