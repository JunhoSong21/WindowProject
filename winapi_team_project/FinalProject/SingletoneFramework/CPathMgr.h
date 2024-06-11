#pragma once

class CPathMgr {
	SINGLE(CPathMgr);
private:
	wchar_t contentPath[255];

public:
	void Init();
	const wchar_t* GetContentPath() { return contentPath; }
};