#include "pch.h"
#include "CPathMgr.h"

#include "CCore.h"

CPathMgr::CPathMgr()
	: contentPath{}
{
}

CPathMgr::~CPathMgr()
{
}

void CPathMgr::Init() {
	GetCurrentDirectory(255, contentPath);
	int len = (int)wcslen(contentPath);
	for (int i = len - 1; 0 <= i; --i) {
		if ('\\' == contentPath[i]) {
			contentPath[i] = '\0';
			break;
		}
	}
	wcscat_s(contentPath, 255, L"\\bin\\Contents\\");

	SetWindowText(CCore::Instance()->GetMainHandle(), contentPath);
}