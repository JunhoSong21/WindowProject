#include "pch.h"
#include "CMissile.h"

#include "CCollider.h"
#include "CTimeMgr.h"

CMissile::CMissile()
	: Theta(PI / 4.f)
	, Dir(Vec2(1.f, 1.f))
{
	Dir.Normalize();
	CreateCollider();
	GetCollider()->SetScale(Vec2(15.f, 15.f));
}

CMissile::~CMissile()
{
}

void CMissile::Update() {
	Vec2 ptPos = getPos();
	GetCollider()->SetScale(getScale());
	if (Distance < length) {
		ptPos.x += 600.f * Dir.x * fDT;
		ptPos.y += 600.f * Dir.y * fDT;
		Distance += 500.f * fDT;
	}
	else {
		DeleteObject(this);
	}
	setPos(ptPos);
}

void CMissile::Render(HDC _hDC) {
	Vec2 ptPos = getPos();
	Vec2 ptScale = getScale();
	Vec2 RenderPos = CCamera::Instance()->GetRenderPos(ptPos);

	Ellipse(_hDC, 
		(int)(RenderPos.x - ptScale.x / 2.f),
		(int)(RenderPos.y - ptScale.y / 2.f),
		(int)(RenderPos.x + ptScale.x / 2.f),
		(int)(RenderPos.y + ptScale.y / 2.f));

	CommponentRender(_hDC);
}

void CMissile::OnCollisionEnter(CCollider* _pOther) {
	CObject* OtherObj = _pOther->GetObj();

	if (OtherObj->GetName() == L"Monster") {
		DeleteObject(this);
	}
}