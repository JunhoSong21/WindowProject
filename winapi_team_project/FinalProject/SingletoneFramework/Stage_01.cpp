#include "pch.h"
#include "Stage_01.h"

#include "CKeyMgr.h"
#include "CResMgr.h"
#include "CPathMgr.h"
#include "CSceneMgr.h"
#include "CTimeMgr.h"

#include "CScene.h"
#include "CTexture.h"
#include "CCollider.h"

Stage_01::Stage_01()
	: Stage_01_tex(nullptr)
{
	Stage_01_tex = CResMgr::Instance()->LoadTexture(L"Map_Stage_01", L"Texture\\Stage_01.bmp");

}

Stage_01::~Stage_01()
{
}

void Stage_01::Update() {

}

void Stage_01::Render(HDC _dc) {
	int width = (int)Stage_01_tex->Width();
	int height = (int)Stage_01_tex->Height();

	Vec2 ptPos = getPos();

	ptPos.x - (float)(width / 2);
	ptPos.y - (float)(height / 2);

	TransparentBlt(_dc
		, int(ptPos.x - (float)(width / 2))
		, int(ptPos.y - (float)(height / 2))
		, width, height
		, Stage_01_tex->GetDC()
		, 0, 0, width, height
		, RGB(255, 0, 255));

	CommponentRender(_dc);
}