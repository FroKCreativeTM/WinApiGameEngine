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

bool CResourceManager::Init(HINSTANCE hInst, HDC hDC)
{
	// 리소스를 등록할 인스턴스와 DC를 가져온다.
	m_hInst = hInst;
	m_hDC = hDC;
	return true;
}

// 텍스처 로딩 시스템
CTexture* CResourceManager::LoadTexture(const string& strKey,
	const wchar_t* pFileName, const string& strPathKey)
{
	// 텍스처를 일단 찾는다.
	CTexture* pTexture = FindTexture(strKey);

	// 텍스처가 이미 저장되어있다면 그대로 반환
	if (pTexture)
	{
		return pTexture;
	}

	pTexture = new CTexture;

	// 텍스처 로딩
	if (!pTexture->LoadTexture(m_hInst, m_hDC, strKey, 
		pFileName, strPathKey))
	{
		// 실패하면(경로에 텍스처가 없다면)
		SAFE_RELEASE(pTexture);
		return nullptr;
	}

	pTexture->AddRef();
	m_mapTexture.insert(make_pair(strKey, pTexture));

	return pTexture;
}

CTexture* CResourceManager::FindTexture(const string& strKey)
{
	unordered_map<string, CTexture*>::iterator iter = 
		m_mapTexture.find(strKey);

	if (iter == m_mapTexture.end())
	{
		return nullptr;
	}

	// 우리가 사용할 텍스처의 레퍼런스 카운터를 증가시킨다.
	iter->second->AddRef();

	// 텍스처 반환.
	return iter->second;
}
