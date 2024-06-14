#pragma once

#include "CObject.h"

class CText :
	public CObject
{
private:
	Vec2 CenterPos; // 중앙 기준점
	Vec2 ScalePos; // 문자열의 너비와 높이

public:
	CText();
	~CText();

	virtual void Update();
	virtual void Render(HDC hDC);

	CLONE(CText);
};

