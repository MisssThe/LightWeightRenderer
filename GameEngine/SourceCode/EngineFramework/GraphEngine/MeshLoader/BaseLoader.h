//
// Created by MisThe on 2021/11/26.
// loader只负责加载顶点，由mesh controller管理
//

#ifndef GAMEENGINE_BASELOADER_H
#define GAMEENGINE_BASELOADER_H


#include "../../../CommonUtils/CommonUtils.h"
#include "../../../CommonUtils/CommonMath.h"
#include <glm/glm.hpp>
struct AttriStruct
{
public:
    int vertexNum  = 3;
    int offset     = 3;
    long initOffset = 3;
};
struct GeneralMesh
{
public:
    float*vertex;
    unsigned int*index;
    int vertexSize;
    int indexSize;
    std::vector<AttriStruct> attriVec;
};

class BaseLoader
{
protected:
    struct Vertex
    {
    public:
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec3 tangent;
        glm::vec4 color;
        glm::vec2 texcoord;
        glm::vec4 standby1;
        glm::vec4 standby2;
        glm::vec4 standby3;
    public:
        int addStandby(glm::vec4 value,int index = 0)
        {
            index = CommonMath::Saturate(index,0,3);
            switch (index) {
                case 0:
                    standby1 = value;
                    break;
                case 1:
                    standby2 = value;
                    break;
                case 2:
                    standby3 = value;
                    break;
            }
            return CommonMath::Saturate(++index,0,3);
        }
    };
public:
    struct Index
    {
    public:
        std::vector<unsigned int> indices;
    };
    struct TempMesh
    {
    public:
        void addVertex(Vertex vertex)
        {
            vertexVec.push_back(vertex);
        }
        void addIndex(unsigned int index)
        {
            indexVec.push_back(index);
        }
        Vertex operator[](int index)
        {
            if (index < vertexVec.size()) {
                return vertexVec[index];
            }
            GameLog::LogError("IndexVertex","index out of range");
            return Vertex();
        }
        std::vector<Vertex> vertexVec;
        std::vector<unsigned int> indexVec;
    };
public:
    GeneralMesh* load(std::string path)
    {
        return processMesh(loadTempMesh(path));
    }
    virtual ~BaseLoader(){}
protected:
    virtual TempMesh* loadTempMesh(std::string path) = 0;
private:
    GeneralMesh* processMesh(TempMesh*mesh)
    {
        GeneralMesh*finalMesh = new GeneralMesh();
        finalMesh->vertex = reinterpret_cast<float *>(&mesh->vertexVec[0]);
        finalMesh->index = &mesh->indexVec[0];
        finalMesh->vertexSize = mesh->vertexVec.size() * sizeof(Vertex);
        finalMesh->indexSize = mesh->indexVec.size() * sizeof(unsigned int);
        finalMesh->attriVec.push_back({3,27,0});
        finalMesh->attriVec.push_back({3,27,3});
        finalMesh->attriVec.push_back({3,27,6});
        finalMesh->attriVec.push_back({4,27,9});
        finalMesh->attriVec.push_back({2,27,13});
        finalMesh->attriVec.push_back({4,27,15});
        finalMesh->attriVec.push_back({4,27,19});
        finalMesh->attriVec.push_back({4,27,23});
        return finalMesh;
    }
};


#endif //GAMEENGINE_BASELOADER_H
