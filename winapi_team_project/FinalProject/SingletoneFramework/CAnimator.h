#pragma once

class CObject;
class CAnimation;
class CTexture;

class CAnimator {
private:
	map<wstring, CAnimation*>	mapAnim; // 모든 애니메이션
	CAnimation*					curAnim; // 현재 재생중인 애니메이션
	CObject*					owner;   // 애니메이터 소유 오브젝트
	bool						repeat;  // 반복재생 여부

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