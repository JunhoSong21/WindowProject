#include "pch.h"
#include "CObstract.h"

#include "CTimeMgr.h"
#include "CCollider.h"

CObstract::CObstract()
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(25.f, 100.f));
}

CObstract::~CObstract()
{
}

void CObstract::Update() {
	Vec2 curPos = getPos();

	setPos(curPos);
}