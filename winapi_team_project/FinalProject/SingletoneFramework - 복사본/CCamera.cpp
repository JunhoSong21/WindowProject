#include "pch.h"
#include "CCamera.h"

#include "CCore.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CObject.h"

CCamera::CCamera()
	: TargetObj(nullptr)
	, fTime(0.5f)//���󰡴µ� �ҿ�Ǵ� �ð�
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


	//ȭ�� �߾Ӱ� ī�޶� ��ǥ ��
	CalDiff();
}

void CCamera::CalDiff() {
	//���� LookAt�� ���� Look�� ���̰��� �����ؼ� ���� LookAt�� ���Ѵ�. -> ī�޶� �÷��̾ õõ�� ���󰣴�
	
	fAccTime += fDT;

	if (fTime <= fAccTime) {
		CurLookAt = LookAt;			//�ð� �ʰ��Ǹ� ���� �̵�, �ƴϸ� õõ�� ����
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
