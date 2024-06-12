#include "pch.h"
#include "CMap.h"

#include "CKeyMgr.h"
#include "CResMgr.h"
#include "CPathMgr.h"
#include "CSceneMgr.h"
#include "CTimeMgr.h"

#include "CScene.h"
#include "CTexture.h"

CMap::CMap()
	: tex(nullptr)
{
		tex = CResMgr::Instance()->LoadTexture(L"MapTex", L"texture\\StartScreen.bmp");
}

CMap::~CMap()
{
}

void CMap::Update()
{
	Vec2 ptPos = getPos();

	setPos(ptPos);
}

void CMap::Render(HDC _dc)
{
	int width = (int)tex->Width();
	int height = (int)tex->Height();

	Vec2 ptPos = getPos();

	BitBlt(_dc
		, int(ptPos.x - (float)(width / 2))
		, int(ptPos.y - (float)(height / 2))
		, width, height
		, tex->GetDC()
		, 0, 0, SRCCOPY);

	CommponentRender(_dc);
}
