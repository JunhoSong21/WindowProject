#pragma once

#include "CObject.h"

class CObstract :
	public CObject
{

public:
	CObstract();
	~CObstract();

	virtual void Update();

	CLONE(CObstract);

};