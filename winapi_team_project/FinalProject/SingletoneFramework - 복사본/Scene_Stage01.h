#pragma once

#include "CScene.h"

class Scene_Stage01 :
    public CScene
{
private:

public:
    Scene_Stage01();
    ~Scene_Stage01();

    virtual void Update();
    virtual void Enter();
    virtual void Exit();
};