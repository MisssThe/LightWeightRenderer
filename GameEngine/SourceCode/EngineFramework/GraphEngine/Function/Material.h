//
// Created by MisThe on 2021/11/1.
// 控制shader的选择使用以及参数传递（材质即数据，shader即指令）
//

#ifndef GAMEENGINE_MATERIAL_H
#define GAMEENGINE_MATERIAL_H

#include "Shader.h"
#include "Mesh.h"
#include "../../EventCenter.h"
#include "../Controller/ShaderController.h"
#include "../Controller/MeshController.h"

//材质显示信息
struct DisplayInfo
{
public:
    std::string matName;
    std::vector<std::string> texturePath;
};

class Material
{
public:

public:
    //测试用
    Material(int index,int lightType = 0)
    {
        this->shader = ShaderController::GetShader(index,"UI");
        this->mesh = MeshController::GetMesh(index,"CoffeeCup");
        this->type = lightType;
    }
    Material(int index,int lightType,std::string shaderName,std::string meshName)
    {
        if (!(shaderName.empty() || meshName.empty()))
        {
            this->shader = ShaderController::GetShader(index,shaderName);
            this->mesh = MeshController::GetMesh(index,meshName);
            this->type = lightType;
        }
    }
    Material(int index,Shader*shader,int shaderType,Mesh*mesh)
    {
        if (shader != nullptr && mesh != nullptr)
        {
            this->shader = shader;
            this->type = shaderType;
            this->mesh = mesh;
        }
    }
    void render()
    {
        this->shader->Use();
        this->mesh->Use();
        glDrawElements(GL_TRIANGLES, 60000, GL_UNSIGNED_INT, 0);
    }
    int getType()
    {
        return this->type;
    }
private:
    int type;
    Shader* shader;     //一个材质只能包含一个shader，一个物体可以包含多个材质
    Mesh* mesh;       //顶点数据
    std::map<std::string,int> textureMap;
    std::map<std::string,float> dataMap;
private:

};

#endif

//GAMEENGINE_MATERIAL_H
