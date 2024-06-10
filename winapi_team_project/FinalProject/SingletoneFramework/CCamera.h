#pragma once

class CObject;

class CCamera
{
	SINGLE(CCamera);
private:
	Vec2 LookAt;		//카메라가 보는 위치
	Vec2 CurLookAt;		//이전 위치와 보정해주는 카메라 위치
	Vec2 PrevLookAt;	//이전 프레임에서 카메라가 보는 위치
	
	CObject* TargetObh;	//카메라의 타켓 오브젝트
	Vec2 Diff;			//해상도 중심위치와 카메라 LookAt 간의 차이 값

	float fTime;		//타겟을 따라가는데 걸리는 시간
	float fSpeed;		//따을 따라가는 속도겟
	float fAccTime;		//누적 시간

public:
	void SetLookAt(Vec2 _Look) 
	{
		LookAt = _Look; 
		float MoveDist = (LookAt - PrevLookAt).Length();
		fSpeed = MoveDist / fTime;
		fAccTime = 0.f;
	}
	void SetTarget(CObject* _Target) { TargetObh = _Target; }
	Vec2 GetLookAt() { return CurLookAt; }
	Vec2 GetRenderPos(Vec2 ObjPos) { return ObjPos - Diff; }
	Vec2 GetRealPos(Vec2 RenderPos) { return RenderPos + Diff; }

	void Update();
private:
	void CalDiff();
};