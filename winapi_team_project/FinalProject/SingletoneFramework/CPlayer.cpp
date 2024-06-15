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
#include "CScore.h"

CPlayer::CPlayer()
{
	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2 (60.f, 60.f));

	CTexture* tex = CResMgr::Instance()->LoadTexture(L"PlayerTex", L"Texture\\player.bmp");
	CreateAnimator();

	GetAnimator()->CreateAnimation(L"AttackKnife", tex, Vec2(0.f, 0.f), Vec2(45.f, 50.f), Vec2(45.f, 0.f), 0.1f, 6.f);
	GetAnimator()->CreateAnimation(L"AttackHandGun", tex, Vec2(0.f, 250.f), Vec2(45.f, 30.f), Vec2(45.f, 0.f), 0.1f, 2.f);
	GetAnimator()->CreateAnimation(L"AttackShotGun", tex, Vec2(0.f, 160.f), Vec2(45.f, 30.f), Vec2(45.f, 0.f), 0.1f, 3.f);
	GetAnimator()->CreateAnimation(L"WALKKnife", tex, Vec2(0.f, 45.f), Vec2(45.f, 30.f), Vec2(45.f, 0.f), 0.1f, 8.f);
	GetAnimator()->CreateAnimation(L"WalkShotGun", tex, Vec2(0.f, 190.f), Vec2(45.f, 30.f), Vec2(45.f, 0.f), 0.1f, 8.f);
	GetAnimator()->CreateAnimation(L"WalkHandGun", tex, Vec2(0.f, 220.f), Vec2(45.f, 30.f), Vec2(45.f, 0.f), 0.1f, 7.f);
	GetAnimator()->CreateAnimation(L"Reload", tex, Vec2(0.f, 80.f), Vec2(45.f, 30.f), Vec2(45.f, 0.f), 0.1f, 6.f);
	GetAnimator()->CreateAnimation(L"Throaw", tex, Vec2(0.f, 110.f), Vec2(45.f, 50.f), Vec2(45.f, 0.f), 0.1f, 4.f);

	CObject::SetSel(1);
	Attack = 0;
	AniOn = 0;
	/*CAnimation* Anim = GetAnimator()->FindAnimation(L"WALK_RIGHT");
	for (UINT i = 0; i < Anim->GetMaxFrame(); ++i)
		Anim->GetFrame(0).offSet = Vec2(0.f, -20.f);*/

}

CPlayer::~CPlayer() {
}

void CPlayer::Update() {
	Vec2 ptPos = getPos();

	if (KEY_HOLD(KEY::W)) {
		ptPos.y -= 400.f * fDT;
	}

	if (KEY_HOLD(KEY::S)) {
		ptPos.y += 400.f * fDT;
	}

	if (KEY_HOLD(KEY::A)) {
		ptPos.x -= 400.f * fDT;
	}

	if (KEY_HOLD(KEY::D)) {
		ptPos.x += 400.f * fDT;
	}

	if (KEY_TAP(KEY::LBTN)) {
		CreateMissile();
	}

	if (KEY_TAP(KEY::RBTN)) {
		ThrowItem();
	}

	if (KEY_TAP(KEY::Key_1)) {
		CObject::SetSel(1);
	}
	if (KEY_TAP(KEY::Key_2)) {
		CObject::SetSel(2);
	}
	if (KEY_TAP(KEY::Key_3)) {
		CObject::SetSel(3);
	}

	if (KEY_HOLD(KEY::W) || KEY_HOLD(KEY::A) || KEY_HOLD(KEY::S) || KEY_HOLD(KEY::D) || KEY_HOLD(KEY::LBTN) || KEY_HOLD(KEY::RBTN) || Attack != 0)
		AniOn = 1;
	else
		AniOn = 0;

	if (Attack == 0) {
		switch (CObject::GetSel())
		{
		case 1:
			GetAnimator()->Play(L"WalkShotGun", true);
			break;
		case 2:
			GetAnimator()->Play(L"WalkHandGun", true);
			break;
		case 3:
			GetAnimator()->Play(L"WALKKnife", true);
			break;
		}
	}
	if (Attack > 0)
		Attack -= 10.f * fDT;
	else
		Attack = 0;
	setPos(ptPos);
	if (AniOn)
		GetAnimator()->Update();
}

