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
	// ī�޶� ���� ���� ��ġ�� �ʿ��ϴ�.
	POSITION		m_tPos;
	POSITION		m_tPivot;
	// Ŭ���̾�Ʈ(â ũ��), ����(�������� ũ��)
	RESOLUTION		m_tClientRS;
	RESOLUTION		m_tWorldRS;
	// ��ġ�Ǵ� �͵��� �� Obj��
	class CObj*		m_pTarget;

	DECLARE_SINGLE(CCamera)
};

