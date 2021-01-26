#pragma once

#include "../Game.h"

class CCamera
{
public : 
	bool Init(const POSITION& tPos, 
		const RESOLUTION& tRS,
		const RESOLUTION& tWorldRS);
	void Input(float fDeltaTime);
	void Update(float fDeltaTime);

public : 
	void SetTarget(class CObj* pObj);

	void SetPivot(const POSITION& ref)
	{
		m_tPivot = ref;
	}
	 
	void SetPivot(float x, float y)
	{
		m_tPivot = POSITION(x, y);
	}

	void SetPos(const POSITION& ref)
	{
		m_tPos = ref;
	}

	void SetPos(float x, float y)
	{
		m_tPos = POSITION(x, y);
	}

	void SetClientResolution(const RESOLUTION& ref)
	{
		m_tClientRS = ref;
	}

	void SetClientResolution(int x, int y)
	{
		m_tClientRS = RESOLUTION(x, y);
	}

	void SetWorldResolution(const RESOLUTION& ref)
	{
		m_tWorldRS = ref;
	}

	void SetWorldResolution(int x, int y)
	{
		m_tWorldRS = RESOLUTION(x, y);
	}

	POSITION GetPos() const
	{
		return m_tPos;
	}

	RESOLUTION GetClientResolution() const
	{
		return m_tClientRS;
	}

private : 
	// 카메라도 월드 상의 위치가 필요하다.
	POSITION		m_tPos;
	POSITION		m_tPivot;
	// 클라이언트(창 크기), 월드(스테이지 크기)
	RESOLUTION		m_tClientRS;
	RESOLUTION		m_tWorldRS;
	// 배치되는 것들은 다 Obj다
	class CObj*		m_pTarget;

	DECLARE_SINGLE(CCamera)
};

