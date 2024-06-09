#pragma once

class CObject; // �Ҽ��� �˱� ���� ������Ʈ ���漱��

class CCollider {
private:
	static UINT nextID; // ��ü�� ����x �����Ϳ� ��� ��������

	CObject* owner; 
	Vec2 offsetPos;
	Vec2 finalPos;
	Vec2 scale;	

	UINT iID; // �浹ü ���� ID
	UINT icol;

public:
	CCollider();
	CCollider(const CCollider& _origin);
	~CCollider();

	void SetOffsetPos(Vec2 _pos) { offsetPos = _pos; }
	void SetScale(Vec2 _scale) { scale = _scale; }

	Vec2 GetOffsetPos() { return offsetPos; }
	Vec2 GetScale() { return scale; }

	Vec2 GetFinalPos() { return finalPos; }

	CObject* GetObj() { return owner; }

	UINT GetID() { return iID; }

	void FinalUpdate();
	void Render(HDC _hDC);

	void OnCollision(CCollider* _pOther);//�浹 ���� �� ȣ��
	void OnCollisionEnter(CCollider* _pOther);//�浹 ���� �� ȣ��
	void OnCollisionExit(CCollider* _pOther);//�浹 Ż�� �� ȣ��

	CCollider& operator = (CCollider& _origin) = delete;

	friend class CObject;
};