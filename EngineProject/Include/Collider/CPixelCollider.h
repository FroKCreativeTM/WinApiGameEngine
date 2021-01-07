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
	/* ���� ��Ҹ� ���� �޼ҵ� */
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual bool Collision(CCollider* pDst);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CPixelCollider* Clone();

public:
	// ��Ʈ�� �̹����� �ҷ��ͼ� �̿� ���� �浹ó���� �Ѵ�.
	bool SetPixelInfo(char* pFileName, const string& strPathKey = TEXTURE_PATH);

protected:
	CPixelCollider();
	CPixelCollider(const CPixelCollider& col);
	virtual ~CPixelCollider();

private:
	friend class CObj;

private:
	// �ȼ� ������ �޾Ƽ� �����ϱ� ���� �迭
	vector<PIXEL>		m_vecPixel;
};

