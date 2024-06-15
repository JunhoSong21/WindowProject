#include "pch.h"
#include "CAnimation.h"
#include "CTimeMgr.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CObject.h"
#include "CCamera.h"

CAnimation::CAnimation()
	: animator(nullptr)
	, tex(nullptr)
	, curFrm(0)
	, accTime(0.f)
	, finish(false)
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::Update() {

	if (finish)
		return;

	accTime += fDT;

	if (vecFrm[curFrm].Duration < accTime) {

		accTime = accTime - vecFrm[curFrm].Duration;

		++curFrm;

		if (vecFrm.size() <= curFrm) {
			curFrm = -1;
			finish = true;
		}
	}
}

void CAnimation::Render(HDC _hDC) {
	if (finish)
		return;

	CObject* Obj = animator->GetObj();
	Vec2 ptPos = Obj->getPos();

	ptPos += vecFrm[curFrm].offSet; // offSet만큼 추가 이동위치

	//랜더링 좌표로 변환
	ptPos = CCamera::Instance()->GetRenderPos(ptPos);
	
	TransparentBlt(_hDC
		, (int)ptPos.x - vecFrm[curFrm].ptSlice.x-10
		, (int)ptPos.y - vecFrm[curFrm].ptSlice.y-10
		, (int)vecFrm[curFrm].ptSlice.x *2+30
		, (int)vecFrm[curFrm].ptSlice.y *2+30
		, tex->GetDC()
		, (int)vecFrm[curFrm].ptLT.x
		, (int)vecFrm[curFrm].ptLT.y
		, (int)vecFrm[curFrm].ptSlice.x
		, (int)vecFrm[curFrm].ptSlice.y
		, RGB(255, 0, 255)
		);
}

void CAnimation::Create(CTexture* _Tex, Vec2 _LT, Vec2 _SliceSize, 
	Vec2 _Step, float _Duration, UINT _FrameCount) {

	tex = _Tex;

	AnimFrm frm = {};
	for (UINT i = 0; i < _FrameCount; ++i) {
		frm.Duration = _Duration;
		frm.ptSlice = _SliceSize;
		frm.ptLT = _LT + _Step * (float)i;

		vecFrm.push_back(frm);
	}
}