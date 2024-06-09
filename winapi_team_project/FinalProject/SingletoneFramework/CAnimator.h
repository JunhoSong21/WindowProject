#pragma once

class CObject;
class CAnimation;
class CTexture;

class CAnimator {
private:
	map<wstring, CAnimation*>	mapAnim; // ��� �ִϸ��̼�
	CAnimation*					curAnim; // ���� ������� �ִϸ��̼�
	CObject*					owner;   // �ִϸ����� ���� ������Ʈ
	bool						repeat;  // �ݺ���� ����

public:
	CAnimator();
	~CAnimator();

	void CreateAnimation(const wstring& _strName, CTexture* _Tex, Vec2 _LT, Vec2 _SliceSize, 
		Vec2 _Step, float _Duration, UINT _FrameCount);
	CAnimation* FindAnimation(const wstring& _strName);
	void Play(const wstring& _strName, bool _repeat);

	void Update();
	void Render(HDC _hDC);

	CObject* GetObj() { return owner; }


	friend class CObject;
};