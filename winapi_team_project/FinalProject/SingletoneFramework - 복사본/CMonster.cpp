#include "pch.h"
#include "CMonster.h"
#include "math.h"
#include "CResMgr.h"
#include "CTimeMgr.h"
#include "CCollider.h"
#include "CFinding.h"
#include "CMissile.h"
#include "CScene.h"
#include "CTexture.h"
#include "CAnimator.h"
#include "CAnimation.h"

CMonster::CMonster()
	: Speed(100.f)
	, CenterPos(Vec2(0.f, 0.f))
	, MaxDis(50.f)
	, Dir(1)
	, iHP(1)
	, Attack(0)
	, DirVec(Vec2(1.f, 1.f))
	, selection(1)
{
	CreateCollider();
	CreateFinding();
	GetCollider()->SetScale(Vec2(42.f, 42.f));
	GetFinding()->SetScale(Vec2(400.f, 400.f));

	CTexture* tex = CResMgr::Instance()->LoadTexture(L"EnemyTex", L"Texture\\enemy.bmp");
	CreateAnimator();

	GetAnimator()->CreateAnimation(L"WalkKnife", tex, Vec2(0.f, 0.f), Vec2(45.f, 30.f), Vec2(45.f, 0.f), 0.1f, 8.f);

	GetAnimator()->Play(L"WalkKnife", true);
}

CMonster::~CMonster()
{
}

void CMonster::Update()	{
	Vec2 curPos = getPos();
	// 진행 방향으로 시간당 Speed 만큼 이동
	curPos.x += fDT * Speed * Dir;

	// 배회 거리 기준점을 넘어섰는지 확인
	float dist = abs(CenterPos.x - curPos.x) - MaxDis;

	if (0.f < dist) {
		// 방향 변경
		Dir *= -1;
		curPos.x += dist * Dir;
	}

	if (Attack > 0)
		Attack -= 10.f * fDT;
	else
		Attack = 0;

	GetAnimator()->Update();
	setPos(curPos);
}

void CMonster::OnCollisionEnter(CCollider* _pOther) {
	CObject* OtherObj = _pOther->GetObj();

	if (OtherObj->GetName() == L"Missile_Player") {
		iHP -= 1;

		if (iHP <= 0)
			DeleteObject(this);
	}
}

void CMonster::OnFinding(CFinding* _pOther) {
	CObject* OtherObj = _pOther->GetObj();
	if (OtherObj->GetName() == L"PLAYER") {
		if (Attack == 0) {
			Vec2 ptPos = getPos();
			Vec2 ptScale = getScale();
			Vec2 RenderPos = CCamera::Instance()->GetRenderPos(ptPos);
			Vec2 playerPos = OtherObj->getPos();
			float SetaX = (playerPos.x - ptPos.x);
			float SetaY = (playerPos.y - ptPos.y);
			float magnitude = std::sqrt(SetaX * SetaX + SetaY * SetaY);
			SetaX = ((SetaX / magnitude));
			SetaY = ((SetaY / magnitude));

			Vec2 NowDir = GetDirV();
			float SetaX2 = (NowDir.x - ptPos.x);
			float SetaY2 = (NowDir.y - ptPos.y);
			float magnitude2 = std::sqrt(SetaX2 * SetaX2 + SetaY2 * SetaY2);
			SetaX2 = ((SetaX2 / magnitude2));
			SetaY2 = ((SetaY2 / magnitude2));

			if (abs(SetaX - SetaX2) < 0.1f && abs(SetaY - SetaY2) < 0.1f) {
				Vec2 MissilePos = getPos();

				CMissile* Missile = new CMissile;
				Missile->SetName(L"Missile_Player");
				Missile->setPos(MissilePos);
				Missile->setScale(Vec2(25.f, 25.f));
				Missile->SetItem(0);
				Missile->SetDir(Vec2(SetaX2, SetaY2));
				switch (CObject::GetSel())
				{
				case 1:
					Missile->Setlen(200.f);
					Missile->SetSpd(1000.f);
					Attack = 3.f;
					break;
				case 2:
					Missile->Setlen(500.f);
					Missile->SetSpd(600.f);
					Attack = 2.f;
					break;
				case 3:
					Missile->setScale(Vec2(100.f, 100.f));
					Missile->Setlen(10.f);
					Missile->SetSpd(1000.f);
					Attack = 5.f;
					break;
				}
				CreateObject(Missile, GROUP_TYPE::PROJ_MONSTER);
			}
			if (SetaX > SetaX2)
				DirVec.x += 500.f * fDT;
			else
				DirVec.x -= 500.f * fDT;
			if (SetaY > SetaY2)
				DirVec.y += 500.f * fDT;
			else
				DirVec.y -= 500.f * fDT;
		}
	}
}