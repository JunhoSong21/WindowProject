#pragma once

class CObject;

class CCamera
{
	SINGLE(CCamera);
private:
	Vec2 LookAt;		//ī�޶� ���� ��ġ
	Vec2 CurLookAt;		//���� ��ġ�� �������ִ� ī�޶� ��ġ
	Vec2 PrevLookAt;	//���� �����ӿ��� ī�޶� ���� ��ġ
	
	CObject* TargetObh;	//ī�޶��� Ÿ�� ������Ʈ
	Vec2 Diff;			//�ػ� �߽���ġ�� ī�޶� LookAt ���� ���� ��

	float fTime;		//Ÿ���� ���󰡴µ� �ɸ��� �ð�
	float fSpeed;		//���� ���󰡴� �ӵ���
	float fAccTime;		//���� �ð�

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