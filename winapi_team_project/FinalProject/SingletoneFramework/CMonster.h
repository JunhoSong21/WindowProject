#pragma once
#include "CObject.h"

class CMonster:
	public CObject
{
private:
	float	Speed;
	float	MaxDis; // �ִ� �̵��Ÿ�
	int		Dir; // ����(1, -1)
	Vec2	CenterPos; // �߾� ������

public:
	CMonster();
	~CMonster();

	virtual void Update();

	float GetSpeed() { return Speed; }
	Vec2 GetCenterPos() { return CenterPos; }

	void SetSpeed(float spd) { Speed = spd; }
	void SetMoveDist(float dis) { MaxDis = dis; }
	void SetCenterPos(Vec2 _Pos) { CenterPos = _Pos; }
};