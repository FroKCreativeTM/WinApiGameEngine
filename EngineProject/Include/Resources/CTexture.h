#pragma once

#include "../Core/CRef.h"

class CTexture : 
	public CRef
{
public : 
	bool LoadTexture(HINSTANCE hInst,
		HDC hDC,
		const string& strKey,
		const wchar_t* pFileName,
		const string& strPathKey = TEXTURE_PATH);

	// �޸� DC�� ��ȯ!
	HDC GetDC() const
	{
		return m_hMemDC;
	}

private : 
	// �޸� DC��� ���ִ�.
	// ȭ�� DC�� �̿��ؼ�, �̰Ͱ� ���� ������ ����
	// �޸� DC�� �������� ���̴�.
	// ������ ������ ���� ��
	HDC			m_hMemDC;
	// �޸� DC�� �ȼ� ������ �о�ͼ� �־���Ѵ�.
	// �� �ȼ� ������ �޾ƿ��� ���� ���̴�.
	// ��Ʈ���� ��Ʈ��(�׸��� ����)�� �ϱ� ���� �����̴�.
	// �̹������� DC�� ���� �����ϴ� ���� ���ϴ�.
	HBITMAP		m_hBitmap;
	// ������ DC�� ������ ���� ������ �ִٰ� �����ִ� �뵵
	HBITMAP		m_hOldBitmap;
	// �ȼ� ���� �� ��Ʈ�� ������ ��������!
	BITMAP		m_tInfo;

private : 
	// �� �����ڸ� �ؽ�ó ���� ����
	friend class CResourceManager;

private : 
	CTexture();
	~CTexture();
};

