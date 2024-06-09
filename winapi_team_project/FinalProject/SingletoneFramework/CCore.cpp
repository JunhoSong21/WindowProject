#include "pch.h"
#include "CCore.h"

#include "CKeyMgr.h"
#include "CColliderMgr.h"
#include "CPathMgr.h"
#include "CSceneMgr.h"
#include "CTimeMgr.h"

#include "CObject.h"

CCore::CCore()
	:handle(0)
	, ptResolution{}
	, hDC(0)
	, mDC(0)
	, hBit(0)
	, arrBrush{}
	, arrPen{}
{
}

CCore::~CCore() {
	ReleaseDC(handle, hDC);

	DeleteDC(mDC);
	DeleteObject(hBit);

	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i) {
		DeleteObject(arrPen[i]);
	}
}

int CCore::Init(HWND _hWnd, POINT _ptResolution) {
	handle = _hWnd;
	ptResolution = _ptResolution;

	RECT rt = { 0, 0, ptResolution.x, ptResolution.y };
	AdjustWindowRect(&rt, WS_POPUPWINDOW, true); // 윈도우가 실제로 그릴 수 있는 영역 ( 윈도우 창 주변으로 생기는 영역 제외)
	SetWindowPos(handle, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);

	hDC = GetDC(handle);
	hBit = CreateCompatibleBitmap(hDC, ptResolution.x, ptResolution.y);
	mDC = CreateCompatibleDC(hDC);
	
	HBITMAP hOldBit = (HBITMAP)SelectObject(mDC, hBit);
	DeleteObject(hOldBit);

	CreateBrushPen();

	// Manager 초기화
	CTimeMgr::Instance()->Init();
	CPathMgr::Instance()->Init();
	CKeyMgr::Instance()->Init();
	CSceneMgr::Instance()->Init();

	return S_OK;
}

void CCore::Progress() {
	CTimeMgr::Instance()->Update();
	CKeyMgr::Instance()->Update();
	CSceneMgr::Instance()->Update();
	CColliderMgr::Instance()->Update();

	Rectangle(mDC, -1, -1, ptResolution.x + 1, ptResolution.y + 1);

	CSceneMgr::Instance()->Render(mDC);
	BitBlt(hDC, 0, 0, ptResolution.x, ptResolution.y, mDC, 0, 0, SRCCOPY);
}

void CCore::CreateBrushPen() {
	arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);

	arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));

}