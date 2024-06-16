#pragma once

class Res {
private:
	wstring key;
	wstring strRelativePath;

public:
	Res();
	virtual ~Res();

	void SetKey(const wstring& _key) { key = _key; }
	void SetRelativePath(const wstring& _str) { strRelativePath = _str; }

	const wstring& GetKey() { return key; }
	const wstring& GetRelativePath() { return strRelativePath; }
};