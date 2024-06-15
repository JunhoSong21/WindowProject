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
	float	Speed;
	bool	isItem;

	void CreateItem();

public:
	CMissile();
	~CMissile();

	virtual void Update();
	virtual void Render(HDC _hDC);

	virtual void OnCollisionEnter(CCollider* _pOther);

	void SetDir(float _th) { Theta = _th; }
	void SetSpd(float _Sp) { Speed = _Sp; }
	void SetDir(Vec2 _dir) {
		Dir = _dir;
		Dir.Normalize();
	}
	void Setlen(float len) { length = len; }
	float getlen() { return length; }
	void SetItem(bool _It) { isItem = _It; }
	bool getItem() { return isItem; }

	CLONE(CMissile);
};

