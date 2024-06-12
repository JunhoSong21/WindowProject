#pragma once
#include "CObject.h"

class CTexture;

class CStartScreen :
	public CObject {
private:
	CTexture* tex;

	CLONE(CStartScreen);
public:
	CStartScreen();
	~CStartScreen();

	virtual void Update();
	virtual void Render(HDC _dc);
};