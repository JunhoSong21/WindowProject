#pragma once

#include "CScene.h"

class Scene_Tool :
	public CScene
{
private:

public:
	Scene_Tool();
	~Scene_Tool();

	virtual void Update();
	virtual void Enter();
	virtual void Exit();
};

