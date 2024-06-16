#include "pch.h"
#include "CCore.h"
#include "CTimeMgr.h"

CTimeMgr::CTimeMgr()
	:curCount{}
	, prevCount{}
	, prequency{}
	, dDT(0.)
	, dAcc(0.)
	, iCallCount(0)
{
}

CTimeMgr::~CTimeMgr()
{
}

void CTimeMgr::Init()
{
	QueryPerformanceCounter(&prevCount);
	QueryPerformanceFrequency(&prequency);
}

void CTimeMgr::Update()
{
	QueryPerformanceCounter(&curCount);
	dDT = (double)(curCount.QuadPart - prevCount.QuadPart) / (double)prequency.QuadPart;

	prevCount = curCount;

#ifdef _DEBUG
	if (dDT > (1. / 60.))
		dDT = (1. / 60.);
#endif
}

void CTimeMgr::Render() {
	++iCallCount;
	dAcc += dDT;

	if (dAcc >= 1.) {
		iFPS = iCallCount;
		dAcc = 0.;
		iCallCount = 0;

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS : %d, DT : %f", iFPS, dDT);
		SetWindowText(CCore::Instance()->GetMainHandle(), szBuffer);
	}
}
