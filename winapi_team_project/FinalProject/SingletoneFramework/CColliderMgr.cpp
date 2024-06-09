#include "pch.h"
#include "CColliderMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CObject.h"
#include "CCollider.h"

CColliderMgr::CColliderMgr()
	:arrCheck{}
{
}

CColliderMgr::~CColliderMgr()
{
}

void CColliderMgr::CollisionUpdateGroup(GROUP_TYPE _left, GROUP_TYPE _right) {
	CScene* curScene = CSceneMgr::Instance()->GetCurScene();

	const vector<CObject*>& vecLeft = curScene->GetGroupObject(_left);
	const vector<CObject*>& vecRight = curScene->GetGroupObject(_right);

	for (size_t i = 0; i < vecLeft.size(); ++i) {
		if (nullptr == vecLeft[i]->GetCollider())
			continue;
		for (size_t j = 0; j < vecRight.size(); ++j) {
			if (nullptr == vecRight[j]->GetCollider() || (vecLeft[i] == vecRight[j])) {
				continue;
			}

			CCollider* pLeftCol = vecLeft[i]->GetCollider();
			CCollider* pRightCol = vecRight[j]->GetCollider();

			ColliderID ID;
			ID.Left_ID = pLeftCol->GetID();
			ID.Right_ID = pRightCol->GetID();

			map<ULONGLONG, bool>::iterator iter = mapColinfo.find(ID.ID);

			//충돌 X
			if (mapColinfo.end() == iter)
			{
				mapColinfo.insert(make_pair(ID.ID, false));
				iter = mapColinfo.find(ID.ID);
			}

			if (IsCollision(pLeftCol, pRightCol)) {
				// 현재 충돌 중
				if (iter->second) {
					//이전에도 충돌
					pLeftCol->OnCollision(pRightCol);
					pRightCol->OnCollision(pLeftCol);
				}
				else {
					//이전에는 충돌 X
					pLeftCol->OnCollisionEnter(pRightCol);
					pRightCol->OnCollisionEnter(pLeftCol);
					iter->second = true;
				}
			}
			else {
				if (iter->second) {
					//이전에는 충돌 O, 현재 충돌 X
					pLeftCol->OnCollisionExit(pRightCol);
					pRightCol->OnCollisionExit(pLeftCol);
					iter->second = false;
				}
			}
		}
	}
}

bool CColliderMgr::IsCollision(CCollider* _leftCol, CCollider* _rightCol) {
	Vec2 LeftPos = _leftCol->GetFinalPos();
	Vec2 LeftScale = _leftCol->GetScale();

	Vec2 RightPos = _rightCol->GetFinalPos();
	Vec2 RightScale = _rightCol->GetScale();

	if (abs(RightPos.x - LeftPos.x) < (LeftScale.x + RightScale.x) / 2.f
		&& abs(RightPos.y - LeftPos.y) < (LeftScale.y + RightScale.y) / 2.f) {
		return true;
	}

	return false;
}

void CColliderMgr::Update() {
	// 충돌검사
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow) {
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol)
			if (arrCheck[iRow] & (1 << iCol))
				CollisionUpdateGroup((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
	}
}

void CColliderMgr::CheckGroup(GROUP_TYPE _left, GROUP_TYPE _right) {
	UINT row = (UINT)_left;
	UINT col = (UINT)_right;

	if (row > col) {
		row = (UINT)_right;
		col = (UINT)_left;
	}

	if (arrCheck[row] & (1 << col))
		arrCheck[row] &= ~(1 << col);
	else
		arrCheck[row] |= (1 << col);
}