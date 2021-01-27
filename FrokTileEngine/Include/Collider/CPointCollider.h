#pragma once
#include "CCollider.h"

class CPointCollider :
	public CCollider
{
public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual bool Collision(CCollider* pDst);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CPointCollider* Clone();
	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);

public : 
	POSITION GetPoint() const
	{
		return m_tPos;
	}

	void SetDistance(float x, float y)
	{
		m_tDist.x = x;
		m_tDist.y = y;
	}

	void SetDistance(const POSITION& dist)
	{
		m_tDist = dist;
	}

protected:
	CPointCollider();
	CPointCollider(const CPointCollider& col);
	virtual ~CPointCollider();

protected:
	POSITION m_tPos;		// 
	POSITION m_tDist;		// 원본 오브젝트로부터 얼마나 떨어져있는가

private:
	friend class CObj;
};