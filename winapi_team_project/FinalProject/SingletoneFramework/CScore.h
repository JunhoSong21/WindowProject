#pragma once

#include "CObject.h"

class CObject;

class CScore {
	SINGLE(CScore);
private:
	int Point;

public:
	void setPoint(int _po) { Point = _po; }
	int getPoint() { return Point; }
};