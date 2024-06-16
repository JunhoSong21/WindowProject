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
	CTexture*		tex; // �ִϸ��̼��� ����ϴ� �ؽ���

	vector<AnimFrm> vecFrm; // �������� ��� ����
	int				curFrm; // ���� ������
	float			accTime; // �ð� ������

	bool			finish; // ��� ���� �����ߴ��� ����

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