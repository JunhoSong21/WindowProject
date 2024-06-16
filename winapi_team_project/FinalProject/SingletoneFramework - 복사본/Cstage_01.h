#pragma once
#include "CObject.h"

class CTexture;

class Cstage_01 :
	public CObject {
private:
	CTexture* tex;

	CLONE(Cstage_01);
public:
	Cstage_01();
	~Cstage_01();

	virtual void Update();
	virtual void Render(HDC _dc);
};