#include "pch.h"

#include "CPlayer.h"
#include "CMissile.h"

#include "CKeyMgr.h"
#include "CResMgr.h"
#include "CPathMgr.h"
#include "CSceneMgr.h"
#include "CTimeMgr.h"

#include "CScene.h"
#include "CTexture.h"
#include "CCollider.h"

CPlayer::CPlayer()
	: tex(nullptr)
{
	tex = CResMgr::Instance()->LoadTexture(L"PlayerTex", L"Texture\\PlayerSprite.bmp");
	CreateCollider();

	GetCollider()->SetOffsetPos(Vec2(0.f, 10.f));
	GetCollider()->SetScale(Vec2(80.f, 90.f));
}

CPlayer::~CPlayer() {
}

void CPlayer::Update() {
	Vec2 ptPos = getPos();

	if (KEY_HOLD(KEY::W)) {
		ptPos.y -= 200.f * DT;
	}

	if (KEY_HOLD(KEY::S)) {
		ptPos.y += 200.f * DT;
	}

	if (KEY_HOLD(KEY::A)) {
		ptPos.x -= 200.f * DT;
	}

	if (KEY_HOLD(KEY::D)) {
		ptPos.x += 200.f * DT;
	}

	if (KEY_TAP(KEY::SPACE)) {
		CreateMissile();
	}

	setPos(ptPos);
}

void CPlayer::Render(HDC _dc) {
	Vec2 ptPos = getPos();
	int width = (int)tex->Width();
	int height = (int)tex->Height();

	TransparentBlt(_dc
		, int(ptPos.x - (float)(width / 2))
		, int(ptPos.y - (float)(height / 2))
		, width, height
		, tex->GetDC()
		, 0, 0, 45, 50
		, RGB(255, 0, 255));

	CommponentRender(_dc);
}

void CPlayer::CreateMissile() {
	Vec2 MissilePos = getPos();
	MissilePos.y -= getScale().y / 2.f;

	CMissile* Missile = new CMissile;
	Missile->setPos(MissilePos);
	Missile->setScale(Vec2(25.f, 25.f));
	Missile->SetDir(Vec2(0.f, 7.f));

	// ÇöÀç¾À ¾ò¾î¿È
	CScene* curScenes = CSceneMgr::Instance()->GetCurScene();
	curScenes->AddObject(Missile, GROUP_TYPE::DEFAULT);
}