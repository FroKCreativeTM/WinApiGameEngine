#pragma once

#include "CMoveObj.h"

class CPlayer :
    public CMoveObj
{
private : 
	friend class CObj;
	friend class CScene;

private :
	CPlayer();
	CPlayer(const CPlayer& ref);
    ~CPlayer();

public:
	virtual bool Init();		
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CPlayer* Clone();

private : 
	void Fire();
	void Skill1();
};

