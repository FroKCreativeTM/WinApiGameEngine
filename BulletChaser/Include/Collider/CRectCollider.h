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

protected:
	CRectCollider();
	CRectCollider(const CRectCollider& col);
	virtual ~CRectCollider();

private:
	friend class CObj;
};

