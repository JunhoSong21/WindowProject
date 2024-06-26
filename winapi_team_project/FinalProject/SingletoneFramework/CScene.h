#pragma once

class CObject; // 전방선언

class CScene {
private:
	vector<CObject*> arrObj[(UINT)GROUP_TYPE::END];
	wstring		strName;
	Vec2		ptPos;
	int			Point;
	bool		InvPoint;
	int			RR, GG, BB;
	float		colortime;

public:
	CScene();
	virtual ~CScene();

	void SetName(const wstring& _strName) { strName = _strName; }
	const wstring& GetName() { return strName; }

	virtual void Update();
	virtual void FinalUpdate();
	virtual void Render(HDC _hDC);

	virtual void Enter() = 0;
	virtual void Exit() = 0;

	void setPos(Vec2 _ptPos) { ptPos = _ptPos; }
	Vec2 getPos() { return ptPos; }

	void setPoint(int _po) { Point = _po; }
	int getPoint() { return Point; }

	void ChangePoint(bool Inv) { InvPoint = Inv; }

public:
	void AddObject(CObject* obj, GROUP_TYPE type) {
		arrObj[(UINT)type].push_back(obj);
	}

	const vector<CObject*>& GetGroupObject(GROUP_TYPE _type) {
		return arrObj[(UINT)_type];
	}
	void DeleteGroup(GROUP_TYPE _Target);
	void DeleteAll();
};

