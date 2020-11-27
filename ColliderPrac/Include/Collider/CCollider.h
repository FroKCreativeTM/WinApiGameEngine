#pragma once

#include "../Core/CRef.h"

// �浹�� ���õ� �⺻ Ŭ�����Դϴ�.
class CCollider : 
	public CRef	
{
public : 
	/* ���� ��Ҹ� ���� �޼ҵ� */
	virtual bool Init() = 0;
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	// 
	virtual CCollider* Clone() = 0;

protected:
	CCollider();
	CCollider(const CCollider& col);
	virtual ~CCollider() = 0;

public : 
	COLLIDER_TYPE GetColliderType() const
	{
		return m_eColType;
	}



protected :
	COLLIDER_TYPE m_eColType;

private : 
	friend class CObj;
};

