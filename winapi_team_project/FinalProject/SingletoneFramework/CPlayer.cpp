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
#include "CAnimator.h"
#include "CAnimation.h"

CPlayer::CPlayer()
{
	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 10.f));
	GetCollider()->SetScale(Vec2(80.f, 90.f));

	CTexture* tex = CResMgr::Instance()->LoadTexture(L"PlayerTex", L"Texture\\player.bmp");
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"WALK_RIGHT", tex, Vec2(0.f, 0.f), Vec2(45.f, 50.f), Vec2(45.f, 0.f), 0.1f, 6.f);
	GetAnimator()->Play(L"WALK_RIGHT", true);

	CAnimation* Anim = GetAnimator()->FindAnimation(L"WALK_RIGHT");
	for (int i = 0; i < Anim->GetMaxFrame(); ++i)
		Anim->GetFrame(0).offSet = Vec2(0.f, -20.f);
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

	GetAnimator()->Update();
}

void CPlayer::Render(HDC _dc) {

	CommponentRender(_dc);
}

void CPlayer::CreateMissile() {
	Vec2 MissilePos = getPos();
	MissilePos.y -= getScale().y / 2.f;

	CMissile* Missile = new CMissile;
	Missile->SetName(L"Missile_Player");
	Missile->setPos(MissilePos);
	Missile->setScale(Vec2(25.f, 25.f));
	Missile->SetDir(Vec2(0.f, 7.f));

	CreateObject(Missile, GROUP_TYPE::PROJ_PLAYER);
}