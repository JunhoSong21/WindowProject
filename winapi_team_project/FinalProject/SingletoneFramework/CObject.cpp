#include "pch.h"
#include "CObject.h"
#include "CKeyMgr.h"
#include "CCollider.h"
#include "CAnimator.h"

CObject::CObject()
	: ptPos{}
	, ptScale{}
	, collider(nullptr)
	, animator(nullptr)
	, alive(true)
{
}

CObject::CObject(const CObject& _origin)
	: strName(_origin.strName)
	, ptPos(_origin.ptPos)
	, ptScale(_origin.ptScale)
	, collider(nullptr)
	, animator(nullptr)
	, alive(true)
{
	if (_origin.collider) {
		collider = new CCollider(*_origin.collider);
		collider->owner = this;
	}

	if (_origin.animator) {
		animator = new CAnimator(*_origin.animator);
		animator->owner = this;
	}
}

CObject::~CObject() {
	if (nullptr != collider)
		delete collider;

	if (nullptr != animator) {
		delete animator;
	}
}

void CObject::Render(HDC _hDC) {
	Vec2 RenderPos = CCamera::Instance()->GetRenderPos(ptPos);

	Rectangle(_hDC
		, (int)(RenderPos.x - ptScale.x / 2.f)
		, (int)(RenderPos.y - ptScale.y / 2.f)
		, (int)(RenderPos.x + ptScale.x / 2.f)
		, (int)(RenderPos.y + ptScale.y / 2.f));
	CommponentRender(_hDC);
}

void CObject::FinalUpdate() {
	if (collider)
		collider->FinalUpdate();
}

void CObject::CommponentRender(HDC _hDC) {
	if (nullptr != collider)
		collider->Render(_hDC);

	if (nullptr != animator) {
		animator->Render(_hDC);
	}
}

void CObject::CreateCollider() {
	collider = new CCollider;
	collider->owner = this;
}

void CObject::CreateAnimator() {
	animator = new CAnimator;
	animator->owner = this;
}