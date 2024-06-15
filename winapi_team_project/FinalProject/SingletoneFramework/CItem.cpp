#include "pch.h"

#include "CItem.h"

#include "CTimeMgr.h"
#include "CCollider.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CCollider.h"
#include "CKeyMgr.h"

CItem::CItem()
	: tex(nullptr)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(50.f, 50.f));

	tex = CResMgr::Instance()->LoadTexture(L"ITEM", L"Texture\\bung.bmp");
}

CItem::~CItem()
{
}

void CItem::Render(HDC _dc) {
	int width = (int)tex->Width();
	int height = (int)tex->Height();

	Vec2 ptPos = getPos();
	Vec2 RenderPos = CCamera::Instance()->GetRenderPos(ptPos);
	TransparentBlt(_dc
		, int(RenderPos.x - (float)(width / 2))
		, int(RenderPos.y - (float)(height / 2))
		, width
		, height
		, tex->GetDC()
		, 0, 0, width, height
		, RGB(255, 0, 255));

	CommponentRender(_dc);
}

void CItem::Update() {
	Vec2 curPos = getPos();

	setPos(curPos);
}

void CItem::OnCollision(CCollider* _pOther) {

	CObject* OtherObj = _pOther->GetObj();
	Vec2 ptPos = getPos();
	if (OtherObj->GetName() == L"PLAYER") {
		if (KEY_HOLD(KEY::E)) {
			OtherObj->SetSel(CObject::GetSel());
		}
	}
}