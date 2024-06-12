#pragma once

class Res;
class CTexture;
class CSound;

class CResMgr {
	SINGLE(CResMgr);
private:
	map<wstring, Res*> mapTex;
	map<wstring, Res*> mapSound;

public:
	CTexture* LoadTexture(const wstring& _key, const wstring& _path);
	CTexture* FindTexture(const wstring& _key);

	CSound* LoadSound(const wstring& _key, const wstring& _str);
	CSound* FindSound(const wstring& _key);
};