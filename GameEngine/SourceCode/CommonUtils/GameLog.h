//
// Created by MisThe on 2021/10/29.
//

#ifndef GAMEENGINE_GAMELOG_H
#define GAMEENGINE_GAMELOG_H

#include <string>
#include <fstream>
#include "Utils/Time.h"
#include <iostream>

enum LogState
{
    EDITOR,GAME
};

class GameLog {
public:
    static void LogError(std::string errorFunc,std::string context,bool needFull = true);
    static void LogWarning(std::string errorFunc,std::string context);
    static void SetLogState(LogState state);
private:
    static std::string logErrorPath;
    static std::string logWarningPath;
    static LogState logState;
};


#endif
//GAMEENGINE_GAMELOG_H
