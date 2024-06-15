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
	Vec2 ptPos = getPos();

	setPos(ptPos);
}

void Cstage_01::Render(HDC _dc)
{
	int width = (int)tex->Width();
	int height = (int)tex->Height();


	int ResloutionX = GetSystemMetrics(SM_CXSCREEN);
	int ResloutionY = GetSystemMetrics(SM_CYSCREEN);

	Vec2 ptPos = Vec2(ResloutionX, ResloutionY);
	Vec2 RenderPos = CCamera::Instance()->GetRenderPos(ptPos);

	TransparentBlt(_dc
		, int(RenderPos.x - (float)(width * 2))
		, int(RenderPos.y - (float)(height * 2))
		, width*3
		, height*3
		, tex->GetDC()
		, 0, 0, width, height
		, RGB(255, 0, 255));

	CommponentRender(_dc);
}