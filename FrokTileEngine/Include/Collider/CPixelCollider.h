#pragma once
#include "CCollider.h"



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
	// �ȼ� ������ �޾Ƽ� �����ϱ� ���� �迭
	vector<PIXEL>		m_vecPixel;
	int					m_nWidth;
	int					m_nHeight;
};

