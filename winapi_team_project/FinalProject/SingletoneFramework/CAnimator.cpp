#include "pch.h"
#include "CAnimator.h"
#include "CAnimation.h"

CAnimator::CAnimator()
	: curAnim(nullptr)
	, owner(nullptr)
	, repeat(false)
{
}

CAnimator::~CAnimator() {
	Safe_Delete_Map(mapAnim);
}

void CAnimator::Update() {
	if (nullptr != curAnim) {
		curAnim->Update();

		if (repeat && curAnim->IsFinish())
			curAnim->SetFrame(0);
	}
}

void CAnimator::Render(HDC _hDC) {
	if (nullptr != curAnim)
		curAnim->Render(_hDC);
}

void CAnimator::CreateAnimation(const wstring& _strName, CTexture* _Tex, Vec2 _LT, Vec2 _SliceSize, 
	Vec2 _Step, float _Duration, UINT _FrameCount) {

	CAnimation* Anim = FindAnimation(_strName);

	assert(nullptr == Anim);
	
	Anim = new CAnimation;
	Anim->SetName(_strName);
	Anim->animator = this;
	Anim->Create(_Tex, _LT, _SliceSize, _Step, _Duration, _FrameCount);

	mapAnim.insert(make_pair(_strName, Anim));
}

CAnimation* CAnimator::FindAnimation(const wstring& _strName) {
	map<wstring, CAnimation*>::iterator iter = mapAnim.find(_strName);

	if (iter == mapAnim.end())
		return nullptr;

	return iter->second;
}

void CAnimator::Play(const wstring& _strName, bool _repeat) {
	curAnim = FindAnimation(_strName);
	repeat = _repeat;
}