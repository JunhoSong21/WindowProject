#include "pch.h"
#include "CCamera.h"

#include "CObject.h"
#include "CCore.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

CCamera::CCamera()
	: TargetObh(nullptr)
	, fTime(.5f)//따라가는데 소요되는 시간
	, fSpeed(0.f)
	, fAccTime(0.f)
{
	
}
CCamera::~CCamera()
{

}

void CCamera::Update()
{
	if (TargetObh)
	{
		if (TargetObh->IsDead()) {
			TargetObh = nullptr;
		}
		else {
			LookAt = TargetObh->getPos();
		}
	}

	if (KEY_HOLD(KEY::UP))
		LookAt.y -= 500.f * fDT;
	if (KEY_HOLD(KEY::DOWN))
		LookAt.y += 500.f * fDT;
	if (KEY_HOLD(KEY::LEFT))
		LookAt.x -= 500.f * fDT;
	if (KEY_HOLD(KEY::RIGHT))
		LookAt.x += 500.f * fDT;

	//화면 중앙과 카메라 좌표 비교
	CalDiff();
}

void CCamera::CalDiff()
{
	//이전 LookAt과 현재 Look의 차이값을 보정해서 현재 LookAt을 구한다. -> 카메라가 플레이어를 천천히 따라간다
	
	fAccTime += fDT;

	if (fTime <= fAccTime)
	{
		CurLookAt = LookAt;			//시간 초과되면 강제 이동, 아니면 천천히 따라감
	}
	else
	{
		Vec2 LookDir = LookAt - PrevLookAt;
		CurLookAt = PrevLookAt + LookDir.Normalize() * fSpeed * fDT;
	}

	Vec2 Resolution = CCore::Instance()->GetResolution();
	Vec2 Center = Resolution / 2;

	Diff = CurLookAt - Center;
	PrevLookAt = CurLookAt;
}
