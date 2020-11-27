#pragma once

#include "CObj.h"

class CMoveObj : 
	public CObj
{
protected : 
	CMoveObj();
	CMoveObj(const CMoveObj& ref);
	virtual ~CMoveObj();

public : 
	// MoveObj 만의 기능이다.
	// position을 넣어주면 그만큼 x,y 축으로 움직인다.
	void Move(float x, float y);
	void Move(float x, float y, float fDeltaTime);
	void Move(const POSITION& tMove);
	void Move(const POSITION& tMove, float fDeltaTime);

	// 특정 방향으로 독립적으로 이동
	void MoveX(float x);
	void MoveXFromSpeed(float fDeltaTime, MOVE_DIR eDir);
	void MoveX(float x, float fDeltaTime);
	void MoveY(float y);
	void MoveYFromSpeed(float fDeltaTime, MOVE_DIR eDir);
	void MoveY(float y, float fDeltaTime);

	// 특정 각도를 이용해서 방향으로 이동할 때
	void MoveAngle();
	void MoveAngle(float fDeltaTime);

public:
	virtual bool Init() = 0;// 하위에 있어야되니 순수 가상함수;
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CMoveObj* Clone() = 0;

protected : 
	// 자식도 못 건들이는 앵글!
	float			m_fAngle;
	float			m_fSpeed;

public : 
	void SetAngle(float fAngle)
	{
		m_fAngle = fAngle;
	}

	void SetSpeed(float fSpeed)
	{
		m_fSpeed = fSpeed;
	}

	float GetAngle() const
	{
		return m_fAngle;
	}

	float GetSpeed() const
	{
		return m_fSpeed;
	}
};

