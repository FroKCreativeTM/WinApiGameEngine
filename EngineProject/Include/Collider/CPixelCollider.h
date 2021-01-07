#pragma once
#include "CCollider.h"

typedef struct _tagPixel
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
}PIXEL, *PPIXEL;

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
	bool SetPixelInfo(char* pFileName, const string& strPathKey = TEXTURE_PATH);

protected:
	CPixelCollider();
	CPixelCollider(const CPixelCollider& col);
	virtual ~CPixelCollider();

private:
	friend class CObj;

private:
	// 픽셀 정보를 받아서 저장하기 위한 배열
	vector<PIXEL>		m_vecPixel;
};

