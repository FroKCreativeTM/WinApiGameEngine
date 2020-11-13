#pragma once

#include "CObj.h"

class CMoveObj : 
	public CObj
{
protected : 
	CMoveObj();
	CMoveObj(const CMoveObj& ref);
	virtual ~CMoveObj();

public:
	virtual bool Init() = 0;// ������ �־�ߵǴ� ���� �����Լ�;
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
};

