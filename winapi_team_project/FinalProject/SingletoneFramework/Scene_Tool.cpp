#include "pch.h"
#include "CCore.h"
#include "Scene_Tool.h"

#include "CKeyMgr.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"

#include "CTexture.h"

Scene_Tool::Scene_Tool()
{
}

Scene_Tool::~Scene_Tool()
{
}

void Scene_Tool::Update() {
	CScene::Update();

	if (KEY_TAP(KEY::ENTER)) {
		ChangeScene(SCENE_TYPE::START);
	}
}

void Scene_Tool::Enter()
{
}

void Scene_Tool::Exit()
{
}
