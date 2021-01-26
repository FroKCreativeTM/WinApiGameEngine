#pragma once
#include "CCollider.h"



class CPixelCollider :
    public CCollider
{
public:
	/* 게임 요소를 위한 메소드 */
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual bool Collision(CCollider* pDst);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CPixelCollider* Clone();

public:
	// 비트맵 이미지를 불러와서 이에 대한 충돌처리를 한다.
	bool SetPixelInfo(const char* pFileName, const string& strPathKey = TEXTURE_PATH);

	const vector<PIXEL>& GetPixel() const
	{
		return m_vecPixel;
	}

	int GetWidth() const
	{
		return m_nWidth;
	}

	int GetHeight() const
	{
		return m_nHeight;
	}

protected:
	CPixelCollider();
	CPixelCollider(const CPixelCollider& col);
	virtual ~CPixelCollider();

private:
	friend class CObj;

private:
	// 픽셀 정보를 받아서 저장하기 위한 배열
	vector<PIXEL>		m_vecPixel;
	int					m_nWidth;
	int					m_nHeight;
};

