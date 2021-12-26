//
// Created by MisThe on 2021/10/28.
// 包含各种通用功能（静态方法）
//

#ifndef GAMEENGINE_COMMONUTILS_H
#define GAMEENGINE_COMMONUTILS_H


#include <vector>
#include <queue>
#include <json.h>
#include <iostream>
#include "Time.h"
#include "GameLog.h"
#include <fstream>
#include <thread>
#include <unordered_map>

class CommonUtils {
private:
    template<class T> static void unpackArgs(std::vector<T>* vec,T arg)
    {
        vec->push_back(arg);
    }
public:
//    template<class ...Args> static void SafeCall(std::function<void(Args)...> func,Args ...args)
//    {
//        if (func != nullptr)
//        {
//            func(args...);
//        }
//    }
    template<class T> static void SafeCall(std::function<void(T)> func,T n)
    {
        if (func != nullptr)
        {
            func(n);
        }
    }
    static void SafeCall(std::function<void()> func)
    {
        if (func != nullptr) {
            func();
        }
    }
    template<class T> static T SafeCall(std::function<T()> func)
    {
        return func();
    }


    template<class T,class Q> static void SafeCall(std::function<void(T,Q)> func,T t,Q q)
    {
        func(t,q);
    }

    template<class T> static void TraverQueue(std::queue<T>* queue,std::function<void(T)> func)
    {
        int length = queue->size();
        if (length > 0)
        {
            T element;
            for (int i = 0; i < length; ++i) {
                element = queue->front();
                func(element);
                queue->pop();
                queue->push(element);
            }
        }
    }
    //避免隐式转换，func会改变queue的结构
    template<class T> static void TraverQueueBool(std::queue<T>* queue,std::function<bool(T)> func)
    {
        if (queue != nullptr) {
            int length = queue->size();
            if (length > 0) {
                T element;
                for (int i = 0; i < length; ++i) {
                    element = queue->front();
                    if (func(element)) {
                        queue->push(element);
                    }
                    queue->pop();
                }
            }
        }
    }
    template<class T>  static void TraverQueue(std::queue<T> queue,std::function<void(T)> func)
    {
        TraverQueue(&queue,func);
    }
    template<class T> static void TraverVector(std::vector<T>*vec,std::function<void(T)> func)
    {
        if (vec != nullptr) {
            int length = vec->size();
            for (int i = 0; i < length; ++i) {
                SafeCall<T>(func, vec->at(i));
            }
        }
    }

    template<class T> static void TraverVector(std::vector<T> vec,std::function<void(T)> func)
    {
        TraverVector(&vec,func);
    }

//    template<class T,class Q,class W> static void TraverVector(std::vector<T> vec,std::function<void(T,Q,W)> func)
//    {
//
//    }

