#pragma once

#include "../Core/CRef.h"

// 충돌에 관련된 기본 클래스입니다.
class CCollider : 
	public CRef	
{
public : 
	/* 게임 요소를 위한 메소드 */
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

