
#ifndef GAMEENGINE_COMPONENT_H
#define GAMEENGINE_COMPONENT_H

class Component
{
public:
    Component(int index = -1)
    {
        if (index > 0)
            this->index = index;
        else
            GameLog::LogError("CreateComponent","error component index");
    }
    int getIndex()
    {
        if (this->index < 0)
            GameLog::LogError("GetComponentIndex","error component index");
        return this->index;
    }
    virtual void Use() = 0;
    virtual ~Component()
    {

    }
private:
    int index = -1;
};

#endif //GAMEENGINE_COMPONENT_H
