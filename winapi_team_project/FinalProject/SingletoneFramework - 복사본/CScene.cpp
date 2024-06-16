#include "pch.h"
#include "CScene.h"
#include "CObject.h"
#include "CScore.h"
#pragma warning(disable:4996)

CScene::CScene()
	: Point(0)
	, InvPoint(0)
	, RR(50)
	, GG(50)
	, BB(50)
	, colortime(0)
{
}

CScene::~CScene() {
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i) {
		for (size_t j = 0; j < arrObj[i].size(); ++j) {
			delete arrObj[i][j]; // arrObj[i] > ±×·ì º¤ÅÍ¿¡ ÀÖ´Â j¹øÂ° °´Ã¼ ¼Ò¸ê
		}
	}
}

void CScene::Update() {
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i) {
		for (size_t j = 0; j < arrObj[i].size(); ++j) {
			if (!arrObj[i][j]->IsDead())
				arrObj[i][j]->Update();
		}
	}
	
	if (colortime < 10) {
		RR++;
		BB--;
	}
	else if (colortime < 20) {
		BB++;
		GG--;
	}
	else if(colortime < 30) {
		GG++;
		RR--;
	}
	else {
		colortime = 0;
	}
}

void CScene::FinalUpdate() {
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i) {
		for (size_t j = 0; j < arrObj[i].size(); ++j) {
			arrObj[i][j]->FinalUpdate();
		}
	}
}

void CScene::Render(HDC _hDC) {

	float ResloutionX = GetSystemMetrics(SM_CXSCREEN);
	float ResloutionY = GetSystemMetrics(SM_CYSCREEN);

	RECT Bkrt = { -ResloutionX ,-ResloutionY ,ResloutionX * 2 ,ResloutionY * 2 };
	HBRUSH hBrush = CreateSolidBrush(RGB(RR, GG, BB));
	HBRUSH oldBrush = (HBRUSH)SelectObject(_hDC, hBrush);
	FillRect(_hDC, &Bkrt, oldBrush);
	DeleteObject(oldBrush);

	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i) {
		vector<CObject*>::iterator iter = arrObj[i].begin();

		for (; iter != arrObj[i].end();) {
			if (!(*iter)->IsDead()) {
				(*iter)->Render(_hDC);
				++iter;
			}
			else {
				iter = arrObj[i].erase(iter);
			}
		}
	}
	if (InvPoint) {

		Point = CScore::Instance()->getPoint();

		Rectangle(_hDC, ResloutionX - 350, 0, ResloutionX, 50);

		HFONT hFont = CreateFont(30, 20, 0, 0, 400,
			0, false, false, ANSI_CHARSET,
			OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, DEFAULT_PITCH, L"h8514oem");

		HFONT oldFont = (HFONT)SelectObject(_hDC, hFont);

		char CharPoint[20];
		sprintf(CharPoint, "%d", Point);
		strcat(CharPoint, "pt");

		RECT rt = { ResloutionX - 350, 0, ResloutionX, 50 };
		SetBkMode(_hDC, TRANSPARENT);
		SetTextColor(_hDC, RGB(150, 150, 150));
		DrawTextA(_hDC, CharPoint, strlen(CharPoint), &rt, DT_VCENTER | DT_CENTER | DT_SINGLELINE);

		rt.left -= 3;
		rt.right -= 3;
		rt.top -= 2;
		rt.bottom -= 2;

		SetTextColor(_hDC, RGB(0, 0, 0));
		DrawTextA(_hDC, CharPoint, strlen(CharPoint), &rt, DT_VCENTER | DT_CENTER | DT_SINGLELINE);

	}
}

void CScene::DeleteGroup(GROUP_TYPE _Target) {
	Safe_Delete_Vec(arrObj[(UINT)_Target]);
}

void CScene::DeleteAll() {
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i) {
		DeleteGroup((GROUP_TYPE)i);
	}
}