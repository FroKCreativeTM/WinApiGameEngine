#pragma once
#include "CMoveObj.h"

// 총알 클래스
// 각도를 이용해서 움직인다.
class CBullet :
    public CMoveObj
{
private:
	friend class CObj;

private:
	CBullet();
	CBullet(const CBullet& bullet);
	~CBullet();

public:
	virtual bool Init(float fObjX, float fObjY);
	// 총알이니까 상식적으로 입력이 필요없다.
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
};

