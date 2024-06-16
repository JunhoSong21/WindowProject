#include "pch.h"
#include "CCollider.h"

#include "CObject.h"
#include "CCore.h"
#include "SelectGDI.h"
#include "CCamera.h"

UINT CCollider::nextID = 0;

CCollider::CCollider()
	:owner(nullptr)
	, iID(nextID++)
	, icol(0)
{
}

CCollider::CCollider(const CCollider& _origin)
	: owner(nullptr)
	, offsetPos(_origin.offsetPos)
	, finalPos(_origin.finalPos)
	, scale(_origin.scale)
	, iID(nextID++)
	, icol(0)
{
}

CCollider::~CCollider()
{
}

void CCollider::FinalUpdate() {
	Vec2 objectPos = owner->getPos();
	finalPos = objectPos + offsetPos;

	assert(0 <= icol);
}

void CCollider::Render(HDC _hDC) {
	PEN_TYPE ePen = PEN_TYPE::GREEN;

	if (icol)
		ePen = PEN_TYPE::RED;

	SelectGDI p(_hDC, ePen);
	SelectGDI b(_hDC, BRUSH_TYPE::HOLLOW);

	Vec2 RenderPos = CCamera::Instance()->GetRenderPos(finalPos);
	
	Rectangle(_hDC
		, (int)(RenderPos.x - scale.x / 2.f)
		, (int)(RenderPos.y - scale.y / 2.f)
		, (int)(RenderPos.x + scale.x / 2.f)
		, (int)(RenderPos.y + scale.y / 2.f));
}

void CCollider::OnCollision(CCollider* _pOther) {
	owner->OnCollision(_pOther);
}

void CCollider::OnCollisionEnter(CCollider* _pOther)
{
	++icol;
	owner->OnCollisionEnter(_pOther);
}

void CCollider::OnCollisionExit(CCollider* _pOther)
{
	--icol;
	owner->OnCollisionExit(_pOther);
}