    template<class T,class Q> static void TraverMap(std::unordered_map<T,Q> map,std::function<void(T,Q)> func)
    {
        for (auto item:map)
        {
            SafeCall(func,item.first,item.second);
        }
    }
    static Json::Value ReadJson(std::string filePath)
    {
        std::ifstream jsonFile;
        jsonFile.open(filePath);
        Json::Value root;
        Json::CharReaderBuilder reader;
        JSONCPP_STRING errs;
        Json::parseFromStream(reader, jsonFile, &root, &errs);
        jsonFile.close();
        GameLog::LogError("ReadJson",errs, false);
        return root;
    }
    static void WriteJson(std::string filePath,std::string key,std::string content)
    {
//        std::ofstream jsonFile(filePath,std::ios::out);
//        if(!jsonFile.is_open())
//        {
//        }
//        else {
//            Json::StyledWriter sw;
//            jsonFile << sw.write(writeJson);
//            jsonFile.close();
//        }
    }
    static void WriteJson()
    {

    }
    static void DeleteChar(std::string*str,std::string flag)
    {
        str->erase(std::remove(str->begin(), str->end(), '\u0000'), str->end());
    }
    static std::vector<std::string>* Split(std::string str,std::string flag)
    {
        std::vector<std::string>* result = new std::vector<std::string>;
        if(str.empty())
        {
            return result;
        }
        int pos = 0;
        int flagLen = flag.length();
        str = str + flag;
        std::string temp;
        do
        {
            pos = str.find(flag);
            temp = str.substr(0,pos);
            if (!temp.empty())
            {
                result->push_back(temp);
            }
            str = str.substr(pos + flagLen,str.size());
        } while (!str.empty());
        return result;
    }
    template<class T> static int ArrayLength(T array)
    {
        int allSize = sizeof(array);
        int oneSize = sizeof(array[0]);
        if (oneSize != 0)
        {
            return allSize/oneSize;
        }
        return 0;
    }
    static int StartThread(std::function<void()> func,bool endless = false)
    {
        //该线程是否需要循环运行
        std::thread* thread;
        int threadId = ++CommonUtils::base_thread_id;
        if (endless)
        {
            thread = new std::thread(
                    [](std::function<void()> func,int threadId)
                    {
                        while (true)
                        {
                            SafeCall(func);
                            if (CommonUtils::thread_map.at(threadId)->endFlag)
                            {
                                return;
                            }
                        }
                    },func,threadId
            );
        }
        else
        {
            thread = new std::thread(
                    [](std::function<void()> func)
                    {
                        SafeCall(func);
                    },func
            );
        }
        Thread* value = new Thread(thread);
        thread_map.insert(std::pair<int,Thread*>(threadId,value));
        return threadId;
    }
    static void StopThread(int threadId)
    {
        thread_map.at(threadId)->endFlag = true;
        thread_map.at(threadId)->thread->join();
        thread_map.erase(threadId);
    }
    static std::string* ReadFile(std::string path,unsigned int ioState = std::ifstream::failbit | std::ifstream::badbit)
    {
        std::string* code;
        std::ifstream file;
        file.exceptions(ioState);
        try
        {
            file.open(path);
            std::stringstream stream;
            stream << file.rdbuf();
            file.close();
            code = new std::string(stream.str());
        }
        catch (std::ifstream::failure& e)
        {
            GameLog::LogError("ReadFile","file read failed:" + path);
        }
        return code;
    }
    template<class T,class ...Args> static std::vector<T> UnpackArgs(Args ... args)
    {
        std::vector<T> vec;
        int arg[] = {(unpackArgs(&vec,args),0)...};
        return vec;
    }
private:
    struct Thread
    {
    public:
        Thread(std::thread* thread,bool flag = false)
        {
            this->thread = thread;
            this->endFlag = flag;
        }
        ~Thread()
        {
            delete this->thread;
        }
        std::thread* thread;
        bool         endFlag;
    };
    static std::unordered_map<int,Thread*> thread_map;
    static int base_thread_id;
};
//----------------------------- CommonStructures ----------------------------------
struct Color
{
public:
    explicit Color(float r = 0,float g = 0,float b = 0,float a = 0):r(r),g(g),b(b),a(a){}
    Color(std::string color)
    {
        std::vector<std::string>* vec = CommonUtils::Split(color,",");
        float colorNum[4] = {0};
        int len1,len2;
        len1 = vec->size();
        len2 = CommonUtils::ArrayLength(colorNum);
        for (int i = 0; i < len1 && i < len2; ++i)
        {
            colorNum[i] = std::stof(vec->at(i));
        }
        this->r = colorNum[0];
        this->g = colorNum[1];
        this->b = colorNum[2];
        this->a = colorNum[3];
        delete vec;
    }
    float r,g,b,a;
};
struct Float2
{
public:
    Float2():x(0),y(0){};
    Float2(float x,float y):x(x),y(y){};
    float x,y;
};
//----------------------------- CommonStructures ----------------------------------

#endif

//GAMEENGINE_COMMONUTILS_H
