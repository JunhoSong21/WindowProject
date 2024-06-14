#include "pch.h"
#include "CCore.h"
#include "Scene_Stage01.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"

#include "CColliderMgr.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"
#include "CTexture.h"
#include "CSceneMgr.h"
#include "CCamera.h"

Scene_Stage01::Scene_Stage01() {

}

Scene_Stage01::~Scene_Stage01() {

}

void Scene_Stage01::Update() {
	CScene::Update();
}

void Scene_Stage01::Enter() {
	// Object 추가
	CObject* obj = new CPlayer;

	float ResloutionX = GetSystemMetrics(SM_CXSCREEN);
	float ResloutionY = GetSystemMetrics(SM_CYSCREEN);

	obj->setPos(Vec2(ResloutionX / 2, ResloutionY / 2));
	obj->setScale(Vec2(45.f, 30.f));
	AddObject(obj, GROUP_TYPE::PLAYER);

	CCamera::Instance()->SetTarget(obj);

	int monCount = 10;
	float moveDist = 25.f;
	float objScale = 50.f;
	Vec2 Resolution = CCore::Instance()->GetResolution();
	float term = (Resolution.x - ((moveDist + objScale / 2.f) * 2)) / (float)(monCount - 1);

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

	//Camera Look 지정
	CCamera::Instance()->SetLookAt(Resolution / 2.f);
}

void Scene_Stage01::Exit() {
	DeleteAll();

	CColliderMgr::Instance()->Reset();
}