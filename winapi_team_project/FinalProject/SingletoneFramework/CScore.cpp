#include "pch.h"
#include "CScore.h"
#include "CTimeMgr.h"
#include <cstdlib>
#pragma warning(disable:4996)

CScore::CScore()
	:Point(0)
{
}

CScore::~CScore()
{
}

void CScore::Update() {
	Vec2 curPos = getPos();

	setPos(curPos);
}

void CScore::Render(HDC _dc) {

	Vec2 ptPos = getPos();
	Vec2 RenderPos = CCamera::Instance()->GetRenderPos(ptPos);

	/*HFONT hFont = CreateFont(0, 0, 0, 0, FW_DONTCARE,
		false, false, false, ANSI_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH, L"h8514oem");

	HFONT oldFont = (HFONT)SelectObject(hDC, hFont);*/
	Rectangle(_dc, ptPos.x, ptPos.y, ptPos.x + 350, ptPos.y + 50);

	char CharPoint[20];
	sprintf(CharPoint, "%d", Point);

	RECT rt = {ptPos.x, 0,ptPos.x+350.,50 };
	SetBkMode(_dc, TRANSPARENT);
	SetTextColor(_dc, RGB(0,0,0));
	DrawTextA(_dc, CharPoint, strlen(CharPoint), &rt, DT_VCENTER | DT_CENTER | DT_SINGLELINE);

	CommponentRender(_dc);
}