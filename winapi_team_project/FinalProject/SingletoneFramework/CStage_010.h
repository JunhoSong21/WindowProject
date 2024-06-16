#pragma once
#include "CObject.h"

class CTexture;

class CStage_010 :
	public CObject {
private:
	CTexture* tex;

	CLONE(CStage_010);
public:
	CStage_010();
	~CStage_010();

	virtual void Update();
	virtual void Render(HDC _dc);
};