//
// Created by MisThe on 2021/12/18.
//

#ifndef GAMEENGINE_BASEENGINE_H
#define GAMEENGINE_BASEENGINE_H

enum UseType
{
    INIT,RUN,PAUSE,STOP
};
class BaseEngine
{
public:
    void use(UseType type)
    {
        switch (type) {
            case UseType::INIT:
                this->init();break;
            case UseType::RUN:
                this->run();break;
            case UseType::PAUSE:
                this->pause();break;
            case UseType::STOP:
                this->stop();break;
        }
    }
protected:
    virtual void init() = 0;
    virtual void run() = 0;
    virtual void pause() = 0;
    virtual void stop() = 0;
};


#endif //GAMEENGINE_BASEENGINE_H
