//
// Created by MisThe on 2021/10/29.
//

#ifndef GAMEENGINE_TIME_H
#define GAMEENGINE_TIME_H


#include <string>
#include <time.h>
#include <sys/time.h>

class Time
{
public:
    static std::string GetTimeStr();
    static long getMillisecond();
    static int CalculateFrame(int num = 1);
private:
    static long millisecond;
};


#endif
//GAMEENGINE_TIME_H
