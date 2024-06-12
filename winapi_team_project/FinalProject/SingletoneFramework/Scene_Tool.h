#pragma once

#include "CScene.h"

class Scene_Enter :
    public CScene
{
public:
    Scene_Enter();
    ~Scene_Enter();

    virtual void Update();
    virtual void Enter();
    virtual void Exit();
};