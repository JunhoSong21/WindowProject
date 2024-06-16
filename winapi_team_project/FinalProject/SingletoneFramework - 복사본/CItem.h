
#pragma once

#include "CObject.h"

class CTexture;

class CItem :
	public CObject
{
private:
	int Type;
	CTexture* tex;

public:
	CItem();
	~CItem();

	virtual void Update();
	virtual void Render(HDC _dc);
	void OnCollision(CCollider* _pOther);
	CLONE(CItem);

};