#include "pch.h"
#include "CStartScreen.h"
#include "CCore.h"
#include "CKeyMgr.h"
#include "CResMgr.h"
#include "CPathMgr.h"
#include "CSceneMgr.h"
#include "CTimeMgr.h"

#include "CScene.h"
#include "CTexture.h"
#include "SelectGDI.h"

CStartScreen::CStartScreen()
	: tex(nullptr)
{
		tex = CResMgr::Instance()->LoadTexture(L"MapTex", L"Texture\\StartScreen.bmp");
}

CStartScreen::~CStartScreen()
{
}

void CStartScreen::Update()
{
}

void CStartScreen::Render(HDC _dc)
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

	SelectGDI b(tex->GetDC(), BRUSH_TYPE::BLACK);
	Rectangle(tex->GetDC(), 0, 1400, 3840, 1600);

	// 비슷한 폰트 목록
	// coure, serife, smalle, h8514sys, h8514oem

	RECT rt = { 0,0,ResloutionX,1200 };
	SetBkMode(_dc, TRANSPARENT);
	SetTextColor(_dc, RGB(255, 255, 255));
	DrawText(_dc, L"PRESS ENTER", lstrlen(L"PRESS ENTER"), &rt, DT_VCENTER | DT_CENTER | DT_SINGLELINE);

	CommponentRender(_dc);
}