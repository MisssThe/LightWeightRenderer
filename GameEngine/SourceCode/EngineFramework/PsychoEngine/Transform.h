//
// Created by MisThe on 2021/11/18.
// 定义物体基础属性（大小，位置，方向）
//

#ifndef GAMEENGINE_TRANSFORM_H
#define GAMEENGINE_TRANSFORM_H


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../../CommonUtils/CommonMath.h"

class Transform
{
public:
    Transform(glm::vec3 translation = glm::vec3(0.0f),glm::vec3 rotation = glm::vec3(0.0f),glm::vec3 scaling = glm::vec3(0.0f))
    {
        this->translate(translation);
        this->rotate(rotation);
        this->scale(scaling);
    }
    void translate(glm::vec3 translation)
    {
        if (!CommonMath::IsZero(translation))
        {
            this->position += translation;
            this->modelMatrix = glm::translate(this->modelMatrix,translation);
        }
    }
    void rotate(glm::vec3 rotation)
    {
        if (!CommonMath::IsZero(rotation))
        {
            //外部旋转z->y->x
            this->rotation += rotation;
            this->modelMatrix = glm::rotate(this->modelMatrix,rotation.z,glm::vec3(0,0,1));
            this->modelMatrix = glm::rotate(this->modelMatrix,rotation.y,glm::vec3(0,1,0));
            this->modelMatrix = glm::rotate(this->modelMatrix,rotation.x,glm::vec3(1,0,0));
        }
    }
    void scale(glm::vec3 scaling)
    {
        if (!CommonMath::IsZero(scaling))
        {
            this->scaling *= scaling;
            this->modelMatrix = glm::scale(this->modelMatrix,scaling);
        }
    }
    GeneralMatrix* GetModelMatrix()
    {
        return new GeneralMatrix(this->modelMatrix);
    }
private:
    glm::fvec3 position = glm::fvec3(0.0f);
    glm::fvec3 rotation = glm::fvec3(0.0f);
    glm::fvec4 quaternion;
    glm::fvec3 scaling = glm::fvec3(0.0f);
    glm::mat4 modelMatrix = glm::mat4(1.0f);
};


#endif //GAMEENGINE_TRANSFORM_H
