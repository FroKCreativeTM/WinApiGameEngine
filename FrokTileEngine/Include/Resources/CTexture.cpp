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

void CTexture::SaveFromPath(const char* pFileName, const string& strPathKey)
{
	
}

void CTexture::Save(FILE* pFile)
{
	// key�� ���� ����
	int nLength = m_strKey.length();
	fwrite(&nLength, 4, 1, pFile);
	fwrite(m_strKey.c_str(), 1, nLength, pFile);

	// FileName ����
	nLength = m_strFileName.length();
	fwrite(&nLength, 4, 1, pFile);
	fwrite(m_strFileName.c_str(), 2, nLength, pFile);

	// PathKey ����
	nLength = m_strPathKey.length();
	fwrite(&nLength, 4, 1, pFile);
	fwrite(m_strPathKey.c_str(), 1, nLength, pFile);

	// �÷�Ű
	fwrite(&m_bColorKeyEnable, 1, 1, pFile);
	fwrite(&m_ColorKey, sizeof(COLORREF), 1, pFile);
}

void CTexture::LoadFromPath(const char* pFileName, const string& strPathKey)
{

}

void CTexture::Load(FILE* pFile)
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

	// �ؽ�ó�� �����´�.
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
	// �÷�Ű�� ���� �� ���� ����Ÿ ������ �����Ѵ�.
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
