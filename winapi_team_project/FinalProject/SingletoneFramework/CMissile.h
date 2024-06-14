#pragma once
#include "CObject.h"

class CMissile :
	public CObject
{
private:
	float	Theta;
	Vec2	Dir;
	float	Distance;
	float	length;
public:
	CMissile();
	~CMissile();

	virtual void Update();
	virtual void Render(HDC _hDC);

	virtual void OnCollisionEnter(CCollider* _pOther);

	void SetDir(float _th) { Theta = _th; }
	void SetDir(Vec2 _dir) {
		Dir = _dir;
		Dir.Normalize();
	}
	void Setlen(float len) { length = len; }
	float getlen() { return length; }

	CLONE(CMissile);
};