void CPlayer::Render(HDC _dc) {
	CommponentRender(_dc);
}

void CPlayer::OnCollision(CCollider* _pOther) {

	CObject* OtherObj = _pOther->GetObj();
	Vec2 ptPos = getPos();
	if (OtherObj->GetName() == L"FURNITURE") {
		if (KEY_HOLD(KEY::W)) {
			ptPos.y += 405.f * fDT;
		}

		if (KEY_HOLD(KEY::S)) {
			ptPos.y -= 405.f * fDT;
		}

		if (KEY_HOLD(KEY::A)) {
			ptPos.x += 405.f * fDT;
		}

		if (KEY_HOLD(KEY::D)) {
			ptPos.x -= 405.f * fDT;
		}
	}
	setPos(ptPos);
}

void CPlayer::CreateMissile() {
	Vec2 MissilePos = getPos();

	CMissile* Missile = new CMissile;
	Missile->SetName(L"Missile_Player");
	Missile->setPos(MissilePos);
	Missile->setScale(Vec2(25.f, 25.f));
	Missile->SetItem(0);
	Vec2 ptPos = getPos();
	Vec2 RenderPos = CCamera::Instance()->GetRenderPos(ptPos);
	Vec2 ptScale = getScale();

	////ÃÑ¾ËÀÇ ¹æÇâº¤ÅÍ °è»ê
	float SetaX = (MOUSE_POS.x - RenderPos.x + ptScale.x);
	float SetaY = (MOUSE_POS.y - RenderPos.y + ptScale.y);
	float magnitude = std::sqrt(SetaX * SetaX + SetaY * SetaY);
	SetaX = ((SetaX / magnitude));
	SetaY = ((SetaY / magnitude));
	Missile->SetDir(Vec2(SetaX, SetaY));

	if (Attack == 0) {
		switch (CObject::GetSel())
		{
		case 1:
			Missile->Setlen(200.f);
			Missile->SetSpd(1000.f);
			GetAnimator()->Play(L"AttackShotGun", true);
			Attack = 3.f;
			break;
		case 2:
			Missile->Setlen(500.f);
			Missile->SetSpd(600.f);
			GetAnimator()->Play(L"AttackHandGun", true);
			Attack = 2.f;
			break;
		case 3:
			Missile->setScale(Vec2(100.f, 100.f));
			Missile->Setlen(10.f);
			Missile->SetSpd(1000.f);
			GetAnimator()->Play(L"AttackKnife", true);
			Attack = 5.f;
			break;
		}
	}

	CreateObject(Missile, GROUP_TYPE::PROJ_PLAYER);
}

void CPlayer::ThrowItem() {
	Vec2 MissilePos = getPos();

	CMissile* Missile = new CMissile;
	Missile->SetName(L"Missile_Player");
	Missile->setPos(MissilePos);
	Missile->setScale(Vec2(25.f, 25.f));
	Missile->SetItem(1);
	Vec2 ptPos = getPos();
	Vec2 RenderPos = CCamera::Instance()->GetRenderPos(ptPos);
	Vec2 ptScale = getScale();

	////ÃÑ¾ËÀÇ ¹æÇâº¤ÅÍ °è»ê
	float SetaX = (MOUSE_POS.x - RenderPos.x + ptScale.x);
	float SetaY = (MOUSE_POS.y - RenderPos.y + ptScale.y);
	float magnitude = std::sqrt(SetaX * SetaX + SetaY * SetaY);
	SetaX = ((SetaX / magnitude));
	SetaY = ((SetaY / magnitude));
	Missile->SetDir(Vec2(SetaX, SetaY));


	Missile->Setlen(500.f);
	Missile->SetSpd(600.f);
	GetAnimator()->Play(L"Throaw", true);
	Attack = 4.f;

	CreateObject(Missile, GROUP_TYPE::PROJ_PLAYER);
}