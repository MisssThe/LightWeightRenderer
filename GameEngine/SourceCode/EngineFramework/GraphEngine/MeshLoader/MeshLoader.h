//
// Created by MisThe on 2021/11/26.
//

#ifndef GAMEENGINE_MESHLOADER_H
#define GAMEENGINE_MESHLOADER_H


#include "BaseLoader.h"
#include "AssimpLoader.h"

enum LoadType
{
    Any,Fbx,Obj
};

class MeshLoader
{
public:
    static GeneralMesh* Load(std::string path,LoadType type = LoadType::Any)
    {
        BaseLoader* loader = nullptr;
        switch (type)
        {
            case LoadType::Any:
                loader = new AssimpLoader();
                break;
            case LoadType::Fbx:
                break;
            case LoadType::Obj:
                break;
        }
        return loader->load(path);
    }
private:
};


#endif //GAMEENGINE_MESHLOADER_H
