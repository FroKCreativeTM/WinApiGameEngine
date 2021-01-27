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
	// 리소스를 등록할 인스턴스와 DC를 가져온다.
	m_hInst = hInst;
	m_hDC = hDC;

	// 백 버퍼 생성
	m_pBackBuffer = LoadTexture("BackBuffer", L"BackBuffer.bmp");

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

CTexture* CResourceManager::LoadTexture(FILE* pFile)
{
	// key의 길이 불러오기
	int nLength = 0;
	char strKey[MAX_PATH] = {};
	char strPathKey[MAX_PATH] = {};
	wchar_t strFileName[MAX_PATH] = {};

	fread(&nLength, 4, 1, pFile);
	fread(strKey, 1, nLength, pFile);
	strKey[nLength] = 0;

	// FileName 저장
	nLength = 0;
	fread(&nLength, 4, 1, pFile);
	fread(strFileName, 2, nLength, pFile);
	strFileName[nLength] = 0;

	// PathKey 저장
	nLength = 0;
	fread(&nLength, 4, 1, pFile);
	fread(strPathKey, 1, nLength, pFile);
	strPathKey[nLength] = 0;

	// 컬러키
	bool bColorKey = false;
	COLORREF dwColorKey = 0;
	fread(&bColorKey, 1, 1, pFile);
	fread(&dwColorKey, sizeof(COLORREF), 1, pFile);

	CTexture* pTex = GET_SINGLE(CResourceManager)->LoadTexture(strKey, strFileName, strPathKey);

	// 텍스처가 있고 컬러키가 있다면
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

	// 우리가 사용할 텍스처의 레퍼런스 카운터를 증가시킨다.
	iter->second->AddRef();

	// 텍스처 반환.
	return iter->second;
}

CTexture* CResourceManager::GetBackBuffer() const
{
	m_pBackBuffer->AddRef();
	return m_pBackBuffer;
}
