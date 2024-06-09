#include "pch.h"
#include "CSceneMgr.h"
#include "Scene_Start.h"

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

	//arrScene[(UINT)SCENE_TYPE::TOOL] = new TOOL;
	//arrScene[(UINT)SCENE_TYPE::STAGE_01] = new STAGE_01;
	//arrScene[(UINT)SCENE_TYPE::STAGE_02] = new STAGE_02;

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
