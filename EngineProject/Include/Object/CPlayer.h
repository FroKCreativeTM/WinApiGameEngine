#pragma once

#include "CMoveObj.h"

class CPlayer :
    public CMoveObj
{

public:
	virtual bool Init();		
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CPlayer* Clone();

public :
	void Hit(CCollider* pSrc, CCollider* pDst, float fDeltaTime);
	void HitStay(CCollider* pSrc, CCollider* pDst, float fDeltaTime);

private : 
	void Fire();

private : 
	int			m_nHP;
	bool		m_isAttack;
	bool		m_isLeft;

private:
	friend class CObj;
	friend class CScene;

private:
	CPlayer();
	CPlayer(const CPlayer& ref);
	~CPlayer();
};

