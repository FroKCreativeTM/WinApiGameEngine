#pragma once
#include "CCollider.h"
class CSphereCollider :
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
	virtual CSphereCollider* Clone();
	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);

public:
	void SetSphere(const POSITION& tCenter, float fRadius)
	{
		m_tInfo.tCenter = tCenter;
		m_tInfo.fRadius = fRadius;
	}

	SPHERE GetInfo() const
	{
		return m_tInfo;
	}

	SPHERE GetWorldInfo() const
	{
		return m_tWorldInfo;
	}

protected:
	CSphereCollider();
	CSphereCollider(const CSphereCollider& col);
	virtual ~CSphereCollider();

private:
	friend class CObj;

private:
	SPHERE m_tInfo;
	SPHERE m_tWorldInfo;
};

