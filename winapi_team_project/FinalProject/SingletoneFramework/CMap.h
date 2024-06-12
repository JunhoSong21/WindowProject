#pragma once
#include "CObject.h"

class CTexture;

class CMap :
	public CObject {
private:
	CTexture* tex;

	CLONE(CMap);
public:
	CMap();
	~CMap();

	virtual void Update();
	virtual void Render(HDC _dc);
};
