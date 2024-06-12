#include "pch.h"
#include "CCore.h"
#include "Scene_Enter.h"

#include "CObject.h"
#include "CMap.h"

#include "CColliderMgr.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"
#include "CTexture.h"
#include "CSceneMgr.h"
#include "CCamera.h"
#include "CResMgr.h"

Scene_Enter::Scene_Enter() {

}

Scene_Enter::~Scene_Enter() {

}
void Scene_Enter::Update() {
	CScene::Update();

	if (KEY_TAP(KEY::ENTER)) {
		ChangeScene(SCENE_TYPE::START);
	}
}


void Scene_Enter::Enter() {
	CObject* Entrance = nullptr;
	Entrance = new CMap;
	Entrance->SetName(L"Entrance");
	Entrance->setPos(Vec2(640.f, 384.f));
	Entrance->setScale(Entrance->getScale());
	AddObject(Entrance, GROUP_TYPE::MAP);
}


void Scene_Enter::Exit() {
	DeleteAll();

	CColliderMgr::Instance()->Reset();
}