#pragma once

#include "../Game.h"

class CResourceManager
{
public : 
	class CTexture* LoadTexture(const string& strKey,
		const wchar_t* pFileName, const string& strPathKey);

private : 
	unordered_map<string, class CTexture*> m_mapTexture;

	DECLARE_SINGLE(CResourceManager)
};

