#pragma once
#include "CObject.h"

class CTexture;

class CPlayer : 
	public CObject {
private:
	CTexture* tex;

	void CreateMissile();

public:
	CPlayer();
	~CPlayer();

	virtual void Update();
	virtual void Render(HDC _dc);
};

