//
// Created by MisThe on 2021/11/26.
// 使用assimp库进行模型导入
// 暂不支持多线程调用
//

#ifndef GAMEENGINE_ASSIMPLOADER_H
#define GAMEENGINE_ASSIMPLOADER_H

#include "BaseLoader.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class AssimpLoader : public BaseLoader
{
public:
    AssimpLoader()
    {

    }
    TempMesh* loadTempMesh(std::string path)
    {
        loadModel(path);
        return tempMesh;
    }
private:
    Vertex tempVertex;
    TempMesh* tempMesh;
private:
    void loadModel(std::string const &path)
    {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
        if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
            GameLog::LogError("AssimpLoadModel","load model failed");
        tempMesh = new TempMesh();
        processNode(scene->mRootNode, scene);
    }
    void processNode(aiNode *node, const aiScene *scene)
    {
        for(unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            processMesh(mesh);
        }
        for(unsigned int i = 0; i < node->mNumChildren; i++)
        {
            processNode(node->mChildren[i], scene);
        }

    }
    void processMesh(aiMesh* mesh)
    {
        for (int i = 0; i < mesh->mNumVertices; ++i) {
            //读取顶点坐标
            tempVertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
            //读取法线信息
            tempVertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
            //读取切线信息
            tempVertex.tangent = glm::vec3(mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z);
            //读取颜色信息以及读取纹理坐标
            if (mesh->mColors[0])
                tempVertex.color = glm::vec4(mesh->mColors[0][i].r, mesh->mColors[0][i].g, mesh->mColors[0][i].b,mesh->mColors[0][i].a);
            if (mesh->mTextureCoords[0])
                tempVertex.texcoord = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
            int tempIndex = 0;
            for (int j = 1; j < 8; ++j) {
                if (mesh->mColors[j])
                    tempIndex = tempVertex.addStandby(glm::vec4(mesh->mColors[j][i].r, mesh->mColors[j][i].g, mesh->mColors[j][i].b,mesh->mColors[j][i].a),tempIndex);
                if (mesh->mTextureCoords[j])
                    tempIndex = tempVertex.addStandby(glm::vec4(mesh->mTextureCoords[j][i].x, mesh->mTextureCoords[j][i].y,0.0f,0.0f),tempIndex);
            }
            tempMesh->addVertex(tempVertex);
        }
        for (int i = 0; i < mesh->mNumFaces; ++i) {
            aiFace face = mesh->mFaces[i];
            for (int j = 0; j < face.mNumIndices; ++j) {
                tempMesh->addIndex(face.mIndices[j]);
            }
        }
    }
};


#endif //GAMEENGINE_ASSIMPLOADER_H