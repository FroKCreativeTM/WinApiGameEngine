#pragma once
#include "CMoveObj.h"
class CZako :
    public CMoveObj
{
private:
	friend class CObj;

private:
	CZako();
	CZako(const CZako& mushroom);
	~CZako();

private:
	MOVE_DIR		m_eDir;

public:
	virtual bool Init();
	// 적이니까 상식적으로 입력이 필요없다.
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CZako* Clone();
};

