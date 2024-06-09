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

	ptPos.x += 600.f * Dir.x * fDT;
	ptPos.y -= 600.f * Dir.y * fDT;

	setPos(ptPos);
}

void CMissile::Render(HDC _hDC) {
	Vec2 ptPos = getPos();
	Vec2 ptScale = getScale();

	Ellipse(_hDC, (int)(ptPos.x - ptScale.x / 2.f),
		(int)(ptPos.y - ptScale.y / 2.f),
		(int)(ptPos.x + ptScale.x / 2.f),
		(int)(ptPos.y + ptScale.y / 2.f));

	CommponentRender(_hDC);
}

void CMissile::OnCollisionEnter(CCollider* _pOther) {
	CObject* OtherObj = _pOther->GetObj();

	if (OtherObj->GetName() == L"Monster") {
		DeleteObject(this);
	}
}
