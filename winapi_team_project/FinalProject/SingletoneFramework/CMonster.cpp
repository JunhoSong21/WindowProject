#include "pch.h"
#include "CMonster.h"

#include "CTimeMgr.h"
#include "CCollider.h"

CMonster::CMonster()
	: Speed(100.f)
	, CenterPos(Vec2(0.f, 0.f))
	, MaxDis(50.f)
	, Dir(1)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(42.f, 42.f));
}

CMonster::~CMonster()
{
}

void CMonster::Update()	{
	Vec2 curPos = getPos();

	// ���� �������� �ð��� Speed ��ŭ �̵�
	curPos.x += fDT * Speed * Dir;

	// ��ȸ �Ÿ� �������� �Ѿ���� Ȯ��
	float dist = abs(CenterPos.x - curPos.x) - MaxDis;

	if (0.f < dist) {
		// ���� ����
		Dir *= -1;
		curPos.x += dist * Dir;
	}

	setPos(curPos);
}
