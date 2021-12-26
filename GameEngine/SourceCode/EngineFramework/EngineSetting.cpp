//
// Created by 谭地杰 on 2021/10/28.
//

#include "EngineSetting.h"

//----------------------------------   static element   ----------------------------------
std::vector<float> EngineSetting::screen_width = std::vector<float>();
std::vector<float> EngineSetting::screen_height = std::vector<float>();
std::string EngineSetting::setting_path = "SourceCode/SystemDocuments/engine_setting.json";
std::vector<Color> EngineSetting::back_color = std::vector<Color>();
std::vector<std::vector<ShaderPath>*> EngineSetting::shader_path;
std::vector<std::vector<MeshPath>*> EngineSetting::mesh_path = std::vector<std::vector<MeshPath>*>();
std::vector<int>* EngineSetting::input_set = new std::vector<int>();
int EngineSetting::setNum_window = 0;
int EngineSetting::setNum_shader = 0;
int EngineSetting::setNum_mesh = 0;
//----------------------------------   static element   ----------------------------------


void EngineSetting::RefreshEngineSetting()
{
    std::string project_path = "/Users/tandijie/LightWeightRenderer/GameEngine/";
    Json::Value setting = CommonUtils::ReadJson(project_path + setting_path);
    //process property
    Json::Value window_set     = setting["window_set"];
    Json::Value shader_set     = setting["shader_path"];
    Json::Value mesh_set       = setting["mesh_path"];
    Json::Value temp_input_set = setting["input_set"];
    setNum_window = window_set.size();
    setNum_shader = shader_set.size();
    setNum_mesh   = mesh_set.size();
    Json::Value tempSet;
    for (int i = 0; i < setNum_window; ++i) {
        tempSet = window_set["set_" + std::to_string(i)];
        screen_width.push_back(tempSet["screen_width"].asFloat());
        screen_height.push_back(tempSet["screen_height"].asFloat());
        back_color.push_back(Color(tempSet["back_color"].asString()));
    }
    Json::Value::Members names;
    std::vector<std::string> pathVec;
    for (int i = 0; i < setNum_shader; ++i) {
        tempSet = shader_set["path_"+ std::to_string(i)];
        shader_path.push_back(new std::vector<ShaderPath>());
        names = tempSet.getMemberNames();
        for (auto name : names) {
            {
                std::vector<std::string> tempVec;
                pathVec.swap(tempVec);
            }
            for (int j = 0; j < tempSet[name].size(); ++j) {
                pathVec.push_back(project_path + tempSet[name][j].asString());
            }
            shader_path[i]->push_back(ShaderPath(name,pathVec));
        }
    }
    for (int i = 0; i < setNum_mesh; ++i) {
        tempSet = mesh_set["path_" + std::to_string(i)];
        names = tempSet.getMemberNames();
        mesh_path.push_back(new std::vector<MeshPath>);
        for (auto name:names) {
            mesh_path[i]->push_back({name,project_path + tempSet[name].asString()});
        }
    }
    int length = temp_input_set.size();
    for (int i = 0; i < length; ++i) {
        input_set->push_back(temp_input_set[i].asInt());
    }
}


float EngineSetting::GetScreenWidth(int index)
{
    if (index < setNum_window)
    {
        return screen_width[index];
    }
    return 0;
}

float EngineSetting::GetScreenHeight(int index)
{
    if (index < setNum_window)
    {
        return screen_height[index];
    }
    return 0;
}

void EngineSetting::CheckState()
{
//    if (isReady)
//    {
//        exit(0);
//    }
}

Color EngineSetting::GetBackColor(int index)
{
    if (index < setNum_window)
    {
        return back_color[index];
    }
    return Color();
}

std::vector<ShaderPath>* EngineSetting::GetShaders(int index) {
    if (index < setNum_shader)
        return shader_path[index];
    return new std::vector<ShaderPath>();
}

std::vector<MeshPath> *EngineSetting::GetMeshes(int index) {
    if (index < setNum_mesh)
        return mesh_path[index];
    return new std::vector<MeshPath>();
}

std::vector<int> *EngineSetting::GetInputSet() {
    return input_set;
}


