//
// Created by MisThe on 2021/11/1.
//

#ifndef GAMEENGINE_SHADER_H
#define GAMEENGINE_SHADER_H

#include <string>
#include <glad.h>
#include <glfw3.h>
#include "../../../CommonUtils/CommonUtils.h"
#include "../../../CommonUtils/CommonMath.h"

const std::string UNIFORM_BEGIN = "//------------ UNIFORM START ------------";
const std::string UNIFORM_END   = "//------------ UNIFORM   END ------------";
const int UNIFORM_LENGTH        = UNIFORM_BEGIN.length() + 1;

class Shader
{
public:
    std::unordered_map<std::string ,int> uniformMap;
private:
    int shaderID;
    int textureNum;
    std::string name;
public:
    //不建议使用
    Shader(std::string name,int ID)
    {
        this->shaderID = ID;
        this->name = name;
    }
    Shader(std::string shaderName,std::string shaderPath)
    {
        this->name = shaderName;
    }
    Shader(std::string shaderName,std::string vertexShaderPath,std::string fragmentShaderPath)
    {
        this->name = shaderName;
        std::string*vCode = CommonUtils::ReadFile(vertexShaderPath);
        std::string*fCode = CommonUtils::ReadFile(fragmentShaderPath);
        std::unordered_map<std::string,int> codeMap;
        codeMap.insert(std::pair<std::string,int>(*vCode,GL_VERTEX_SHADER));
        codeMap.insert(std::pair<std::string,int>(*fCode,GL_FRAGMENT_SHADER));
        this->shaderID = glCreateProgram();
        this->attachShader(codeMap);
        this->scanProperty(*vCode);
        this->scanProperty(*fCode);
    }
    Shader(std::string shaderName,std::string vertexShaderPath,std::string fragmentShaderPath,std::string geometryShaderPath)
    {
        this->name = shaderName;
    }
    Shader(std::string shaderName,std::string vertexShaderPath,std::string fragmentShaderPath,std::string tessellationShaderPath,std::string geometryShaderPath)
    {
        this->name = shaderName;
    }
    ~Shader()
    {
        this->uniformMap.clear();
    }
    void Use()
    {
        glUseProgram(this->shaderID);
    }
    template<class ...Args> void setFloat(std::string name,Args ...args)
    {
        std::vector<float> vec = CommonUtils::UnpackArgs<float>(args...);
        int length = vec.size();
        int location = this->uniformMap.at(name);
        switch (length)
        {
            case 1:
                glUniform1f(location,vec[0]);
                break;
            case 2:
                glUniform2f(location,vec[0],vec[1]);
                break;
            case 3:
                glUniform3f(location,vec[0],vec[1],vec[2]);
                break;
            case 4:
                glUniform4f(location,vec[0],vec[1],vec[2],vec[3]);
                break;
        }
    }
    void setTexture(std::string name,int tex)
    {
        int location = this->uniformMap.at(name);
        glUniform1i(location,tex);
        this->textureNum++;
    }
    void setMatrix(std::string name,GeneralMatrix *matrix)
    {
        if (this->uniformMap.find(name) != this->uniformMap.end())
        {
            int size = matrix->getSize();
            switch (size) {
                case 2:
                    glUniformMatrix2fv(this->uniformMap.at(name),size,false,matrix->getIndex());
                    break;
                case 3:
                    glUniformMatrix3fv(this->uniformMap.at(name),size,false,matrix->getIndex());
                    break;
                case 4:
                    glUniformMatrix4fv(this->uniformMap.at(name),size,false,matrix->getIndex());
                    break;
            }
        }
    }
    std::string getName()
    {
        return this->name;
    }
private:
    void checkCompile(unsigned int shader, bool isProgram = false)
    {
        int success;
        char infoLog[1024];
        if (!isProgram)
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                GameLog::LogError("ShaderCompile", std::string(infoLog));
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                GameLog::LogError("ProgramCompile", std::string(infoLog));
            }
        }
    }
    void attachShader(std::unordered_map<std::string,int> codeMap)
    {
        if (this->shaderID < 0 || codeMap.empty())
        {
            GameLog::LogError("CompileShader","shader create failed");
            return;
        }
        CommonUtils::TraverMap<std::string,int>(codeMap,
           [this](std::string codeStr,int shaderType)
           {
               unsigned int shader;
               shader = glCreateShader(shaderType);
               const char* codeChar = codeStr.c_str();
               glShaderSource(shader, 1, &codeChar, NULL);
               glCompileShader(shader);
               checkCompile(shader, false);
               glAttachShader(shaderID,shader);
               glDeleteShader(shader);
           }
        );
        glLinkProgram(this->shaderID);
        checkCompile(this->shaderID, true);
    }
    void scanProperty(std::string code)
    {
        this->textureNum = 0;
        int firstPos = code.find(UNIFORM_BEGIN);
        int lastPos = code.rfind(UNIFORM_END);
        std::string uniformStr = code.substr(firstPos + UNIFORM_LENGTH, lastPos - firstPos - UNIFORM_LENGTH);
        std::vector<std::string>* vec = CommonUtils::Split(uniformStr,";\n");
        CommonUtils::TraverVector<std::string>(vec,
           [this](std::string str)
           {
                std::vector<std::string>*vec = CommonUtils::Split(str," ");
                this->uniformMap.insert(std::pair<std::string,int>(vec->at(1),glGetUniformLocation(this->shaderID,vec->at(1).c_str())));
           }
        );
        delete vec;
    }
};


#endif
//GAMEENGINE_SHADER_H
