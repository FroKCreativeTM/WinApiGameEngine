#include "CPixelCollider.h"
#include "../Object/CObj.h"
#include "CRectCollider.h"
#include "CSphereCollider.h"
#include "CPointCollider.h"
#include "../Core/CPathManager.h"		// Full Path ����� ���� �뵵

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

	// �н��� �ִٸ�
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

	// ��Ʈ�� ���� ��� ����ü�� �̿��ؼ� �����Ѵ�.
	BITMAPFILEHEADER fh;
	BITMAPINFOHEADER ih;

	// ���Ϸκ��� �о�´�.
	fread(&fh, sizeof(fh), 1, pFile);
	fread(&ih, sizeof(ih), 1, pFile);

	m_nWidth = ih.biWidth;
	m_nHeight = ih.biHeight;

	// ���͸� ���� �ٽ� ���������Ѵ�.
	m_vecPixel.clear();
	m_vecPixel.resize(m_nWidth * m_nHeight);

	// �ȼ� ������ ���� ��� �´�.
	// ������ �̷��� �Ǹ�, ���� �����Ǽ� �о�����.
	fread(&m_vecPixel[0], sizeof(PIXEL), m_vecPixel.size(), pFile);

	// ���� ����� �ȼ�
	PPIXEL pPixelArr = new PIXEL[m_nWidth];

	// �� �Ʒ� ���������ش�.
	for (int i = 0; i < m_nHeight / 2; ++i)
	{
		// ���� �ε����� �ȼ��� ���� �������ش�.
		memcpy(pPixelArr, &m_vecPixel[i * m_nWidth], sizeof(PIXEL) * m_nWidth);
		// �� �ȼ��� ������ ���� �Ʒ��� �����Ѵ�.
		memcpy(&m_vecPixel[i * m_nWidth], &m_vecPixel[(m_nHeight - i - 1) * m_nWidth], sizeof(PIXEL)* m_nWidth);
		// �Ʒ� �ȼ��� ����� �迭�� �����Ѵ�.
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
