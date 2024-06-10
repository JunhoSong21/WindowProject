#include "pch.h"
#include "CCamera.h"

#include "CObject.h"
#include "CCore.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

CCamera::CCamera()
	: TargetObh(nullptr)
	, fTime(.5f)//���󰡴µ� �ҿ�Ǵ� �ð�
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

	//ȭ�� �߾Ӱ� ī�޶� ��ǥ ��
	CalDiff();
}

void CCamera::CalDiff()
{
	//���� LookAt�� ���� Look�� ���̰��� �����ؼ� ���� LookAt�� ���Ѵ�. -> ī�޶� �÷��̾ õõ�� ���󰣴�
	
	fAccTime += fDT;

	if (fTime <= fAccTime)
	{
		CurLookAt = LookAt;			//�ð� �ʰ��Ǹ� ���� �̵�, �ƴϸ� õõ�� ����
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
