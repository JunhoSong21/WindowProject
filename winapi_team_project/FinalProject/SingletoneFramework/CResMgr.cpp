#include "pch.h"
#include "CResMgr.h"

#include "CPathMgr.h"
#include "CTexture.h"

CResMgr::CResMgr() {

}

CResMgr::~CResMgr() {
	Safe_Delete_Map(mapTex);
}

CTexture* CResMgr::LoadTexture(const wstring& _key, const wstring& _path) {
	CTexture* tex = FindTexture(_key);
	if (nullptr != tex)
		return tex;

	wstring strPath = CPathMgr::Instance()->GetContentPath();
	strPath += _path;

	tex = new CTexture;
	tex->Load(strPath);
	tex->SetKey(_key);
	tex->SetRelativePath(_path);

	mapTex.insert(make_pair(_key, tex));

	return tex;
}

CTexture* CResMgr::FindTexture(const wstring& _key) {
	map<wstring, Res*>::iterator iter = mapTex.find(_key);

	if (iter == mapTex.end()) {
		return  nullptr;
	}

	return (CTexture*)iter->second;
}