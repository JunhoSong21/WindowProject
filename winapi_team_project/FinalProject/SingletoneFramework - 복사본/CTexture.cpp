#include "pch.h"
#include "CTexture.h"
#include "CPathMgr.h"
#include "CCore.h"

CTexture::CTexture()
	: bit(0)
	, dc(0)
	, info{}
{
}

CTexture::~CTexture() {
	DeleteDC(dc);
	DeleteObject(bit);
}

void CTexture::Load(const wstring& _str) {
	bit = (HBITMAP)LoadImage(nullptr, _str.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	assert(bit);

	dc = CreateCompatibleDC(CCore::Instance()->GetMainDC());
	HBITMAP preBit = (HBITMAP)SelectObject(dc, bit);
	DeleteObject(preBit);

	GetObject(bit, sizeof(BITMAP), &info);
}