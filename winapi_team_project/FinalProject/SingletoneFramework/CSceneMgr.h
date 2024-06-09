#pragma once

class CScene;

class CSceneMgr {
	SINGLE(CSceneMgr);
private:
	CScene* arrScene[(UINT)SCENE_TYPE::END];
	CScene* curScene;

	void ChangeScene(SCENE_TYPE _Next);

public:
	void Init();
	void Update();
	void Render(HDC _hDC);

	CScene* GetCurScene() { return curScene; }

	friend class CEventMgr;
};