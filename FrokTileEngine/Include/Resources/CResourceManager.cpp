#include "CResourceManager.h"
#include "CTexture.h"

DEFINITION_SINGLE(CResourceManager)

CResourceManager::CResourceManager()
{

}

CResourceManager::~CResourceManager()
{
	SAFE_RELEASE(m_pBackBuffer);
	Safe_Release_Map(m_mapTexture);
}

bool CResourceManager::Init(HINSTANCE hInst, HDC hDC)
{
	// ���ҽ��� ����� �ν��Ͻ��� DC�� �����´�.
	m_hInst = hInst;
	m_hDC = hDC;

	// �� ���� ����
	m_pBackBuffer = LoadTexture("BackBuffer", L"BackBuffer.bmp");

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

CTexture* CResourceManager::LoadTexture(FILE* pFile)
{
	// key�� ���� �ҷ�����
	int nLength = 0;
	char strKey[MAX_PATH] = {};
	char strPathKey[MAX_PATH] = {};
	wchar_t strFileName[MAX_PATH] = {};

	fread(&nLength, 4, 1, pFile);
	fread(strKey, 1, nLength, pFile);
	strKey[nLength] = 0;

	// FileName ����
	nLength = 0;
	fread(&nLength, 4, 1, pFile);
	fread(strFileName, 2, nLength, pFile);
	strFileName[nLength] = 0;

	// PathKey ����
	nLength = 0;
	fread(&nLength, 4, 1, pFile);
	fread(strPathKey, 1, nLength, pFile);
	strPathKey[nLength] = 0;

	// �÷�Ű
	bool bColorKey = false;
	COLORREF dwColorKey = 0;
	fread(&bColorKey, 1, 1, pFile);
	fread(&dwColorKey, sizeof(COLORREF), 1, pFile);

	CTexture* pTex = GET_SINGLE(CResourceManager)->LoadTexture(strKey, strFileName, strPathKey);

	// �ؽ�ó�� �ְ� �÷�Ű�� �ִٸ�
	if (pTex && bColorKey)
	{
		pTex->SetColorKey(dwColorKey);
	}

	return pTex;
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

CTexture* CResourceManager::GetBackBuffer() const
{
	m_pBackBuffer->AddRef();
	return m_pBackBuffer;
}
