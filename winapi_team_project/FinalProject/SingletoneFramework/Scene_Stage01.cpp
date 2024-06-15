#include "pch.h"
#include "CCore.h"
#include "Scene_Stage01.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CObstract.h"
#include "CItem.h"
#include "CScore.h"
#include "Cstage_01.h"

#include "CColliderMgr.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"
#include "CTexture.h"
#include "CSceneMgr.h"
#include "CCamera.h"
#include "CResMgr.h"

Scene_Stage01::Scene_Stage01() {

}

Scene_Stage01::~Scene_Stage01() {

}

void Scene_Stage01::Update() {
	CScene::Update();
}

void Scene_Stage01::Enter() {
	// Object 추가

	Cstage_01* map = new Cstage_01;
	map->SetName(L"Stage_01");
	AddObject(map, GROUP_TYPE::MAP);
	

	CObject* obj = new CPlayer;

	float ResloutionX = GetSystemMetrics(SM_CXSCREEN);
	float ResloutionY = GetSystemMetrics(SM_CYSCREEN);

	obj->setPos(Vec2(ResloutionX / 2, ResloutionY / 2));
	obj->setScale(Vec2(45.f, 30.f));
	obj->SetName(L"PLAYER");
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

	CObstract* wall = nullptr;
	wall = new CObstract;
	wall->SetName(L"FURNITURE");
	wall->setPos(Vec2(500.f, 500.f));
	wall->setScale(Vec2(25.f, 100.f));
	AddObject(wall, GROUP_TYPE::FURNITURE);

	CItem* Item = nullptr;
	Item = new CItem;
	Item->SetName(L"ITEM");
	Item->setPos(Vec2(1000.f, 500.f));
	Item->setScale(Vec2(25.f, 25.f));
	AddObject(Item, GROUP_TYPE::ITEM);

	CScore* Score = nullptr;
	Score = new CScore;
	Score->SetName(L"SCORE");
	Score->setPos(Vec2(1200.f, 0.f));
	Score->setScale(Vec2(25.f, 25.f));
	AddObject(Score, GROUP_TYPE::SCORE);

	CColliderMgr::Instance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CColliderMgr::Instance()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);
	CColliderMgr::Instance()->CheckGroup(GROUP_TYPE::FURNITURE, GROUP_TYPE::PLAYER);
	CColliderMgr::Instance()->CheckGroup(GROUP_TYPE::FURNITURE, GROUP_TYPE::MONSTER);
	CColliderMgr::Instance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::ITEM);

	//Camera Look 지정
	CCamera::Instance()->SetLookAt(Resolution / 2.f);
}

void Scene_Stage01::Exit() {
	DeleteAll();

	CColliderMgr::Instance()->Reset();
}