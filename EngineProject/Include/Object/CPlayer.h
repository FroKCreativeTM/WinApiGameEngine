#pragma once

#include "CMoveObj.h"

class CPlayer :
    public CMoveObj
{
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
};

