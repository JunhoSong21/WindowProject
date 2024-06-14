#include "pch.h"
#include "CText.h"

#include "CCore.h"
#include "CTimeMgr.h"
#include "SelectGDI.h"

CText::CText()
	: CenterPos(Vec2(0.f, 0.f))
	, ScalePos(Vec2(0.f, 0.f))
{
}

CText::~CText()
{
}

void CText::Update() 
{
}

void CText::Render(HDC hDC) {
	Vec2 ptPos = getPos();
	Vec2 ptScale = getScale();
	
	/*HFONT hFont = CreateFont(0, 0, 0, 0, FW_DONTCARE,
		false, false, false, ANSI_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH, L"h8514oem");

	HFONT oldFont = (HFONT)SelectObject(hDC, hFont);*/

	RECT rt = { 1800, 1450, 2040, 1550 }; 
	SetBkMode(hDC, TRANSPARENT);
	// SelectGDI w(hDC, PEN_TYPE::WHITE);
	SetTextColor(hDC, RGB(255, 255, 255));
	DrawText(hDC, L"PRESS ENTER", 15, &rt, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
}