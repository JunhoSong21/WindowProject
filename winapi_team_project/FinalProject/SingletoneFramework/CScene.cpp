#include "pch.h"
#include "CScene.h"
#include "CObject.h"

CScene::CScene()
{
}

CScene::~CScene() {
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i) {
		for (size_t j = 0; j < arrObj[i].size(); ++j) {
			delete arrObj[i][j]; // arrObj[i] > ±×·ì º¤ÅÍ¿¡ ÀÖ´Â j¹øÂ° °´Ã¼ ¼Ò¸ê
		}
	}
}

void CScene::Update() {
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i) {
		for (size_t j = 0; j < arrObj[i].size(); ++j) {
			if (!arrObj[i][j]->IsDead())
				arrObj[i][j]->Update();
		}
	}
}

void CScene::FinalUpdate() {
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i) {
		for (size_t j = 0; j < arrObj[i].size(); ++j) {
			arrObj[i][j]->FinalUpdate();
		}
	}
}

void CScene::Render(HDC _hDC) {
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i) {
		vector<CObject*>::iterator iter = arrObj[i].begin();

		for (; iter != arrObj[i].end(); ++iter) {
			if (!(*iter)->IsDead()) {
				(*iter)->Render(_hDC);
				++iter;
			}
			else {
				iter = arrObj[i].erase(iter);
			}
		}
	}
}

void CScene::DeleteGroup(GROUP_TYPE _Target) {
	Safe_Delete_Vec(arrObj[(UINT)_Target]);
}

void CScene::DeleteAll() {
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i) {
		DeleteGroup((GROUP_TYPE)i);
	}
}