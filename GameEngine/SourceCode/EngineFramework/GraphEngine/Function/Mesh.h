//
// Created by MisThe on 2021/11/23.
//

#ifndef GAMEENGINE_MESH_H
#define GAMEENGINE_MESH_H

#include <glad.h>
#include "../MeshLoader/BaseLoader.h"

class Mesh
{
private:
    unsigned int VAO;
public:
    Mesh(unsigned int VAO)
    {
        this->VAO = VAO;
    }
    Mesh(GeneralMesh*tempMesh)
    {
        if (tempMesh != nullptr) {
            unsigned int VBO, EBO;
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);
            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, tempMesh->vertexSize, tempMesh->vertex, GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, tempMesh->indexSize, tempMesh->index, GL_STATIC_DRAW);
            int length = tempMesh->attriVec.size();
            for (int i = 0; i < length; ++i) {
                glVertexAttribPointer(i, tempMesh->attriVec[i].vertexNum, GL_FLOAT, GL_FALSE, tempMesh->attriVec[i].offset * sizeof(float), (void*)tempMesh->attriVec[i].initOffset);
                glEnableVertexAttribArray(i);
            }
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }
    }
    void Use()
    {
        glBindVertexArray(this->VAO);
    }
};


#endif //GAMEENGINE_MESH_H
