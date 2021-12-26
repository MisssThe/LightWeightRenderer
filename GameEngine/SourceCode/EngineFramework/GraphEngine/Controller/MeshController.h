//
// Created by MisThe on 2021/11/23.
// 管理所有mesh避免产生冗余mesh
//

#ifndef GAMEENGINE_MESHCONTROLLER_H
#define GAMEENGINE_MESHCONTROLLER_H


#include "../../../CommonUtils/CommonUtils.h"
#include "../Function/Mesh.h"
#include "../../EngineSetting.h"
#include "../MeshLoader/MeshLoader.h"
#include <string>
#include <glad.h>

class MeshController
{
public:
    static MeshController* GetMeshController()
    {
        if (meshController == nullptr)
        {
            meshController = new MeshController();
        }
        return meshController;
    }
    static void InitMesh(int index)
    {
        GetMeshController()->initMesh(index);
    }
    static Mesh* AddMesh(int index,std::string meshName, GeneralMesh*tempMesh)
    {
        //判断该mesh是否存在
        Mesh *mesh = GetMesh(index,meshName);
        if (mesh != nullptr)
        {
            return mesh;
        }
        mesh = new Mesh(tempMesh);
        GetMeshController()->addMesh(index,meshName,mesh);
        if (GetMesh(index,meshName) != nullptr)
        GetMeshController()->addMesh(index, meshName, mesh);
        return nullptr;
    }
    static Mesh* AddMesh(int index,std::string meshName, Mesh*mesh)
    {
        //判断该mesh是否存在
        if (index < meshVec.size()) {
            if (meshVec[index]->find(meshName) != meshVec[index]->end())
            {
                return meshVec[index]->at(meshName);
            }
        }
        return nullptr;
    }
    static Mesh* GetMesh(int index,std::string meshName)
    {
        if (index < meshVec.size())
        {
            if (meshVec[index]->find(meshName) != meshVec[index]->end())
            {
                return meshVec[index]->at(meshName);
            }
        }
        GameLog::LogError("GetMesh","Input an incorrect index or mesh name:{"+ std::to_string(index) + "," + meshName +"}");
        return nullptr;
    }
    static void DestroyMesh(int index,std::string meshName)
    {
        if (index < meshVec.size())
        {
            meshVec[index]->erase(meshName);
        }
    }
private:
    static MeshController*meshController;
    static std::vector<std::unordered_map<std::string,Mesh*>*> meshVec;
private:
    MeshController(){}
    void addMesh(int index,std::string meshName,Mesh*mesh)
    {
        if (index < meshVec.size())
        {
            if (mesh != nullptr) {
                meshVec[index]->insert(std::pair<std::string, Mesh *>(meshName, mesh));
            }
        }
        else{
            meshVec.push_back(new std::unordered_map<std::string,Mesh*>());
            addMesh(index,meshName,mesh);
        }
    }
    void initMesh(int index)
    {
        std::vector<MeshPath>* meshPath = EngineSetting::GetMeshes(index);
        CommonUtils::TraverVector<MeshPath>(meshPath,[&index](MeshPath path){
            MeshController::AddMesh(index,path.meshName,MeshLoader::Load(path.meshPath,LoadType::Any));
        });
    }
};


#endif //GAMEENGINE_MESHCONTROLLER_H
