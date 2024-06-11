#include "pch.h"
#include "CEventMgr.h"

#include "CSceneMgr.h"
#include "CObject.h"
#include "CScene.h"

CEventMgr::CEventMgr() 
{
}

CEventMgr::~CEventMgr() 
{
}

void CEventMgr::Update() {
	// 이전 프레임에서 등록해둔 Dead Object들을 삭제한다.
	for (size_t i = 0; i < vecDead.size(); ++i) {
		delete vecDead[i];
	}
	vecDead.clear();

	for (size_t i = 0; i < vecEvent.size(); ++i) {
		Excute(vecEvent[i]);
	}
	vecEvent.clear();
}

void CEventMgr::Excute(const tEvent& _eve) {
	switch (_eve.eEven) {
	case EVENT_TYPE::CREATE_OBJECT:
	{
		// lParam : 오브젝트 주소
		// wParam : GROUP_TYPE
		CObject* NewObj = (CObject*)_eve.lParam;
		GROUP_TYPE Type = (GROUP_TYPE)_eve.wParam;

		CSceneMgr::Instance()->GetCurScene()->AddObject(NewObj, Type);
	}
		break;
	case EVENT_TYPE::DELETE_OBJECT:
	{
		// lParam : 오브젝트 주소
		// wParam : 어짜피 삭제할거라 뭔지 알빠 아님
		// Object를 Dead 상태로 변경
		// 삭제 예정 오브젝트들을 모아둔다
		CObject* DeadObj = (CObject*)_eve.lParam;
		DeadObj->SetDead();
		vecDead.push_back(DeadObj);
	}
		break;
	case EVENT_TYPE::SCENE_CHANGE:
		// lParam : 다음 Scene_Type
		CSceneMgr::Instance()->ChangeScene((SCENE_TYPE)_eve.lParam);
		break;
	}
}