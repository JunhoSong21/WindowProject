#pragma once

#include "CObject.h"

class CMonster:
	public CObject
{
private:
	Vec2	CenterPos; // �߾� ������
	float	Speed;
	float	MaxDis; // �ִ� �̵��Ÿ�
	int		Dir; // ����(1, -1)

	int		iHP;

public:
	CMonster();
	~CMonster();

	virtual void Update();

	CLONE(CMonster);

	float GetSpeed() { return Speed; }
	Vec2 GetCenterPos() { return CenterPos; }

	void SetSpeed(float spd) { Speed = spd; }
	void SetMoveDist(float dis) { MaxDis = dis; }
	void SetCenterPos(Vec2 _Pos) { CenterPos = _Pos; }

	virtual void OnCollisionEnter(CCollider* _pOther);
};