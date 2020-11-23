#include "CTexture.h"
#include "../Core/CPathManager.h"

bool CTexture::LoadTexture(HINSTANCE hInst,
	HDC hDC,
	const string& strKey, 
	const wchar_t* pFileName, 
	const string& strPathKey)
{
	// �޸� DC�� ���������
	// CreateCompatibleDC
	// ���ڿ� �޸� DC�� ���������.
	m_hMemDC = CreateCompatibleDC(hDC);

	// ��ü ��θ� �����.
	const wchar_t* pPath = 
		GET_SINGLE(CPathManager)->FindPath(strPathKey);

	wstring strPath;

	if (pPath)
	{
		// ���ڿ��� �ƴ϶� NULL�� ���ٸ� �ٷ� ũ����!
		strPath = pPath;
	}

	// Ǯ ����
	strPath += pFileName;

	m_hBitmap = (HBITMAP)LoadImage(hInst, strPath.c_str(),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	// ������ ������� ��Ʈ�� ������ DC�� �����Ѵ�.
	// ������ �� ��ȯ�Ǵ� ���� DC�� �⺻���� �����Ǿ� �ִ�
	// ������ ��ȯ�ȴ�.
	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

	// �ε��� �� ������ ����
	// GetObject�� �̿��ؼ� �ڵ��� ������ �����´�.
	GetObject(m_hBitmap, sizeof(m_tInfo), &m_tInfo);

	return true;
}

CTexture::CTexture() : 
	m_hMemDC(nullptr)
{

}

CTexture::~CTexture()
{
	// ������ �����Ǿ��ִ� ������ �ٽ� �������ش�.
	SelectObject(m_hMemDC, m_hOldBitmap);

	// ��Ʈ���� �����ش�.
	DeleteObject(m_hBitmap);

	// DC�� �����ش�.
	DeleteDC(m_hMemDC);
}
