#include "CResourceManager.h"
#include "CTexture.h"

DEFINITION_SINGLE(CResourceManager)

CResourceManager::CResourceManager()
{

}

CResourceManager::~CResourceManager()
{
	Safe_Release_Map(m_mapTexture);
}

// 텍스처 로딩 시스템
CTexture* CResourceManager::LoadTexture(const string& strKey,
	const wchar_t* pFileName, const string& strPathKey)
{
	return nullptr;
}
