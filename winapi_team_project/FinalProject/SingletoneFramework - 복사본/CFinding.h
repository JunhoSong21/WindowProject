#pragma once

class CObject; // 소속을 알기 위한 오브젝트 전방선언

class CFinding {
private:
	static UINT nextID; // 객체에 포함x 데이터에 계속 남아있음

	CObject*	owner;
	Vec2		offsetPos;
	Vec2		finalPos;
	Vec2		scale;

	UINT		iID; // 충돌체 고유 ID
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

	void OnFinding(CFinding* _pOther);//충돌 중일 때 호출
	void OnFindingEnter(CFinding* _pOther);//충돌 진입 시 호출
	void OnFindingExit(CFinding* _pOther);//충돌 탈출 시 호출

	CFinding& operator = (CFinding& _origin) = delete;

	friend class CObject;
};