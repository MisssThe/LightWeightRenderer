//
// Created by MisThe on 2021/11/4.
//

#include "GraphEngine.h"

GraphEngine* GraphEngine::engine = nullptr;
std::queue<GLFWwindow*> GraphEngine::staticWindowQueue;