#pragma once

#include "CCollider.h"

// 사각형의 충돌체입니다.
class CRectCollider :
    public CCollider
{
public:
	/* 게임 요소를 위한 메소드 */
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CRectCollider* Clone();

protected:
	CRectCollider();
	CRectCollider(const CRectCollider& col);
	virtual ~CRectCollider();

private:
	friend class CObj;
};

