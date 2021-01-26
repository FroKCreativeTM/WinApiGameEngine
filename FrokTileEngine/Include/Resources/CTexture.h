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

	// 메모리 DC를 반환!
	HDC GetDC() const
	{
		return m_hMemDC; 
	}

public : 
	void SetColorKey(unsigned char r,
		unsigned char g,
		unsigned char b);
	void SetColorKey(COLORREF colorKey);
	COLORREF GetColorKey() const
	{
		return m_ColorKey;
	}

	bool GetColorKeyEnable() const
	{
		return m_bColorKeyEnable;
	}

	LONG GetWidth() const
	{
		return m_tInfo.bmWidth;
	}

	LONG GetHeight() const
	{
		return m_tInfo.bmHeight;
	}

private : 
	// 메모리 DC라는 것있다.
	// 화면 DC를 이용해서, 이것과 같은 성질을 같는
	// 메모리 DC를 만들어놓는 것이다.
	// 일종의 스탬프 같은 것
	HDC			m_hMemDC;
	// 메모리 DC에 픽셀 정보를 읽어와서 넣어야한다.
	// 그 픽셀 정보를 받아오기 위한 것이다.
	// 비트맵을 컨트롤(그리기 도구)을 하기 위한 도구이다.
	// 이미지마다 DC를 따로 생성하는 것이 편하다.
	HBITMAP		m_hBitmap;
	// 기존에 DC가 저장한 것을 가지고 있다가 돌려주는 용도
	HBITMAP		m_hOldBitmap;
	// 픽셀 정보 외 비트맵 정보를 저장하자!
	BITMAP		m_tInfo;
	// 컬러에 대한 정보를 저장한다.
	COLORREF	m_ColorKey;
	bool		m_bColorKeyEnable;	// 컬러키가 있는가

private : 
	// 이 관리자만 텍스처 생성 가능
	friend class CResourceManager;

private : 
	CTexture();
	~CTexture();
};

