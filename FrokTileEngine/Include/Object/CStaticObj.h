#pragma once

#include "CObj.h"

class CStaticObj :
    public CObj
{
protected :
	CStaticObj();
	CStaticObj(const CStaticObj& ref);
    virtual ~CStaticObj();

public:
	virtual bool Init() = 0;// ������ �־�ߵǴ� ���� �����Լ�;
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CStaticObj* Clone() = 0;
};

