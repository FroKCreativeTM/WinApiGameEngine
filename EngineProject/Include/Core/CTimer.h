#pragma once
#include "../Game.h"

// �����Ӱ� �ð��� �����ϱ� ���� �ִ� Ŭ�����̴�.
class CTimer
{
private : 
	LARGE_INTEGER	m_tSecond;
	LARGE_INTEGER	m_tTime;
	float			m_fDeltaTime;
	float			m_fFPS;
	float			m_fFPSTime;
	int				m_nFrameMax;
	int				m_nFrame;

public : 
	float GetDeltaTime() const
	{
		return m_fDeltaTime;
	}

	float GetFPS() const
	{
		return m_fFPS;
	}

public : 
	bool Init();
	void Update();

	DECLARE_SINGLE(CTimer)
};

