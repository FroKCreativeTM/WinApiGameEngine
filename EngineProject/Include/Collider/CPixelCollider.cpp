#include "CPixelCollider.h"
#include "../Object/CObj.h"
#include "CRectCollider.h"
#include "CSphereCollider.h"
#include "CPointCollider.h"
#include "../Core/CPathManager.h"		// Full Path 만들기 위한 용도

bool CPixelCollider::Init()
{
	return true;
}

void CPixelCollider::Input(float fDeltaTime)
{
	CCollider::Input(fDeltaTime);
}

int CPixelCollider::Update(float fDeltaTime)
{
	CCollider::Update(fDeltaTime);
	return 0;
}

int CPixelCollider::LateUpdate(float fDeltaTime)
{
	CCollider::LateUpdate(fDeltaTime);
	return 0;
}

bool CPixelCollider::Collision(CCollider* pDst)
{
	switch (pDst->GetColliderType())
	{
	case CT_RECT:
		return CollisionRectToPixel(((CRectCollider*)pDst)->GetWorldInfo(), m_vecPixel, m_nWidth, m_nHeight);
	case CT_POINT:
		return CollisionPixelToPoint(m_vecPixel, m_nWidth, m_nHeight, ((CPointCollider*)pDst)->GetPoint());
	}
}

void CPixelCollider::Render(HDC hDC, float fDeltaTime)
{
	CCollider::Render(hDC, fDeltaTime);
}

CPixelCollider* CPixelCollider::Clone()
{
	return new CPixelCollider(*this);
}

bool CPixelCollider::SetPixelInfo(const char* pFileName, const string& strPathKey)
{
	const char* pPath = GET_SINGLE(CPathManager)->FindPathMultiByte(strPathKey);
	string strPath;

	// 패스가 있다면
	if (pPath)
	{
		strPath = pPath;
	}

	strPath += pFileName;

	FILE* pFile = nullptr;

	fopen_s(&pFile, strPath.c_str(), "rb");

	if (!pFile)
	{
		return false;
	}

	// 비트맵 파일 헤더 구조체를 이용해서 구현한다.
	BITMAPFILEHEADER fh;
	BITMAPINFOHEADER ih;

	// 파일로부터 읽어온다.
	fread(&fh, sizeof(fh), 1, pFile);
	fread(&ih, sizeof(ih), 1, pFile);

	m_nWidth = ih.biWidth;
	m_nHeight = ih.biHeight;

	// 벡터를 비우고 다시 리사이즈한다.
	m_vecPixel.clear();
	m_vecPixel.resize(m_nWidth * m_nHeight);

	// 픽셀 정보를 전부 들고 온다.
	// 문제는 이렇게 되면, 상하 반전되서 읽어진다.
	fread(&m_vecPixel[0], sizeof(PIXEL), m_vecPixel.size(), pFile);

	// 가로 저장용 픽셀
	PPIXEL pPixelArr = new PIXEL[m_nWidth];

	// 위 아래 반전시켜준다.
	for (int i = 0; i < m_nHeight / 2; ++i)
	{
		// 현재 인덱스의 픽셀한 줄을 저장해준다.
		memcpy(pPixelArr, &m_vecPixel[i * m_nWidth], sizeof(PIXEL) * m_nWidth);
		// 위 픽셀을 저장한 것을 아래로 복사한다.
		memcpy(&m_vecPixel[i * m_nWidth], &m_vecPixel[(m_nHeight - i - 1) * m_nWidth], sizeof(PIXEL)* m_nWidth);
		// 아래 픽셀을 저장용 배열에 저장한다.
		memcpy(&m_vecPixel[(m_nHeight - i - 1) * m_nWidth], pPixelArr, sizeof(PIXEL) * m_nWidth);
	}

	delete[] pPixelArr;

	fclose(pFile);

	return true;
}

CPixelCollider::CPixelCollider()
{
	m_eColType = CT_PIXEL;
	m_nWidth = 0;
	m_nHeight = 0;
}

CPixelCollider::CPixelCollider(const CPixelCollider& col) : 
	CCollider(col)
{
	m_nWidth = col.m_nWidth;
	m_nHeight = col.m_nHeight;
}

CPixelCollider::~CPixelCollider()
{
}
