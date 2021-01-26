#pragma once
#include "../Game.h"

// �����Ӱ� �ð��� �����ϱ� ���� �ִ� Ŭ�����̴�.
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
	// m_fTimeScale�� ����� Time���� ��ȯ�Ѵ�.
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

