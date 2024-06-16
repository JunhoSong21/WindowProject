#include "pch.h"
#include "CCamera.h"

#include "CCore.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CObject.h"

CCamera::CCamera()
	: TargetObj(nullptr)
	, fTime(0.5f)//따라가는데 소요되는 시간
	, fSpeed(0.f)
	, fAccTime(0.5f)
{	
}
CCamera::~CCamera()
{
}

void CCamera::Update()
{
	if (TargetObj)
	{
		if (TargetObj->IsDead()) {
			TargetObj = nullptr;
		}
		else {
			LookAt = TargetObj->getPos();
		}
	}


	//화면 중앙과 카메라 좌표 비교
	CalDiff();
}

void CCamera::CalDiff() {
	//이전 LookAt과 현재 Look의 차이값을 보정해서 현재 LookAt을 구한다. -> 카메라가 플레이어를 천천히 따라간다
	
	fAccTime += fDT;

	if (fTime <= fAccTime) {
		CurLookAt = LookAt;			//시간 초과되면 강제 이동, 아니면 천천히 따라감
	}
	else {
		Vec2 LookDir = LookAt - PrevLookAt;
			CurLookAt = PrevLookAt + LookDir.Normalize() * fSpeed * fDT;
	}

	Vec2 Resolution = CCore::Instance()->GetResolution();
	Vec2 Center = Resolution / 2;

	Diff = CurLookAt - Center;
	PrevLookAt = CurLookAt;
}
