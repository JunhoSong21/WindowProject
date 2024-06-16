#include "pch.h"

#include "CSceneMgr.h"
#include "CSceneMgr.h"
#include "Scene_Start.h"
#include "Scene_Stage010.h"
#include "Scene_Stage01.h"

CSceneMgr::CSceneMgr()
	:arrScene(),
	curScene(nullptr)
{
}

CSceneMgr::~CSceneMgr() {
	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; ++i) {
		if (nullptr != arrScene[i])
			delete arrScene[i];
	}
}

void CSceneMgr::Init() {
	arrScene[(UINT)SCENE_TYPE::START] = new Scene_Start;
	arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");

	arrScene[(UINT)SCENE_TYPE::STAGE_010] = new Scene_Stage010;
	arrScene[(UINT)SCENE_TYPE::STAGE_010]->SetName(L"Stage010 Scene");

	arrScene[(UINT)SCENE_TYPE::STAGE_01] = new Scene_Stage01;
	arrScene[(UINT)SCENE_TYPE::STAGE_01]->SetName(L"Stage01 Scene");

	// ÇöÀç ¾À ÁöÁ¤
	curScene = arrScene[(UINT)SCENE_TYPE::START];
	curScene->Enter();
}

void CSceneMgr::Update() {
	curScene->Update();
	curScene->FinalUpdate();
}

void CSceneMgr::Render(HDC _hDC) {
	curScene->Render(_hDC);
}

void CSceneMgr::ChangeScene(SCENE_TYPE _Next) {
	curScene->Exit();

	curScene = arrScene[(UINT)_Next];

	curScene->Enter();
}