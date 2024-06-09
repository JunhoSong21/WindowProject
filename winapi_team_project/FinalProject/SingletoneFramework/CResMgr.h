#pragma once

class Res;
class CTexture;

class CResMgr {
	SINGLE(CResMgr);
private:
	map<wstring, Res*> mapTex;

public:
	CTexture* LoadTexture(const wstring& _key, const wstring& _path);
	CTexture* FindTexture(const wstring& _key);
};

