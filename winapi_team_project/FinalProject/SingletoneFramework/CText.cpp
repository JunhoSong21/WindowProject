#include "pch.h"
#include "CText.h"
#include <tchar.h>

#include "CCore.h"
#include "CTimeMgr.h"
#include "SelectGDI.h"

CText::CText()
{
}

CText::~CText()
{
}

void CText::Update() 
{
}

void CText::Render(HDC hDC) {

	//RECT rt = { 0,1400,500,1600 };
	//SetBkMode(hDC, TRANSPARENT);
	//SetTextColor(hDC, RGB(255, 255, 255));
	//DrawText(hDC, L"PRESS ENTER", lstrlen(L"PRESS ENTER"), &rt, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
}