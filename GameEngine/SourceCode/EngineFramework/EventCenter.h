//
// Created by MisThe on 2021/11/16.
// 负责所有的事件转发用于解耦
//

#ifndef GAMEENGINE_EVENTCENTER_H
#define GAMEENGINE_EVENTCENTER_H

#include "../CommonUtils/CommonUtils.h"

class EventCenter
{
public:
    static void AddEvent(std::string name,std::function<void(long )> func)
    {
        eventMap.insert(std::pair<std::string,std::function<void(long)>>(name,func));
    }
    static void UseEvent(std::string name,long index)
    {
        CommonUtils::SafeCall(eventMap.at(name),index);
    }
private:
    static std::unordered_map<std::string,std::function<void(long)>> eventMap;
};


#endif //GAMEENGINE_EVENTCENTER_H
