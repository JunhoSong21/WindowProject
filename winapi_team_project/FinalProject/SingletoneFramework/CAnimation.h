#pragma once

class CAnimator;
class CTexture;

struct AnimFrm {
	float	Duration;
	Vec2	ptLT;
	Vec2	ptSlice;
	Vec2	offSet;
};

class CAnimation {
private:
	wstring			strName;
	CAnimator*		animator;
	CTexture*		tex; // 애니메이션이 사용하는 텍스쳐

	vector<AnimFrm> vecFrm; // 프레임의 모든 정보
	int				curFrm; // 현재 프레임
	float			accTime; // 시간 누적용

	bool			finish; // 재생 끝에 도달했는지 여부

	void SetName(const wstring& _strName) { strName = _strName; }

public:
	CAnimation();
	~CAnimation();

	const wstring& GetName() { return strName; }

	bool IsFinish() { return finish; }

	void SetFrame(int _FrameIdx) {
		finish = false;
		curFrm = _FrameIdx;
		accTime = 0.f;
	}

	AnimFrm& GetFrame(int _iIdx) { return vecFrm[_iIdx]; }
	UINT GetMaxFrame() { return (UINT)vecFrm.size(); }

	void Create(CTexture* _Tex, Vec2 _LT, Vec2 _SliceSize, 
		Vec2 _Step, float _Duration, UINT _FrameCount);

	void Update();
	void Render(HDC _hDC);

	friend class CAnimator;
};