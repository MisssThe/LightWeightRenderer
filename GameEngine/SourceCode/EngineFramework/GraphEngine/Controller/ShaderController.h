//
// Created by MisThe on 2021/11/15.
// shader的复用率很高，用一个pool进行管理
// 需要在对应window创建好后进行编译
//

#ifndef GAMEENGINE_SHADERCONTROLLER_H
#define GAMEENGINE_SHADERCONTROLLER_H


#include "../Function/Shader.h"
#include "../../EventCenter.h"
#include "../../EngineSetting.h"

class ShaderController
{
public:
    static ShaderController* GetShaderController()
    {
        if (shaderController == nullptr)
        {
            shaderController = new ShaderController();
        }
        return shaderController;
    }
    static Shader* AddShader(int index,std::string shaderName,Shader*shader)
    {
        Shader* tempShader = GetShader(index,shaderName);
        if (tempShader == nullptr)
        {
            tempShader = GetShaderController()->addShader(index,shaderName,shader,"","");
        }
        return tempShader;
    }
    static Shader* AddShader(int index,std::string shaderName,std::string vertexPath,std::string fragmentPath)
    {
        Shader* tempShader = GetShader(index,shaderName);
        if (tempShader == nullptr)
            tempShader = GetShaderController()->addShader(index,shaderName,nullptr,vertexPath,fragmentPath);
        return tempShader;
    }
    static Shader* GetShader(int index,std::string shaderName)
    {
        if (index < shaderVec.size())
        {
            if (shaderVec[index]->find(shaderName) != shaderVec[index]->end())
            {
                return shaderVec[index]->at(shaderName);
            }
        }
        GameLog::LogError("GetShader","Input an incorrect index to get shader");
        return nullptr;
    }
    static void CompileShader(int index)
    {
        GetShaderController()->compileShaders(index);
    }
    ~ShaderController()
    {
        delete shaderController;
//        CommonUtils::TraverMap<std::string,Shader*>(shaderMap,[](std::string name,Shader*shader)
//        {
//            delete shader;
//        });
    }
private:
    static std::vector<std::unordered_map<std::string,Shader*>*> shaderVec;
    static ShaderController* shaderController;
    static int errorNum;
private:
    ShaderController(){}
    //compile之前保证window创建成功
    void compileShaders(int index)
    {
        if (index < shaderVec.size()) {
            errorNum = 0;
            std::unordered_map<std::string, Shader *> *shaderMap = shaderVec[index];
            std::vector<ShaderPath> *shaderPath = EngineSetting::GetShaders(index);
            CommonUtils::TraverVector<ShaderPath>(shaderPath, [&shaderMap](ShaderPath path) {
                switch (path.shaderLength) {
                    case 2:
                        shaderMap->insert(std::pair<std::string,Shader*>(path.shaderName,new Shader(path.shaderName,path.vertexPath,path.fragmentPath)));
                        break;
                    case 3:
                        shaderMap->insert(std::pair<std::string,Shader*>(path.shaderName,new Shader(path.shaderName,path.vertexPath,path.fragmentPath,path.tessellationPath)));
                        break;
                    case 4:
                        shaderMap->insert(std::pair<std::string,Shader*>(path.shaderName,new Shader(path.shaderName,path.vertexPath,path.fragmentPath,path.tessellationPath,path.geometryPath)));
                        break;
                }
            });
        }else
        {
            if (errorNum > 0)
            {
                GameLog::LogError("CompileShader","Input an incorrect Index");
            }
            errorNum++;
            shaderVec.push_back(new std::unordered_map<std::string,Shader*>());
            compileShaders(index);
        }
    }
    Shader* addShader(int index,std::string shaderName,Shader*shader,std::string vertexPath,std::string fragmentPath)
    {
        if (index < shaderVec.size()) {
            errorNum = 0;
            Shader* tempShader = nullptr;
            if (shader != nullptr)
            {
                tempShader = shader;
            }
            else if (!vertexPath.empty() && !fragmentPath.empty())
            {
                tempShader = new Shader(shaderName,vertexPath,fragmentPath);
            }
            shaderVec[index]->insert(std::pair<std::string,Shader*>(tempShader->getName(),tempShader));
            return tempShader;
        }else
        {
            if (errorNum > 0)
            {
                GameLog::LogError("CompileShader","Input an incorrect Index");
            }
            errorNum++;
            shaderVec.push_back(new std::unordered_map<std::string,Shader*>());
            return addShader(index,shaderName,shader,vertexPath,fragmentPath);
        }
    }
};


#endif //GAMEENGINE_SHADERCONTROLLER_H
