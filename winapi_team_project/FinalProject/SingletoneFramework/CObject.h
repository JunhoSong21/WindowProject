#pragma once

#include "CCamera.h"

class CCollider;
class CAnimator;

class CObject {
private:
	wstring		strName;

	Vec2		ptPos;
	Vec2		ptScale;

	// 기능이 있을수도 있고 없을수도 있으므로 Component로 제작
	CCollider*	collider;
	CAnimator*	animator;

	bool		alive;

public:
	CObject();
	CObject(const CObject& _origin);
	virtual ~CObject();

	void setPos(Vec2 _ptPos) { ptPos = _ptPos; }
	void setScale(Vec2 _ptScale) { ptScale = _ptScale; }

	Vec2 getPos() { return ptPos; }
	Vec2 getScale() { return ptScale; }

	void SetName(const wstring& _strName) { strName = _strName; }
	const wstring& GetName() { return strName; }

	CCollider* GetCollider() { return collider; }
	CAnimator* GetAnimator() { return animator; }

	bool IsDead() { return !alive; }

	void CreateCollider();
	void CreateAnimator();

	virtual void OnCollision(CCollider* _pOther) {}
	virtual void OnCollisionEnter(CCollider* _pOther) {}
	virtual void OnCollisionExit(CCollider* _pOther) {}

private:
	void SetDead() { alive = false; }

public:
	virtual void Update() = 0;
	virtual void Render(HDC _hDC);
	virtual void FinalUpdate() final;

	virtual CObject* Clone() = 0;

	void CommponentRender(HDC _hdc);

	friend class CEventMgr;
};