//
// Created by MisThe on 2021/11/16.
//

#include "EventCenter.h"

std::unordered_map<std::string,std::function<void(long)>> EventCenter::eventMap;
