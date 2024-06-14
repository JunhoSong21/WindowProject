#include "pch.h"

#include "CPlayer.h"
#include "CMissile.h"
#include "math.h"

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
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2 (30.f, 30.f));

	CTexture* tex = CResMgr::Instance()->LoadTexture(L"PlayerTex", L"Texture\\player.bmp");
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"WALK", tex, Vec2(0.f, 45.f), Vec2(45.f, 30.f), Vec2(45.f, 0.f), 0.1f, 6.f);
	GetAnimator()->Play(L"WALK", true);

	/*CAnimation* Anim = GetAnimator()->FindAnimation(L"WALK_RIGHT");
	for (UINT i = 0; i < Anim->GetMaxFrame(); ++i)
		Anim->GetFrame(0).offSet = Vec2(0.f, -20.f);*/

}

CPlayer::~CPlayer() {
}

void CPlayer::Update() {
	Vec2 ptPos = getPos();

	if (KEY_HOLD(KEY::W)) {
		ptPos.y -= 200.f * fDT;
	}

	if (KEY_HOLD(KEY::S)) {
		ptPos.y += 200.f * fDT;
	}

	if (KEY_HOLD(KEY::A)) {
		ptPos.x -= 200.f * fDT;
	}

	if (KEY_HOLD(KEY::D)) {
		ptPos.x += 200.f * fDT;
	}

	if (KEY_TAP(KEY::LBTN)) {
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
	Vec2 ptPos = getPos();
	Vec2 RenderPos = CCamera::Instance()->GetRenderPos(ptPos);
	Vec2 ptScale = getScale();

	////ÃÑ¾ËÀÇ ¹æÇâº¤ÅÍ °è»ê
	float SetaX = (MOUSE_POS.x - RenderPos.x);
	float SetaY = (MOUSE_POS.y - RenderPos.y);
	float magnitude = std::sqrt(SetaX * SetaX + SetaY * SetaY);
	SetaX = ((SetaX / magnitude));
	SetaY = ((SetaY / magnitude));

	Missile->SetDir(Vec2(SetaX, SetaY));

	CreateObject(Missile, GROUP_TYPE::PROJ_PLAYER);
}