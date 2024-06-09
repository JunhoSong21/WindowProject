#pragma once
#include "CObject.h"

class CMissile :
	public CObject
{
private:
	float	Theta;
	Vec2	Dir;

public:
	CMissile();
	~CMissile();

	virtual void Update();
	virtual void Render(HDC _hDC);

	void SetDir(float _th) { Theta = _th; }
	void SetDir(Vec2 _dir) {
		Dir = _dir;
		Dir.Normalize();
	}
};

