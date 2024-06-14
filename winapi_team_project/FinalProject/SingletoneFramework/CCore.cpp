#include "pch.h"
#include "CCore.h"

#include "CColliderMgr.h"
#include "CEventMgr.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"
#include "CResMgr.h"
#include "CSceneMgr.h"
#include "CTimeMgr.h"

#include "CObject.h"
#include "CCamera.h"
#include "CSound.h"

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
	CSoundMgr::Instance()->Init();

	CResMgr::Instance()->LoadSound(L"BGM", L"Sound//MainBGM.wav");
	CSound* NewSound = CResMgr::Instance()->FindSound(L"BGM");

	NewSound->PlayToBGM(true);
	NewSound->SetPosition(0.f);
	NewSound->SetVolume(20.f);
	// NewSound->PlayToBGM(true);

	return S_OK;
}

void CCore::Progress() {
	// 매니저 업데이트
	CTimeMgr::Instance()->Update();
	CKeyMgr::Instance()->Update();
	CCamera::Instance()->Update();

	CSceneMgr::Instance()->Update();

	// 충돌체크
	CColliderMgr::Instance()->Update();

	Rectangle(mDC, -1, -1, ptResolution.x + 1, ptResolution.y + 1);

	CSceneMgr::Instance()->Render(mDC);
	BitBlt(hDC, 0, 0, ptResolution.x, ptResolution.y, mDC, 0, 0, SRCCOPY);

	CTimeMgr::Instance()->Render();

	// 이벤트 지연처리
	CEventMgr::Instance()->Update();
}

void CCore::CreateBrushPen() {
	arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	arrBrush[(UINT)BRUSH_TYPE::BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);
	arrBrush[(UINT)BRUSH_TYPE::WHITE] = (HBRUSH)GetStockObject(WHITE_BRUSH);

	arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	arrPen[(UINT)PEN_TYPE::WHITE] = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
}