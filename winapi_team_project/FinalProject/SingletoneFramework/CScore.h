#pragma once

#include "CObject.h"

class CScore :
	public CObject
{
private:
	int Point;

public:
	CScore();
	~CScore();

	virtual void Update();
	virtual void Render(HDC _dc);

	void setPoint(int _po) { Point = _po; }
	int getPoint() { return Point; }

	CLONE(CScore);

};