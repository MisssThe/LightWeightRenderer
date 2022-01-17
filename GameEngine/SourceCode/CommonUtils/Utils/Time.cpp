//
// Created by 谭地杰 on 2021/10/29.
//

#include "Time.h"

long Time::millisecond = 0;

std::string Time::GetTimeStr()
{
    time_t curTime;
    time(&curTime);
    struct tm *nowTime;
    nowTime = localtime(&curTime);
    std::string timeStr = std::to_string(nowTime->tm_year + 1900) + std::string("_" + std::to_string(nowTime->tm_mon + 1)) + std::string("_" + std::to_string(nowTime->tm_mday)) + std::string("   " + std::to_string(nowTime->tm_hour)) + std::string(":" + std::to_string(nowTime->tm_min)) + std::string(":" + std::to_string(nowTime->tm_sec));
    return timeStr;
}

long Time::getMillisecond()
{
    struct timeval curTime;
    gettimeofday(&curTime, nullptr);
    return curTime.tv_sec * 1000 + curTime.tv_usec * 0.001;
}

int Time::CalculateFrame(int num)
{
    int nowMillisecond = getMillisecond();
    int dis = (nowMillisecond - millisecond) * num;
    if (dis == 0)
    {
        return 0;
    }
    int frame = 1000 / dis;
    millisecond = nowMillisecond;
    return frame;
}
