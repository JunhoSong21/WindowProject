#pragma once
#include "CObject.h"

class CTexture;

class Stage_01 :
	public CObject {
private:
	CTexture* Stage_01_tex;

public:
	Stage_01();
	~Stage_01();

	virtual void Update();
	virtual void Render(HDC _dc);
};