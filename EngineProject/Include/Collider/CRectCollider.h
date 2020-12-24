#pragma once

#include "CCollider.h"

// �簢���� �浹ü�Դϴ�.
class CRectCollider :
    public CCollider
{
public:
	/* ���� ��Ҹ� ���� �޼ҵ� */
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CRectCollider* Clone();

public : 
	void SetRect(float left, float top, float right, float bottom);

	RECTANGLE GetInfo() const
	{
		return m_tInfo;
	}

	RECTANGLE GetWorldInfo() const
	{
		return m_tWorldInfo;
	}

protected:
	CRectCollider();
	CRectCollider(const CRectCollider& col);
	virtual ~CRectCollider();

private:
	friend class CObj;

private :
	RECTANGLE m_tInfo;
	RECTANGLE m_tWorldInfo; // ������ġ
};

