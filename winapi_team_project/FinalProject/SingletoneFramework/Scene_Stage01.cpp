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
#include "CFindingMgr.h"
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
	wall->setPos(Vec2(310.f, 550.f));
	wall->setScale(Vec2(20.f, 1350.f));
	AddObject(wall, GROUP_TYPE::FURNITURE);

	wall = new CObstract;
	wall->SetName(L"FURNITURE");
	wall->setPos(Vec2(730.f, -95.f));
	wall->setScale(Vec2(830.f, 100.f));
	AddObject(wall, GROUP_TYPE::FURNITURE);

	wall = new CObstract;
	wall->SetName(L"FURNITURE");
	wall->setPos(Vec2(1135.f, 80.f));
	wall->setScale(Vec2(20.f, 450.f));
	AddObject(wall, GROUP_TYPE::FURNITURE);

	wall = new CObstract;
	wall->SetName(L"FURNITURE");
	wall->setPos(Vec2(1550.f, 290.f));
	wall->setScale(Vec2(850.f, 20.f));
	AddObject(wall, GROUP_TYPE::FURNITURE);

	wall = new CObstract;
	wall->SetName(L"FURNITURE");
	wall->setPos(Vec2(620.f, -30.f));
	wall->setScale(Vec2(20.f, 195.f));
	AddObject(wall, GROUP_TYPE::FURNITURE);

	wall = new CObstract;
	wall->SetName(L"FURNITURE");
	wall->setPos(Vec2(620.f, 550.f));
	wall->setScale(Vec2(20.f, 750.f));
	AddObject(wall, GROUP_TYPE::FURNITURE);

	wall = new CObstract;
	wall->SetName(L"FURNITURE");
	wall->setPos(Vec2(1395.f, 650.f));
	wall->setScale(Vec2(120.f, 330.f));
	AddObject(wall, GROUP_TYPE::FURNITURE);

	wall = new CObstract;
	wall->SetName(L"FURNITURE");
	wall->setPos(Vec2(1785.f, 440.f));
	wall->setScale(Vec2(20.f, 300.f));
	AddObject(wall, GROUP_TYPE::FURNITURE);

	wall = new CObstract;
	wall->SetName(L"FURNITURE");
	wall->setPos(Vec2(1785.f, 860.f));
	wall->setScale(Vec2(20.f, 330.f));
	AddObject(wall, GROUP_TYPE::FURNITURE);

	wall = new CObstract;
	wall->SetName(L"FURNITURE");
	wall->setPos(Vec2(1965.f, 750.f));
	wall->setScale(Vec2(20.f, 930.f));
	AddObject(wall, GROUP_TYPE::FURNITURE);

	wall = new CObstract;
	wall->SetName(L"FURNITURE");
	wall->setPos(Vec2(1445.f, 1135.f));
	wall->setScale(Vec2(20.f, 230.f));
	AddObject(wall, GROUP_TYPE::FURNITURE);

	wall = new CObstract;
	wall->SetName(L"FURNITURE");
	wall->setPos(Vec2(930.f, 1020.f));
	wall->setScale(Vec2(20.f, 410.f));
	AddObject(wall, GROUP_TYPE::FURNITURE);

	wall = new CObstract;
	wall->SetName(L"FURNITURE");
	wall->setPos(Vec2(1345.f, 920.f));
	wall->setScale(Vec2(20.f, 210.f));
	AddObject(wall, GROUP_TYPE::FURNITURE);

	wall = new CObstract;
	wall->SetName(L"FURNITURE");
	wall->setPos(Vec2(1380.f, 810.f));
	wall->setScale(Vec2(310.f, 20.f));
	AddObject(wall, GROUP_TYPE::FURNITURE);

	wall = new CObstract;
	wall->SetName(L"FURNITURE");
	wall->setPos(Vec2(1020.f, 810.f));
	wall->setScale(Vec2(200.f, 20.f));
	AddObject(wall, GROUP_TYPE::FURNITURE);

	wall = new CObstract;
	wall->SetName(L"FURNITURE");
	wall->setPos(Vec2(1710.f, 810.f));
	wall->setScale(Vec2(140.f, 20.f));
	AddObject(wall, GROUP_TYPE::FURNITURE);

	wall = new CObstract;
	wall->SetName(L"FURNITURE");
	wall->setPos(Vec2(1550.f, 1015.f));
	wall->setScale(Vec2(430.f, 20.f));
	AddObject(wall, GROUP_TYPE::FURNITURE);

	wall = new CObstract;
	wall->SetName(L"FURNITURE");
	wall->setPos(Vec2(1140.f, 1225.f));
	wall->setScale(Vec2(1680.f, 20.f));
	AddObject(wall, GROUP_TYPE::FURNITURE);

	wall = new CObstract;
	wall->SetName(L"FURNITURE");
	wall->setPos(Vec2(860.f, 500.f));
	wall->setScale(Vec2(720.f, 20.f));
	AddObject(wall, GROUP_TYPE::FURNITURE);

	wall = new CObstract;
	wall->SetName(L"FURNITURE");
	wall->setPos(Vec2(340.f, 500.f));
	wall->setScale(Vec2(100.f, 20.f));
	AddObject(wall, GROUP_TYPE::FURNITURE);

	wall = new CObstract;
	wall->SetName(L"FURNITURE");
	wall->setPos(Vec2(770.f, 915.f));
	wall->setScale(Vec2(320.f, 20.f));
	AddObject(wall, GROUP_TYPE::FURNITURE);

	CItem* Item = nullptr;
	Item = new CItem;
	Item->SetName(L"ITEM");
	Item->setPos(Vec2(1000.f, 500.f));
	Item->setScale(Vec2(25.f, 25.f));
	AddObject(Item, GROUP_TYPE::ITEM);

	CColliderMgr::Instance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CColliderMgr::Instance()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);
	CColliderMgr::Instance()->CheckGroup(GROUP_TYPE::FURNITURE, GROUP_TYPE::PROJ_PLAYER);
	CColliderMgr::Instance()->CheckGroup(GROUP_TYPE::FURNITURE, GROUP_TYPE::PROJ_MONSTER);
	CColliderMgr::Instance()->CheckGroup(GROUP_TYPE::FURNITURE, GROUP_TYPE::MONSTER);
	CColliderMgr::Instance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::ITEM);
	CFindingMgr::Instance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);

	//Camera Look 지정
	CCamera::Instance()->SetLookAt(Resolution / 2.f);
}

void Scene_Stage01::Exit() {
	DeleteAll();

	CColliderMgr::Instance()->Reset();
}