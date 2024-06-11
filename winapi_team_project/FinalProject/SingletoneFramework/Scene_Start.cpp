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
#include "CCamera.h"

Scene_Start::Scene_Start() {

}

Scene_Start::~Scene_Start() {

}

void Scene_Start::Update() {
	CScene::Update();

	if (KEY_TAP(KEY::ENTER)) {
		ChangeScene(SCENE_TYPE::TOOL);
	}
	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 LookAt = CCamera::Instance()->GetRealPos(MOUSE_POS);
		CCamera::Instance()->SetLookAt(LookAt);
	}
}

void Scene_Start::Enter() {
	// Object 추가
	CObject* obj = new CPlayer;
	obj->setPos(Vec2(640.f, 384.f));
	obj->setScale(Vec2(100.f, 100.f));
	AddObject(obj, GROUP_TYPE::PLAYER);

	CCamera::Instance()->SetTarget(obj);

	CObject* OtherPlayer = obj->Clone();
	OtherPlayer->setPos(Vec2(740.f, 384.f));
	AddObject(OtherPlayer, GROUP_TYPE::PLAYER);

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

void Scene_Start::Exit() {
	DeleteAll();

	CColliderMgr::Instance()->Reset();
}