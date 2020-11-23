#pragma once

#include "../Game.h"

class CResourceManager
{
public : 
	bool Init(HINSTANCE hInst, HDC hDC);	// 텍스처를 로딩하려면 인스턴스 핸들이 필요하다.
	class CTexture* LoadTexture(const string& strKey,
		const wchar_t* pFileName, 
		const string& strPathKey = TEXTURE_PATH);
	class CTexture* FindTexture(const string& strKey);

private : 
	HINSTANCE		m_hInst;
	HDC				m_hDC;
	unordered_map<string, class CTexture*> m_mapTexture;

	DECLARE_SINGLE(CResourceManager)
};

