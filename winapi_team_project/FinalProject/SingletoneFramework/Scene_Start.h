#pragma once

#include "CScene.h"
class Scene_Start :
    public CScene {
public:
    Scene_Start();
    ~Scene_Start();

    virtual void Enter();
    virtual void Exit();
};