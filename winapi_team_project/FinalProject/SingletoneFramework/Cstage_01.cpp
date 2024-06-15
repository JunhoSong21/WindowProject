#include "pch.h"
#include "Cstage_01.h"
#include "CCore.h"
#include "CKeyMgr.h"
#include "CResMgr.h"
#include "CPathMgr.h"
#include "CSceneMgr.h"
#include "CTimeMgr.h"

#include "CScene.h"
#include "CTexture.h"
#include "SelectGDI.h"

Cstage_01::Cstage_01()
	: tex(nullptr)
{
	tex = CResMgr::Instance()->LoadTexture(L"Stage_01", L"Texture\\Stage_01.bmp");
}

Cstage_01::~Cstage_01()
{
}

void Cstage_01::Update()
{
}

void Cstage_01::Render(HDC _dc)
{
	Vec2 ptPos = getPos();

	int ResloutionX = GetSystemMetrics(SM_CXSCREEN);
	int ResloutionY = GetSystemMetrics(SM_CYSCREEN);

	StretchBlt(_dc
		, 0, 0
		, ResloutionX, ResloutionY
		, tex->GetDC()
		, 0, 0
		, 3840, 2160
		, SRCCOPY);

	CommponentRender(_dc);
}