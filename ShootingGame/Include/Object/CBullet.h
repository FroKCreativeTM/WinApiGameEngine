#pragma once
#include "CMoveObj.h"
class CBullet :
    public CMoveObj
{
private:
	friend class CObj;

private:
	CBullet();
	CBullet(const CBullet& mushroom);
	~CBullet();

public:
	virtual bool Init();
	// 총알이니까 상식적으로 입력이 필요없다.
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
};

