#include "pch.h"
#include <bitset>
#include "CFindingMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CObject.h"
#include "CCore.h"
#include "CFinding.h"

CFindingMgr::CFindingMgr()
	:arrCheck{}
{
}

CFindingMgr::~CFindingMgr()
{
}

void CFindingMgr::FindingUpdateGroup(GROUP_TYPE _left, GROUP_TYPE _right) {
	CScene* curScene = CSceneMgr::Instance()->GetCurScene();

	const vector<CObject*>& vecLeft = curScene->GetGroupObject(_left);
	const vector<CObject*>& vecRight = curScene->GetGroupObject(_right);

	for (size_t i = 0; i < vecLeft.size(); ++i) {
		if (nullptr == vecLeft[i]->GetFinding())
			continue;
		for (size_t j = 0; j < vecRight.size(); ++j) {
			if (nullptr == vecRight[j]->GetFinding() || (vecLeft[i] == vecRight[j])) {
				continue;
			}

			CFinding* pLeftCol = vecLeft[i]->GetFinding();
			CFinding* pRightCol = vecRight[j]->GetFinding();

			// 두 충돌체 조합 ID 생성
			FindingID ID;
			ID.Left_ID = pLeftCol->GetID();
			ID.Right_ID = pRightCol->GetID();

			map<ULONGLONG, bool>::iterator iter = mapColinfo.find(ID.ID);

			//충돌 X
			if (mapColinfo.end() == iter)
			{
				mapColinfo.insert(make_pair(ID.ID, false));
				iter = mapColinfo.find(ID.ID);
			}

			if (IsFind(pLeftCol, pRightCol)) {
				// 현재 충돌 중
				if (iter->second) {
					//이전에도 충돌

					if (vecLeft[i]->IsDead() || vecRight[j]->IsDead()) {
						pLeftCol->OnFindingExit(pRightCol);
						pRightCol->OnFindingExit(pLeftCol);
						iter->second = false;
					}
					else {
						pLeftCol->OnFinding(pRightCol);
						pRightCol->OnFinding(pLeftCol);
					}
				}
				else {
					//이전에는 충돌 X
					if (!vecLeft[i]->IsDead() && !vecRight[j]->IsDead()) {
						pLeftCol->OnFindingEnter(pRightCol);
						pRightCol->OnFindingEnter(pLeftCol);
						iter->second = true;
					}
				}
			}
			else {
				if (iter->second) {
					//이전에는 충돌 O, 현재 충돌 X
					pLeftCol->OnFindingExit(pRightCol);
					pRightCol->OnFindingExit(pLeftCol);
					iter->second = false;
				}
			}
		}
	}
}

bool CFindingMgr::IsFind(CFinding* _leftCol, CFinding* _rightCol) {
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

void CFindingMgr::Update() {
	// 충돌검사
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow) {
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol) {
			if (arrCheck[iRow] & (1 << iCol))
				FindingUpdateGroup((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
		}
	}
}

void CFindingMgr::CheckGroup(GROUP_TYPE _left, GROUP_TYPE _right) {
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