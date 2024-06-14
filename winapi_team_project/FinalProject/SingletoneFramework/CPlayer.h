#pragma once
#include "CObject.h"

class CTexture;

class CPlayer : 
	public CObject {
private:
	int Selection;
	void CreateMissile();

	CLONE(CPlayer);
public:
	CPlayer();
	~CPlayer();

	virtual void Update();
	virtual void Render(HDC _dc);
};

