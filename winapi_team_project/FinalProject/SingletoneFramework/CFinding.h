#pragma once

class CObject; // �Ҽ��� �˱� ���� ������Ʈ ���漱��

class CFinding {
private:
	static UINT nextID; // ��ü�� ����x �����Ϳ� ��� ��������

	CObject*	owner;
	Vec2		offsetPos;
	Vec2		finalPos;
	Vec2		scale;

	UINT		iID; // �浹ü ���� ID
	UINT		icol;

public:
	CFinding();
	CFinding(const CFinding& _origin);
	~CFinding();

	void SetOffsetPos(Vec2 _pos) { offsetPos = _pos; }
	void SetScale(Vec2 _scale) { scale = _scale; }

	Vec2 GetOffsetPos() { return offsetPos; }
	Vec2 GetScale() { return scale; }

	Vec2 GetFinalPos() { return finalPos; }

	CObject* GetObj() { return owner; }

	UINT GetID() { return iID; }

	void FinalUpdate();
	void Render(HDC _hDC);

	void OnFinding(CFinding* _pOther);//�浹 ���� �� ȣ��
	void OnFindingEnter(CFinding* _pOther);//�浹 ���� �� ȣ��
	void OnFindingExit(CFinding* _pOther);//�浹 Ż�� �� ȣ��

	CFinding& operator = (CFinding& _origin) = delete;

	friend class CObject;
};