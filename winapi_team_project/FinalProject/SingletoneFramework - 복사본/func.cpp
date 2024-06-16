#include "pch.h"
#include "func.h"

#include "CEventMgr.h"

void CreateObject(CObject* _Obj, GROUP_TYPE _Group) {
	tEvent evn = { };
	evn.eEven = EVENT_TYPE::CREATE_OBJECT;
	evn.lParam = (DWORD_PTR)_Obj;
	evn.wParam = (DWORD_PTR)_Group;

	CEventMgr::Instance()->AddEvent(evn);
}

void DeleteObject(CObject* _Obj) {
	tEvent evn = { };
	evn.eEven = EVENT_TYPE::DELETE_OBJECT;
	evn.lParam = (DWORD_PTR)_Obj;

	CEventMgr::Instance()->AddEvent(evn);
}

void ChangeScene(SCENE_TYPE _Next) {
	tEvent evn = { };
	evn.eEven = EVENT_TYPE::SCENE_CHANGE;
	evn.lParam = (DWORD_PTR)_Next;

	CEventMgr::Instance()->AddEvent(evn);
}