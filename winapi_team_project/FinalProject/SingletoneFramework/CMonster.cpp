#include "pch.h"
#include "CMonster.h"
#include "math.h"

#include "CTimeMgr.h"
#include "CCollider.h"
#include "CMissile.h"
#include "CPlayer.h"

CMonster::CMonster()
	: Speed(100.f)
	, CenterPos(Vec2(0.f, 0.f))
	, MaxDis(50.f)
	, Dir(1)
	, iHP(1)
	, Theta(PI / 4.f)
	, DirVec(Vec2(1.f, 1.f))
	, selection(1)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(42.f, 42.f));
}

CMonster::~CMonster()
{
}

void CMonster::Update()	{
	Vec2 curPos = getPos();

	//// ���� �������� �ð��� Speed ��ŭ �̵�
	//curPos.x += fDT * Speed * Dir;

	//// ��ȸ �Ÿ� �������� �Ѿ���� Ȯ��
	//float dist = abs(CenterPos.x - curPos.x) - MaxDis;

	//if (0.f < dist) {
	//	// ���� ����
	//	Dir *= -1;
	//	curPos.x += dist * Dir;
	//}

	setPos(curPos);
}

void CMonster::OnCollisionEnter(CCollider* _pOther) {
	CObject* OtherObj = _pOther->GetObj();

	if (OtherObj->GetName() == L"Missile_Player") {
		iHP -= 1;

		if (iHP <= 0)
			DeleteObject(this);
	}
}