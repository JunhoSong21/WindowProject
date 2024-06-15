#include "pch.h"
#include "CMissile.h"

#include "CCollider.h"
#include "CTimeMgr.h"
#include "CItem.h"
#include "func.h"
#include "CScore.h"

CMissile::CMissile()
	: Theta(PI / 4.f)
	, Dir(Vec2(1.f, 1.f))
	, Speed(600.f)
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
		ptPos.x += Speed * Dir.x * fDT;
		ptPos.y += Speed * Dir.y * fDT;
		Distance += Speed * fDT;
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
		if (isItem) {
			CreateItem();
		}
	}
}

void CMissile::CreateItem() {
	Vec2 ItemPos = getPos();

	CItem* Item = new CItem;
	Item->SetName(L"ITEM");
	Item->setPos(ItemPos);
	Item->setScale(Vec2(25.f, 25.f));

	CreateObject(Item, GROUP_TYPE::ITEM);
}