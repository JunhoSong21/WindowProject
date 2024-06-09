#include "pch.h"
#include "CCore.h"
#include "Scene_Start.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"

#include "CColliderMgr.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"
#include "CTexture.h"
#include "CSceneMgr.h"

Scene_Start::Scene_Start() {

}

Scene_Start::~Scene_Start() {

}

void Scene_Start::Update() {
	CScene::Update();

	if (KEY_TAP(KEY::ENTER)) {
		ChangeScene(SCENE_TYPE::TOOL);
	}
}

void Scene_Start::Enter() {
	// Object Ãß°¡
	CObject* obj = new CPlayer;
	obj->setPos(Vec2(640.f, 384.f));
	obj->setScale(Vec2(100.f, 100.f));
	AddObject(obj, GROUP_TYPE::PLAYER);

	CObject* OtherPlayer = obj->Clone();
	OtherPlayer->setPos(Vec2(740.f, 384.f));
	AddObject(OtherPlayer, GROUP_TYPE::PLAYER);

	int monCount = 2;
	float moveDist = 25.f;
	float objScale = 50.f;
	Vec2 resolutions = CCore::Instance()->GetResolution();
	float term = (resolutions.x - ((moveDist + objScale / 2.f) * 2)) / (float)(monCount - 1);

	CMonster* MonsterObj = nullptr;
	for (int i = 0; i < monCount; ++i) {
		MonsterObj = new CMonster;
		MonsterObj->SetName(L"Monster");
		MonsterObj->SetCenterPos(Vec2((moveDist + objScale / 2.f) + (float)i * term, 50.f));
		MonsterObj->setPos(Vec2(MonsterObj->GetCenterPos()));
		MonsterObj->SetMoveDist(moveDist);
		MonsterObj->setScale(Vec2(objScale, objScale));
		AddObject(MonsterObj, GROUP_TYPE::MONSTER);
	}

	CColliderMgr::Instance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CColliderMgr::Instance()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);
}

void Scene_Start::Exit() {
	DeleteAll();

	CColliderMgr::Instance()->Reset();
}