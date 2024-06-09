#include "pch.h"
#include "CObject.h"
#include "CKeyMgr.h"
#include "CCollider.h"

CObject::CObject()
	: ptPos{}
	, ptScale{}
	, collider(nullptr)
{
}

CObject::~CObject() {
	if (nullptr != collider)
		delete collider;
}

void CObject::Render(HDC _hDC) {
	Rectangle(_hDC, (int)(ptPos.x - ptScale.x / 2.f), (int)(ptPos.y - ptScale.y / 2.f),
		(int)(ptPos.x + ptScale.x / 2.f), (int)(ptPos.y + ptScale.y / 2.f));
	CommponentRender(_hDC);
}

void CObject::FinalUpdate() {
	if (collider)
		collider->FinalUpdate();
}

void CObject::CommponentRender(HDC _hDC) {
	if (nullptr != collider)
		collider->Render(_hDC);
}

void CObject::CreateCollider() {
	collider = new CCollider;
	collider->owner = this;
}