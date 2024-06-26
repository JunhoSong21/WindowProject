#include "pch.h"
#include "CCore.h"
#include "Scene_Stage01.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CObstract.h"
#include "CItem.h"
#include "CScore.h"
#include "CStage_01.h"

#include "CColliderMgr.h"
#include "CFindingMgr.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"
#include "CTexture.h"
#include "CSceneMgr.h"
#include "CCamera.h"
#include "CResMgr.h"
#include "CSound.h"

Scene_Stage01::Scene_Stage01() 
{
}

Scene_Stage01::~Scene_Stage01() 
{
}

void Scene_Stage01::Update() {
	CScene::Update();

	if (KEY_TAP(KEY::R)) {
		ChangeScene(SCENE_TYPE::STAGE_01);
	}
}

void Scene_Stage01::Enter() {
	
	// Object �߰�
	CScene::ChangePoint(1);
	float ResloutionX = GetSystemMetrics(SM_CXSCREEN);
	float ResloutionY = GetSystemMetrics(SM_CYSCREEN);
	Cstage_01* map = new Cstage_01;
	map->SetName(L"Stage_01");
	map->setPos(Vec2(ResloutionX, ResloutionY));
	AddObject(map, GROUP_TYPE::MAP);
	
	CObject* obj = new CPlayer;

	CCamera::Instance()->SetCamera(Vec2(1760.f, 1120.f));

	obj->setPos(Vec2(1760.f, 1120.f));
	obj->setScale(Vec2(45.f, 30.f));
	obj->SetName(L"PLAYER");
	AddObject(obj, GROUP_TYPE::PLAYER);

	CCamera::Instance()->SetTarget(obj);

	int monCount = 3;
	float moveDist = 50.f;
	float objScale = 50.f;
	Vec2 Resolution = CCore::Instance()->GetResolution();
	float term = (500 - ((moveDist + objScale / 2.f) * 2)) / (float)(monCount - 1);

	CMonster* MonsterObj = nullptr;
	MonsterObj = new CMonster;
	MonsterObj->SetName(L"Monster");
	MonsterObj->SetCenterPos(Vec2(450.f, 700.f));
	MonsterObj->setPos(Vec2(MonsterObj->GetCenterPos()));
	MonsterObj->SetMoveDist(0);
	MonsterObj->setScale(Vec2(objScale, objScale));
	MonsterObj->SetHP(5);
	AddObject(MonsterObj, GROUP_TYPE::MONSTER);

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
	ResloutionX = 0;
	ResloutionY = 0;

	wall = new CObstract;
	wall->SetName(L"FURNITURE");
	wall->setPos(Vec2(ResloutionX / 2 + 310.f, ResloutionY / 2 + 550.f));
	wall->setScale(Vec2(16.f, 1350.f));
	AddObject(wall, GROUP_TYPE::FURNITURE);

	wall = new CObstract;
	wall->SetName(L"FURNITURE");
	wall->setPos(Vec2(ResloutionX / 2 + 730.f, ResloutionY / 2 - 85.f));
	wall->setScale(Vec2(830.f, 100.f));
	AddObject(wall, GROUP_TYPE::FURNITURE);

	wall = new CObstract;
	wall->SetName(L"FURNITURE");
	wall->setPos(Vec2(ResloutionX / 2 + 1135.f, ResloutionY / 2 + 80.f));
	wall->setScale(Vec2(20.f, 450.f));
	AddObject(wall, GROUP_TYPE::FURNITURE);

	wall = new CObstract;
	wall->SetName(L"FURNITURE");
	wall->setPos(Vec2(ResloutionX / 2 + 1550.f, ResloutionY / 2 + 290.f));
	wall->setScale(Vec2(850.f, 20.f));
	AddObject(wall, GROUP_TYPE::FURNITURE);

	wall = new CObstract;
	wall->SetName(L"FURNITURE");
	wall->setPos(Vec2(ResloutionX / 2 + 620.f, ResloutionY / 2 + -30.f));
	wall->setScale(Vec2(20.f, 195.f));
	AddObject(wall, GROUP_TYPE::FURNITURE);

	wall = new CObstract;
	wall->SetName(L"FURNITURE");
	wall->setPos(Vec2(ResloutionX / 2 + 620.f, ResloutionY / 2 + 550.f));
	wall->setScale(Vec2(20.f, 750.f));
	AddObject(wall, GROUP_TYPE::FURNITURE);

	wall = new CObstract;
	wall->SetName(L"FURNITURE");
	wall->setPos(Vec2(ResloutionX / 2 + 1395.f, ResloutionY / 2 + 650.f));
	wall->setScale(Vec2(120.f, 330.f));
	AddObject(wall, GROUP_TYPE::FURNITURE);

	wall = new CObstract;
	wall->SetName(L"FURNITURE");
	wall->setPos(Vec2(ResloutionX / 2 + 1785.f, ResloutionY / 2 + 440.f));
	wall->setScale(Vec2(20.f, 300.f));
	AddObject(wall, GROUP_TYPE::FURNITURE);

	wall = new CObstract;
	wall->SetName(L"FURNITURE");
	wall->setPos(Vec2(ResloutionX / 2 + 1785.f, ResloutionY / 2 + 860.f));
	wall->setScale(Vec2(20.f, 330.f));
	AddObject(wall, GROUP_TYPE::FURNITURE);

	wall = new CObstract;
	wall->SetName(L"FURNITURE");
	wall->setPos(Vec2(ResloutionX / 2 + 1965.f, ResloutionY / 2 + 750.f));
	wall->setScale(Vec2(20.f, 930.f));
	AddObject(wall, GROUP_TYPE::FURNITURE);

	wall = new CObstract;
	wall->SetName(L"FURNITURE");
	wall->setPos(Vec2(ResloutionX / 2 + 1445.f, ResloutionY / 2 + 1135.f));
	wall->setScale(Vec2(20.f, 230.f));
	AddObject(wall, GROUP_TYPE::FURNITURE);

	wall = new CObstract;
	wall->SetName(L"FURNITURE");
	wall->setPos(Vec2(ResloutionX / 2 + 930.f, ResloutionY / 2 + 1020.f));
	wall->setScale(Vec2(20.f, 410.f));
	AddObject(wall, GROUP_TYPE::FURNITURE);

	wall = new CObstract;
	wall->SetName(L"FURNITURE");
	wall->setPos(Vec2(ResloutionX / 2 + 1345.f, ResloutionY / 2 + 920.f));
	wall->setScale(Vec2(20.f, 210.f));
	AddObject(wall, GROUP_TYPE::FURNITURE);

	wall = new CObstract;
	wall->SetName(L"FURNITURE");
	wall->setPos(Vec2(ResloutionX / 2 + 1380.f, ResloutionY / 2 + 810.f));
	wall->setScale(Vec2(310.f, 20.f));
	AddObject(wall, GROUP_TYPE::FURNITURE);

	wall = new CObstract;
	wall->SetName(L"FURNITURE");
	wall->setPos(Vec2(ResloutionX / 2 + 1020.f, ResloutionY / 2 + 810.f));
	wall->setScale(Vec2(200.f, 20.f));
	AddObject(wall, GROUP_TYPE::FURNITURE);

	wall = new CObstract;
	wall->SetName(L"FURNITURE");
	wall->setPos(Vec2(ResloutionX / 2 + 1710.f, ResloutionY / 2 + 810.f));
	wall->setScale(Vec2(140.f, 20.f));
	AddObject(wall, GROUP_TYPE::FURNITURE);

	wall = new CObstract;
	wall->SetName(L"FURNITURE");
	wall->setPos(Vec2(ResloutionX / 2 + 1550.f, ResloutionY / 2 + 1015.f));
	wall->setScale(Vec2(430.f, 20.f));
	AddObject(wall, GROUP_TYPE::FURNITURE);

	wall = new CObstract;
	wall->SetName(L"FURNITURE");
	wall->setPos(Vec2(ResloutionX / 2 + 1140.f, ResloutionY / 2 + 1225.f));
	wall->setScale(Vec2(1680.f, 20.f));
	AddObject(wall, GROUP_TYPE::FURNITURE);

	wall = new CObstract;
	wall->SetName(L"FURNITURE");
	wall->setPos(Vec2(ResloutionX / 2 + 860.f, ResloutionY / 2 + 500.f));
	wall->setScale(Vec2(720.f, 20.f));
	AddObject(wall, GROUP_TYPE::FURNITURE);

	wall = new CObstract;
	wall->SetName(L"FURNITURE");
	wall->setPos(Vec2(ResloutionX / 2 + 340.f, ResloutionY / 2 + 500.f));
	wall->setScale(Vec2(100.f, 20.f));
	AddObject(wall, GROUP_TYPE::FURNITURE);

	wall = new CObstract;
	wall->SetName(L"FURNITURE");
	wall->setPos(Vec2(ResloutionX / 2 + 770.f, ResloutionY / 2 + 915.f));
	wall->setScale(Vec2(320.f, 20.f));
	AddObject(wall, GROUP_TYPE::FURNITURE);

	wall = new CObstract;
	wall->SetName(L"FURNITURE");
	wall->setPos(Vec2(ResloutionX / 2 + 770.f, ResloutionY / 2 + 915.f));
	wall->setScale(Vec2(100.f, 100.f));
	AddObject(wall, GROUP_TYPE::FURNITURE);

	CItem* Item = nullptr;
	Item = new CItem;
	Item->SetName(L"ITEM");
	Item->setPos(Vec2(ResloutionX / 2 + 1000.f, ResloutionY / 2 + 500.f));
	Item->setScale(Vec2(25.f, 25.f));
	AddObject(Item, GROUP_TYPE::ITEM);

	CColliderMgr::Instance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CColliderMgr::Instance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::FURNITURE);
	CColliderMgr::Instance()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);
	CColliderMgr::Instance()->CheckGroup(GROUP_TYPE::FURNITURE, GROUP_TYPE::PROJ_PLAYER);
	CColliderMgr::Instance()->CheckGroup(GROUP_TYPE::FURNITURE, GROUP_TYPE::PROJ_MONSTER);
	CColliderMgr::Instance()->CheckGroup(GROUP_TYPE::FURNITURE, GROUP_TYPE::MONSTER);
	CColliderMgr::Instance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::ITEM);
	CFindingMgr::Instance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);

	//Camera Look ����
	CCamera::Instance()->SetLookAt(Resolution / 2.f);
}

void Scene_Stage01::Exit() {
	DeleteAll();

	CColliderMgr::Instance()->Reset();
}