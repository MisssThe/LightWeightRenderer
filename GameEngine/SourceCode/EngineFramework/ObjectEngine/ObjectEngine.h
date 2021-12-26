//
// Created by MisThe on 2021/12/26.
//

#ifndef GAMEENGINE_OBJECTENGINE_H
#define GAMEENGINE_OBJECTENGINE_H


#include "../../CommonUtils/CommonUtils.h"
#include "../../Components/GameObject.h"

class ObjectEngine
{
public:
    static void Init()
    {
        check();
    }
    static void Run()
    {
        check();
        engine->run();
    }
    static void Pause()
    {
        check();

    }
    static void Stop()
    {
        check();
    }
    static void Add(GameObject* object)
    {
        check();
        //添加游戏物体
        engine->add(object);
    }
private:
    std::queue<GameObject*> beginQueue;
    std::queue<GameObject*> updateQueue;
    std::queue<GameObject*> endQueue;
    bool isRun = false;
    static ObjectEngine* engine;
private:
    static void check()
    {
        if (!engine)
            engine = new ObjectEngine();
    }
    ObjectEngine()
    {
        //--------------------
    }
    void run()
    {
        if (isRun)
            return;
        CommonUtils::StartThread([this](){
            CommonUtils::TraverQueueBool<GameObject*>(&(this->beginQueue),[](GameObject* obj)->bool {
                obj->Begin();
                return false;
            });
            CommonUtils::TraverQueueBool<GameObject*>(&(this->updateQueue),[](GameObject* obj)->bool {
                return obj->Update();
            });
            CommonUtils::TraverQueueBool<GameObject*>(&(this->endQueue),[](GameObject* obj)->bool {
                obj->End();
                return false;
            });
        }, true);
    }
    void add(GameObject*object)
    {
        if (object)
            this->beginQueue.push(object);
    }
};


#endif //GAMEENGINE_OBJECTENGINE_H
