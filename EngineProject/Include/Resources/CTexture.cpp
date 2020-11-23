#include "CTexture.h"
#include "../Core/CPathManager.h"

bool CTexture::LoadTexture(HINSTANCE hInst,
	HDC hDC,
	const string& strKey, 
	const wchar_t* pFileName, 
	const string& strPathKey)
{
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

CTexture::CTexture() : 
	m_hMemDC(nullptr)
{

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
