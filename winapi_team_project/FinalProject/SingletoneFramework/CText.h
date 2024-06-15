#pragma once

#include "CObject.h"

class CText :
	public CObject
{
private:

public:
	CText();
	~CText();

	virtual void Update();
	virtual void Render(HDC hDC);

	CLONE(CText);
};

