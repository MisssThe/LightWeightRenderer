//
// Created by MisThe on 2021/12/5.
//

#ifndef GAMEENGINE_SHORTCUTCONTROLLER_H
#define GAMEENGINE_SHORTCUTCONTROLLER_H


#include "InputController.h"

class ShortcutController
{
public:
    static void Update()
    {
        if (InputController::GetKey(256))
        {
            exit(0);
        }
    }
};


#endif //GAMEENGINE_SHORTCUTCONTROLLER_H
