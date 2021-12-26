//
// Created by 谭地杰 on 2021/10/29.
//

#include "GameLog.h"

//----------------------------------   static element   ----------------------------------
std::string GameLog::logErrorPath = "/Users/tandijie/MisThe/GameEngine/SourceCode/SystemDocuments/error_log.txt";
std::string GameLog::logWarningPath = "/Users/tandijie/MisThe/GameEngine/SourceCode/SystemDocuments/warning_log.txt";
LogState GameLog::logState = LogState::EDITOR;
//----------------------------------   static element   ----------------------------------

void GameLog::LogError(std::string errorFunc,std::string context,bool needFull)
{
    if (context.empty())
    {
        if (!needFull)
            return;
        context = "存入一次无内容错误";
    }
    std::string nowTime = Time::GetTimeStr();
    if (logState == LogState::GAME)
    {
        std::ofstream logFile(logErrorPath, std::ios::app);
        logFile.setf(std::ios::left);
        logFile << std::setw(40) << "ERROR_TIME:" + nowTime << "ERROR_FUNCTION:" + errorFunc << std::endl << "      ERROR_CONTEXT:" +  context << std::endl;
        logFile.close();
        exit(0);
    }
    else if (logState == LogState::EDITOR)
    {
        std::cout.setf(std::ios::left);
        std::cout << std::setw(40) << "ERROR_TIME:" + nowTime << "ERROR_FUNCTION:" + errorFunc << std::endl << "      ERROR_CONTEXT:" +  context << std::endl;
    }
}

void GameLog::LogWarning(std::string context, std::string warningFunc)
{

}

void GameLog::SetLogState(LogState state)
{
    logState = state;
}

