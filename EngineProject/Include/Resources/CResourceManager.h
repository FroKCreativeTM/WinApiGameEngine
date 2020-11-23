#pragma once

#include "../Game.h"

class CResourceManager
{
public : 
	bool Init(HINSTANCE hInst, HDC hDC);	// �ؽ�ó�� �ε��Ϸ��� �ν��Ͻ� �ڵ��� �ʿ��ϴ�.
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

