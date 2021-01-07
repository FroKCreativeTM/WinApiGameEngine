#include "CTimer.h"

DEFINITION_SINGLE(CTimer)

CTimer::CTimer() : 
	m_fTimeScale(1.f)
{
}

CTimer::~CTimer() 
{
}

bool CTimer::Init(HWND hWnd)
{
	QueryPerformanceFrequency(&m_tSecond); 
	QueryPerformanceCounter(&m_tTime);

	m_fDeltaTime = 0.0f;
	m_fFPS = 0.0f;
	m_fFPSTime = 0.0f;
	m_nFrame = 0;

	m_hWnd = hWnd;

	return true;
}

void CTimer::Update()
{
	LARGE_INTEGER tTime;
	QueryPerformanceCounter(&tTime);

	// 델타타임(시간의 변화량) 공식
	m_fDeltaTime = (tTime.QuadPart - m_tTime.QuadPart)
		/ (float)m_tSecond.QuadPart;

	m_tTime = tTime;
	
	// 1 이상 되면 1초가 지난 것
	m_fFPSTime += m_fDeltaTime;
	++m_nFrame;

	// 1초란 보장 불가
	if (m_fFPSTime >= 1.f)
	{
		m_fFPS = m_nFrame / m_fFPSTime;
		m_fFPSTime = 0.f;
		m_nFrame = 0;

#ifdef _DEBUG
		char strFPS[64] = {};
		sprintf_s(strFPS, "FPS : %.f\n", m_fFPS);
		SetWindowTextA(m_hWnd, strFPS);
		// 디버그 콘솔에 프린팅한다.
		OutputDebugStringA(strFPS);
#endif
	}
}