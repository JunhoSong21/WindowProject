#pragma once

class CCollider;

class CObject {
private:
	Vec2		ptPos;
	Vec2		ptScale;
	CCollider*	collider;

public:
	CObject();
	virtual ~CObject();

	void setPos(Vec2 _ptPos) { ptPos = _ptPos; }
	void setScale(Vec2 _ptScale) { ptScale = _ptScale; }

	Vec2 getPos() { return ptPos; }
	Vec2 getScale() { return ptScale; }

	CCollider* GetCollider() { return collider; }
	void CreateCollider();

public:
	virtual void Update() = 0;
	virtual void Render(HDC _hDC);
	virtual void FinalUpdate() final;

	void CommponentRender(HDC _hdc);
};