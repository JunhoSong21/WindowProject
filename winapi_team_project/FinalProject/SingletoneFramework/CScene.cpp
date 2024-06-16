#include "pch.h"
#include "CScene.h"
#include "CObject.h"
#include "CScore.h"
#pragma warning(disable:4996)

CScene::CScene()
	:Point(0)
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
}

void CScene::FinalUpdate() {
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i) {
		for (size_t j = 0; j < arrObj[i].size(); ++j) {
			arrObj[i][j]->FinalUpdate();
		}
	}
}

void CScene::Render(HDC _hDC) {
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

	Point = CScore::Instance()->getPoint();

	Rectangle(_hDC, ptPos.x, ptPos.y, ptPos.x + 350, ptPos.y + 50);

	char CharPoint[20];
	sprintf(CharPoint, "%d", Point);

	RECT rt = { ptPos.x, 0,ptPos.x + 350.,50 };
	SetBkMode(_hDC, TRANSPARENT);
	SetTextColor(_hDC, RGB(0, 0, 0));
	DrawTextA(_hDC, CharPoint, strlen(CharPoint), &rt, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	/*HFONT hFont = CreateFont(0, 0, 0, 0, FW_DONTCARE,
		false, false, false, ANSI_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH, L"h8514oem");

	HFONT oldFont = (HFONT)SelectObject(hDC, hFont);*/
}

void CScene::DeleteGroup(GROUP_TYPE _Target) {
	Safe_Delete_Vec(arrObj[(UINT)_Target]);
}

void CScene::DeleteAll() {
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i) {
		DeleteGroup((GROUP_TYPE)i);
	}
}