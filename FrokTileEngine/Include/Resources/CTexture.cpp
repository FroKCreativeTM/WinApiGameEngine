#include "CTexture.h"
#include "../Core/CPathManager.h"
#include "CResourceManager.h"

bool CTexture::LoadTexture(HINSTANCE hInst,
	HDC hDC,
	const string& strKey, 
	const wchar_t* pFileName, 
	const string& strPathKey)
{
	m_strFileName = pFileName;
	m_strKey = strKey;
	m_strPathKey = strPathKey;

	// 메모리 DC를 만들어주자
	// CreateCompatibleDC
	// 인자용 메모리 DC가 만들어진다.
	m_hMemDC = CreateCompatibleDC(hDC);

	// 전체 경로를 만든다.
	const wchar_t* pPath = 
		GET_SINGLE(CPathManager)->FindPath(strPathKey);

	wstring strPath;

	if (pPath)
	{
		// 문자열이 아니라 NULL이 들어간다면 바로 크래시!
		strPath = pPath;
	}

	// 풀 정보
	strPath += pFileName;

	m_hBitmap = (HBITMAP)LoadImage(hInst, strPath.c_str(),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	// 위에서 만들어준 비트맵 도구를 DC에 저장한다.
	// 저장할 때 반환되는 값은 DC에 기본으로 지정되어 있던
	// 도구가 반환된다.
	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

	// 로딩이 다 끝나고 나면
	// GetObject를 이용해서 핸들의 정보를 가져온다.
	GetObject(m_hBitmap, sizeof(m_tInfo), &m_tInfo);

	return true;
}

void CTexture::SaveFromPath(const char* pFileName, const string& strPathKey)
{
	
}

void CTexture::Save(FILE* pFile)
{
	// key의 길이 저장
	int nLength = m_strKey.length();
	fwrite(&nLength, 4, 1, pFile);
	fwrite(m_strKey.c_str(), 1, nLength, pFile);

	// FileName 저장
	nLength = m_strFileName.length();
	fwrite(&nLength, 4, 1, pFile);
	fwrite(m_strFileName.c_str(), 2, nLength, pFile);

	// PathKey 저장
	nLength = m_strPathKey.length();
	fwrite(&nLength, 4, 1, pFile);
	fwrite(m_strPathKey.c_str(), 1, nLength, pFile);

	// 컬러키
	fwrite(&m_bColorKeyEnable, 1, 1, pFile);
	fwrite(&m_ColorKey, sizeof(COLORREF), 1, pFile);
}

void CTexture::LoadFromPath(const char* pFileName, const string& strPathKey)
{

}

void CTexture::Load(FILE* pFile)
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

	// 텍스처를 가져온다.
	GET_SINGLE(CResourceManager)->LoadTexture(strKey, strFileName, strPathKey);
}

void CTexture::SetColorKey(unsigned char r, unsigned char g, unsigned char b)
{
	m_ColorKey = RGB(r, g, b);
	m_bColorKeyEnable = true;
}

void CTexture::SetColorKey(COLORREF colorKey)
{
	m_ColorKey = colorKey;
	m_bColorKeyEnable = true;
}

CTexture::CTexture() : 
	m_hMemDC(nullptr),
	m_bColorKeyEnable(false),
	m_ColorKey(RGB(255, 0, 255))
{
	// 컬러키는 제일 안 쓰는 마젠타 색으로 설정한다.
}

CTexture::~CTexture()
{
	// 기존에 지정되어있던 도구로 다시 지정해준다.
	SelectObject(m_hMemDC, m_hOldBitmap);

	// 비트맵을 지워준다.
	DeleteObject(m_hBitmap);

	// DC를 지워준다.
	DeleteDC(m_hMemDC);
}
