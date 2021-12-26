//
// Created by MisThe on 2021/10/28.
//

#ifndef GAMEENGINE_ENGINESETTING_H
#define GAMEENGINE_ENGINESETTING_H

#include <stdlib.h>
#include "../CommonUtils/CommonUtils.h"

//-------structure--------
struct ShaderPath
{
    ShaderPath(std::string name,std::string path1,std::string path2,std::string path3,std::string path4):shaderName(name),vertexPath(path1),fragmentPath(path2),tessellationPath(path3),geometryPath(path4){}
    ShaderPath(std::string name,std::vector<std::string> vec)
    {
        shaderName = name;
        shaderLength = vec.size();
        if (shaderLength > 0)
            vertexPath = vec[0];
        if (shaderLength > 1)
            fragmentPath = vec[1];
        if (shaderLength > 2)
            tessellationPath = vec[2];
        if (shaderLength > 3)
            geometryPath = vec[3];
    }
    std::string shaderName;
    std::string vertexPath;
    std::string fragmentPath;
    std::string tessellationPath;
    std::string geometryPath;
    int shaderLength;
};
struct MeshPath
{
    std::string meshName;
    std::string meshPath;
};
//-------structure--------

class EngineSetting
{
public:
    enum SetType
    {
        WINDOW_HEIGHT,WINDOW_WIDTH,BACK_COLOR,SHADER_PATH,MESH_PATH
    };
public:
    static void RefreshEngineSetting();
    static float GetScreenWidth(int index = 0);
    static float GetScreenHeight(int index = 0);
    static Color GetBackColor(int index = 0);
    static std::vector<ShaderPath>* GetShaders(int index = 0);
    static std::vector<MeshPath>* GetMeshes(int index = 0);
    static std::vector<int>* GetInputSet();
    static void CheckState();
private:
    static std::vector<float> screen_width;
    static std::vector<float> screen_height;
    static bool is_ready;
    static std::string setting_path;
    static std::vector<Color> back_color;
    static std::vector<std::vector<ShaderPath>*> shader_path;
    static std::vector<std::vector<MeshPath>*> mesh_path;
    static std::vector<int>* input_set;
    static int setNum_window;
    static int setNum_shader;
    static int setNum_mesh;
};

#endif

//GAMEENGINE_ENGINESETTING_H
