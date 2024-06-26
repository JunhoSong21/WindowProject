#include "pch.h"
#include "CCore.h"
#include "Scene_Stage010.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CObstract.h"
#include "CItem.h"
#include "CScore.h"
#include "CStage_010.h"

#include "CColliderMgr.h"
#include "CFindingMgr.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"
#include "CTexture.h"
#include "CSceneMgr.h"
#include "CCamera.h"
#include "CResMgr.h"
#include "CSound.h"
#include "CCollider.h"

Scene_Stage010::Scene_Stage010()
{
}

Scene_Stage010::~Scene_Stage010()
{
}

void Scene_Stage010::Update() {
	CScene::Update();

	if (KEY_TAP(KEY::ENTER)) {
		// 0.5초 반 검은색 화면 0.5초 완전 검은색 화면
		ChangeScene(SCENE_TYPE::STAGE_01);
	}

	Vec2 ptPos = getPos();
}

void Scene_Stage010::Enter() {
	// Object 추가
	CScene::ChangePoint(1);
	float ResloutionX = GetSystemMetrics(SM_CXSCREEN);
	float ResloutionY = GetSystemMetrics(SM_CYSCREEN);
	CStage_010* map = new CStage_010;
	map->SetName(L"Stage_010");
	map->setPos(Vec2(ResloutionX, ResloutionY));
	AddObject(map, GROUP_TYPE::MAP);

	CObject* obj = new CPlayer;

	CCamera::Instance()->SetCamera(Vec2(310.f, -320.f));

	Vec2 Resolution = CCore::Instance()->GetResolution();

	obj->setPos(Vec2(310.f, -320.f));
	obj->setScale(Vec2(45.f, 30.f));
	obj->SetName(L"PLAYER");
	AddObject(obj, GROUP_TYPE::PLAYER);

	CCamera::Instance()->SetTarget(obj);

	CObstract* wall = nullptr;
	ResloutionX = 0;
	ResloutionY = 0;

	wall = new CObstract;
	wall->SetName(L"FURNITURE");
	wall->setPos(Vec2(ResloutionX / 2 + -30.f, ResloutionY / 2 + 500.f));
	wall->setScale(Vec2(16.f, 1900.f));
	AddObject(wall, GROUP_TYPE::FURNITURE); // 제일 왼쪽 긴 벽

	CMonster* MonsterObj = nullptr;
	MonsterObj = new CMonster;
	MonsterObj->SetName(L"Monster");
	MonsterObj->SetCenterPos(Vec2(2180.f, 1300.f));
	MonsterObj->setPos(Vec2(MonsterObj->GetCenterPos()));
	MonsterObj->SetMoveDist(0);
	MonsterObj->setScale(Vec2(100.f, 250.f));
	MonsterObj->SetHP(0);
	AddObject(MonsterObj, GROUP_TYPE::MONSTER);

	CColliderMgr::Instance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CColliderMgr::Instance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::FURNITURE);
	CColliderMgr::Instance()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);
	CColliderMgr::Instance()->CheckGroup(GROUP_TYPE::FURNITURE, GROUP_TYPE::PROJ_PLAYER);
	CColliderMgr::Instance()->CheckGroup(GROUP_TYPE::FURNITURE, GROUP_TYPE::PROJ_MONSTER);
	CColliderMgr::Instance()->CheckGroup(GROUP_TYPE::FURNITURE, GROUP_TYPE::MONSTER);
	CColliderMgr::Instance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::ITEM);

	//Camera Look 지정
	CCamera::Instance()->SetLookAt(Resolution / 2.f);
}

void Scene_Stage010::Exit() {
	DeleteAll();

	CColliderMgr::Instance()->Reset();
}