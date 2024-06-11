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
	// ���� �����ӿ��� ����ص� Dead Object���� �����Ѵ�.
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
		// lParam : ������Ʈ �ּ�
		// wParam : GROUP_TYPE
		CObject* NewObj = (CObject*)_eve.lParam;
		GROUP_TYPE Type = (GROUP_TYPE)_eve.wParam;

		CSceneMgr::Instance()->GetCurScene()->AddObject(NewObj, Type);
	}
		break;
	case EVENT_TYPE::DELETE_OBJECT:
	{
		// lParam : ������Ʈ �ּ�
		// wParam : ��¥�� �����ҰŶ� ���� �˺� �ƴ�
		// Object�� Dead ���·� ����
		// ���� ���� ������Ʈ���� ��Ƶд�
		CObject* DeadObj = (CObject*)_eve.lParam;
		DeadObj->SetDead();
		vecDead.push_back(DeadObj);
	}
		break;
	case EVENT_TYPE::SCENE_CHANGE:
		// lParam : ���� Scene_Type
		CSceneMgr::Instance()->ChangeScene((SCENE_TYPE)_eve.lParam);
		break;
	}
}