#pragma once
#include "../Game.h"

// 프레임간 시간을 측정하기 위해 있는 클래스이다.
class CTimer
{
private : 
	HWND			m_hWnd;
	LARGE_INTEGER	m_tSecond;
	LARGE_INTEGER	m_tTime;
	float			m_fDeltaTime;
	float			m_fTimeScale;
	float			m_fFPS;
	float			m_fFPSTime;
	int				m_nFrame;

public : 
	// m_fTimeScale이 적용된 Time값을 반환한다.
	float GetDeltaTime() const
	{
		return m_fDeltaTime * m_fTimeScale;
	}

	float GetTimeScale() const
	{
		return m_fTimeScale;
	}

	float GetFPS() const
	{
		return m_fFPS;
	}

	void SetTimeScale(float fTimeScale)
	{
		this->m_fTimeScale = fTimeScale;
	}

public : 
	bool Init(HWND hWnd);
	void Update();

	DECLARE_SINGLE(CTimer)
};

