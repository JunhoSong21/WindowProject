#pragma once
class CTimeMgr {
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER curCount;
	LARGE_INTEGER prevCount;
	LARGE_INTEGER prequency;

	double		dDT;
	double		dAcc;
	UINT		iCallCount;
	UINT		iFPS;

public:
	void Init();
	void Update();
	void Render();

	double getDT() { return dDT; }
	float  getfDT() { return (float)dDT; }
};