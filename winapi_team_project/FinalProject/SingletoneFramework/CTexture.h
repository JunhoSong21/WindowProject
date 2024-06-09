#pragma once
#include "Res.h"

class CTexture
	: public Res
{
private:
	HDC		dc;
	HBITMAP bit;
	BITMAP	info;

public:
	void Load(const wstring& _str);
	UINT Width() { return info.bmWidth; }
	UINT Height() { return info.bmHeight; }

	HDC GetDC() { return dc; }

private:
	CTexture();
	~CTexture();

	friend class CResMgr;
};