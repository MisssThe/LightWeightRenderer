//
// Created by MisThe on 2021/10/28.
//

#include "Engine.h"

Engine* Engine::engine = nullptr;
BaseEngine* Engine::baseEngine = nullptr;
bool Engine::isLock = true;