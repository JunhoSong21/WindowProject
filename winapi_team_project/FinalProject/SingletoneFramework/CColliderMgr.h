#pragma once

class CCollider;

union ColliderID {
	struct {
		UINT Left_ID;
		UINT Right_ID;
	};
	ULONGLONG ID;
};

class CColliderMgr {
	SINGLE(CColliderMgr);
private:
	map<ULONGLONG, bool> mapColinfo; //�浹ü���� ���� ������ �浹 ����
	UINT arrCheck[(UINT)GROUP_TYPE::END];	//�׷찣�� �浹 üũ
		
	void CollisionUpdateGroup(GROUP_TYPE _left, GROUP_TYPE _right);
	bool IsCollision(CCollider* _leftCol, CCollider* _rightCol);

public:
	void Update();
	void CheckGroup(GROUP_TYPE _left, GROUP_TYPE _right);
	void Reset() { memset(arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END); }
};

