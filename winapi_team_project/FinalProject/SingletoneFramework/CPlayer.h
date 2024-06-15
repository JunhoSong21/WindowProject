#pragma once
#include "CObject.h"

class CTexture;

class CPlayer : 
	public CObject {
private:
	void CreateMissile();
	void ThrowItem();
	float Attack;

	CLONE(CPlayer);
public:
	CPlayer();
	~CPlayer();

	virtual void Update();
	virtual void Render(HDC _dc);
	virtual void OnCollision(CCollider* _pOther);
};