//
// Created by MisThe on 2021/12/5.
//

#ifndef GAMEENGINE_CAMERA_H
#define GAMEENGINE_CAMERA_H


#include "../../PsychoEngine/Transform.h"
#include "Shader.h"

class Camera
{
public:
    enum ProjectionType
    {
        ORTHOGONAL,PERSPECTIVE
    };
    Transform trans;
public:
    void transmitVP(Shader*shader)
    {
        if (shader->uniformMap.find("V_P_MATRIX") != shader->uniformMap.end())
        {
//            shader->setMatrix()
        }
    }
    void transmitV(Shader*shader)
    {
        if (shader->uniformMap.find("V_MATRIX") != shader->uniformMap.end())
        {

        }
    }
    void transmitP(Shader*shader)
    {
        if (shader->uniformMap.find("P_MATRIX") != shader->uniformMap.end())
        {

        }
    }
    void setProjectionType(ProjectionType type)
    {
        if (type != this->projectionType)
        {
            this->updateProjectionMatrix();
        }
    }
    void setViewLimit(float near,float far)
    {
        if (near > 0 && far > near)
        {
            this->near = near;
            this->far  = far;
            this->updateProjectionMatrix();
        }
    }
private:
    glm::mat4 view_matrix;
    glm::mat4 projection_matrix;
    glm::mat4 vp_matrix;
    ProjectionType projectionType;
    float near,far;
private:
    void updateProjectionMatrix()
    {
        switch (this->projectionType) {
            case ProjectionType::ORTHOGONAL:
                this->projection_matrix = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, this->near, this->far);
                break;
            case ProjectionType::PERSPECTIVE:
                this->projection_matrix = glm::perspective(glm::radians(45.0f), 1.0f, this->near, this->far);
                break;
        }
    }
    void updateViewMatrix()
    {

    }
};


#endif //GAMEENGINE_CAMERA_H
