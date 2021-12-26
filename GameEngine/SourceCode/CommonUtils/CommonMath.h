//
// Created by MisThe on 2021/11/26.
//

#ifndef GAMEENGINE_COMMONMATH_H
#define GAMEENGINE_COMMONMATH_H


#include <glm/glm.hpp>
#include <iostream>
class GeneralMatrix
{
public:
    GeneralMatrix(glm::mat2 matrix)
    {
        this->size = sizeof(float) * 4;
        this->index = &matrix[0][0];
    }
    GeneralMatrix(glm::mat3 matrix)
    {
        this->size = sizeof(float) * 9;
        this->index = &matrix[0][0];
    }
    GeneralMatrix(glm::mat4 matrix)
    {
        this->size = sizeof(float) * 16;
        this->index = &matrix[0][0];
    }
    int getSize()
    {
        return this->size;
    }
    float* getIndex()
    {
        return this->index;
    }
private:
    int size;
    float*index;
};
class CommonMath
{
public:
    static float minDecimal;
public:
    template<class T> static T Saturate(T t,T min,T max)
    {
        t = t < max?t:max;
        t = t > min?t:min;
        return t;
    }
    static bool IsZero(glm::fvec3 data)
    {
        if (abs(data.x - 0.0f) > minDecimal || abs(data.y - 0.0f) > minDecimal || abs(data.z - 0.0f) > minDecimal)
        {
            return false;
        }
        return true;
    }
private:
    CommonMath(){}
};


#endif //GAMEENGINE_COMMONMATH_H
