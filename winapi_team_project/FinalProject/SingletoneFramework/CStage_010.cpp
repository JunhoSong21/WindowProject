#include "pch.h"
#include "CStage_010.h"
#include "CCore.h"
#include "CKeyMgr.h"
#include "CResMgr.h"
#include "CPathMgr.h"
#include "CSceneMgr.h"
#include "CTimeMgr.h"

#include "CScene.h"
#include "CTexture.h"
#include "SelectGDI.h"

CStage_010::CStage_010()
	: tex(nullptr)
{
	tex = CResMgr::Instance()->LoadTexture(L"Stage_010", L"Texture\\Stage_010.bmp");
}

CStage_010::~CStage_010()
{
}

void CStage_010::Update()
{
	Vec2 ptPos = getPos();

	setPos(ptPos);
}

void CStage_010::Render(HDC _dc)
{
	int width = (int)tex->Width();
	int height = (int)tex->Height();


	int ResloutionX = GetSystemMetrics(SM_CXSCREEN);
	int ResloutionY = GetSystemMetrics(SM_CYSCREEN);

	Vec2 ptPos = getPos();
	Vec2 RenderPos = CCamera::Instance()->GetRenderPos(ptPos);

	TransparentBlt(_dc
		, RenderPos.x - width * 2
		, RenderPos.y - height * 2
		, width * 3
		, height * 3
		, tex->GetDC()
		, 0, 0, width, height
		, RGB(255, 0, 255));

	CommponentRender(_dc);
}