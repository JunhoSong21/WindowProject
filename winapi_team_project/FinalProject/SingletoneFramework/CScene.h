#pragma once

class CObject; // 전방선언

class CScene {
private:
	vector<CObject*> arrObj[(UINT)GROUP_TYPE::END];
	wstring		strName;

public:
	CScene();
	virtual ~CScene();

	void SetName(const wstring& _strName) { strName = _strName; }
	const wstring& GetName() { return strName; }

	void Update();
	void FinalUpdate();
	void Render(HDC _hDC);

	virtual void Enter() = 0;
	virtual void Exit() = 0;

public:
	void AddObject(CObject* obj, GROUP_TYPE type) {
		arrObj[(UINT)type].push_back(obj);
	}

	const vector<CObject*>& GetGroupObject(GROUP_TYPE _type) {
		return arrObj[(UINT)_type];
	}
};

