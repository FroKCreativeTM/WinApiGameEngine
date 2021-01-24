#pragma once
#include "CUI.h"

// Input이 관리할 것이다.
class CMouse :
    public CUI
{
public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CMouse* Clone();

public:
	void Hit(CCollider* pSrc, CCollider* pDst, float fDeltaTime);

private : 
	POSITION m_tMove;

private:
	friend class CObj;
	friend class CScene;

private:
	CMouse();
	CMouse(const CMouse& ref);
	~CMouse();
};

