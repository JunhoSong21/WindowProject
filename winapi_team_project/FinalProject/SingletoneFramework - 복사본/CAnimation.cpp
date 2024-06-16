#include "pch.h"
#include "CAnimation.h"
#include "CTimeMgr.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CObject.h"
#include "CCamera.h"
#include "CKeyMgr.h"

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

    if (Obj->GetName() == L"PLAYER") {
        XFORM xForm;
        XFORM oldXForm;

        // 마우스 포인터와 ptPos 간의 각도 계산
        float angle = atan2f((float)MOUSE_POS.y - ptPos.y, (float)MOUSE_POS.x - ptPos.x);

        // 현재 변환을 저장
        GetWorldTransform(_hDC, &oldXForm);

        // 고급 그래픽 모드 설정
        int oldMode = SetGraphicsMode(_hDC, GM_ADVANCED);

        // 변환을 초기화
        ModifyWorldTransform(_hDC, NULL, MWT_IDENTITY);

        // 회전 중심을 ptPos로 이동
        xForm.eM11 = 1.0f;
        xForm.eM12 = 0.0f;
        xForm.eM21 = 0.0f;
        xForm.eM22 = 1.0f;
        xForm.eDx = (FLOAT)ptPos.x;
        xForm.eDy = (FLOAT)ptPos.y;
        ModifyWorldTransform(_hDC, &xForm, MWT_LEFTMULTIPLY);

        // 회전 변환 설정
        xForm.eM11 = cos(angle);
        xForm.eM12 = sin(angle);
        xForm.eM21 = -sin(angle);
        xForm.eM22 = cos(angle);
        xForm.eDx = 0.0f;
        xForm.eDy = 0.0f;
        ModifyWorldTransform(_hDC, &xForm, MWT_LEFTMULTIPLY);

        // 원래 위치로 이동
        xForm.eM11 = 1.0f;
        xForm.eM12 = 0.0f;
        xForm.eM21 = 0.0f;
        xForm.eM22 = 1.0f;
        xForm.eDx = (FLOAT)-ptPos.x;
        xForm.eDy = (FLOAT)-ptPos.y;
        ModifyWorldTransform(_hDC, &xForm, MWT_LEFTMULTIPLY);

        // 투명하게 비트맵 그리기
        TransparentBlt(_hDC,
            (int)(ptPos.x - vecFrm[curFrm].ptSlice.x - 10),
            (int)(ptPos.y - vecFrm[curFrm].ptSlice.y - 10),
            (int)(vecFrm[curFrm].ptSlice.x * 2 + 30),
            (int)(vecFrm[curFrm].ptSlice.y * 2 + 30),
            tex->GetDC(),
            (int)vecFrm[curFrm].ptLT.x,
            (int)vecFrm[curFrm].ptLT.y,
            (int)vecFrm[curFrm].ptSlice.x,
            (int)vecFrm[curFrm].ptSlice.y,
            RGB(255, 0, 255)
        );

        // 원래 변환으로 복원
        SetWorldTransform(_hDC, &oldXForm);
        SetGraphicsMode(_hDC, oldMode);
    }
    else {
        TransparentBlt(_hDC
            , (int)ptPos.x - vecFrm[curFrm].ptSlice.x - 10
            , (int)ptPos.y - vecFrm[curFrm].ptSlice.y - 10
            , (int)vecFrm[curFrm].ptSlice.x * 2 + 30
            , (int)vecFrm[curFrm].ptSlice.y * 2 + 30
            , tex->GetDC()
            , (int)vecFrm[curFrm].ptLT.x
            , (int)vecFrm[curFrm].ptLT.y
            , (int)vecFrm[curFrm].ptSlice.x
            , (int)vecFrm[curFrm].ptSlice.y
            , RGB(255, 0, 255)
        );
    }
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