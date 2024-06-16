#pragma once

#include "CScene.h"

class Scene_Start :
    public CScene
{
private:

public:
    Scene_Start();
    ~Scene_Start();

    virtual void Update();
    virtual void Enter();
    virtual void Exit();
};