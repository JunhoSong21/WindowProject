#pragma once

class CFinding;

union FindingID {
	struct {
		UINT Left_ID;
		UINT Right_ID;
	};
	ULONGLONG ID;
};

class CFindingMgr {
	SINGLE(CFindingMgr);
private:

	map<ULONGLONG, bool> mapColinfo; //충돌체간의 이전 프레임 충돌 정보
	UINT arrCheck[(UINT)GROUP_TYPE::END];	//그룹간의 충돌 체크

	void FindingUpdateGroup(GROUP_TYPE _left, GROUP_TYPE _right);
	bool IsFind(CFinding* _leftCol, CFinding* _rightCol);

public:
	void Update();
	void CheckGroup(GROUP_TYPE _left, GROUP_TYPE _right);
	void Reset() { memset(arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END); }
};

