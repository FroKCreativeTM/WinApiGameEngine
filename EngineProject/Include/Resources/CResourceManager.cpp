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
	// ���ҽ��� ����� �ν��Ͻ��� DC�� �����´�.
	m_hInst = hInst;
	m_hDC = hDC;
	return true;
}

// �ؽ�ó �ε� �ý���
CTexture* CResourceManager::LoadTexture(const string& strKey,
	const wchar_t* pFileName, const string& strPathKey)
{
	// �ؽ�ó�� �ϴ� ã�´�.
	CTexture* pTexture = FindTexture(strKey);

	// �ؽ�ó�� �̹� ����Ǿ��ִٸ� �״�� ��ȯ
	if (pTexture)
	{
		return pTexture;
	}

	pTexture = new CTexture;

	// �ؽ�ó �ε�
	if (!pTexture->LoadTexture(m_hInst, m_hDC, strKey, 
		pFileName, strPathKey))
	{
		// �����ϸ�(��ο� �ؽ�ó�� ���ٸ�)
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

	// �츮�� ����� �ؽ�ó�� ���۷��� ī���͸� ������Ų��.
	iter->second->AddRef();

	// �ؽ�ó ��ȯ.
	return iter->second;
}
