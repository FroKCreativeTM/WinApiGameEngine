#pragma once

#include "Game.h"

// 게임의 코어
class CCore
{
public : 
	static CCore* GetInst();
	static void DestroyInst();

public : 
	bool Init(HINSTANCE hInstance);
	int Run();

public : 
	// 해상도 반환
	RESOLUTION GetResolution() const
	{
		return m_tRS;
	}

	// 윈도우 핸들 반환
	HWND GetWindowHandle() const
	{
		return m_hWnd;
	}

	// 윈도우 종료 함수
	void DestroyGame()
	{
		DestroyWindow(m_hWnd);
	}

public : 
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// 싱글톤! 
// static이라 결국은 전역변수화되니 이 점 주의!(멀티스레드 상에선 특히나)
// 메모리 생성 시점! 프로그램 시작할 때
private : 
	static CCore*	m_pInstance;
	static bool		m_bLoop;

// API 관련 멤버변수
private : 
	HINSTANCE		m_hInst;
	HWND			m_hWnd;
	RESOLUTION		m_tRS;
	HDC				m_hDC;

// 외부 공개할 필요 없는 메소드들
private : 
	ATOM MyRegisterClass();
	BOOL Create();

private : 
	void Logic();
	// 전부 시간 기반 처리다.
	void Input(float fDeltaTime);	
	int Update(float fDeltaTime);
	// 업데이트가 끝난 상태로 (충돌 전에) 후처리가 필요한 경우
	int LateUpdate(float fDeltaTime); 
	void Collision(float fDeltaTime);
	void Render(float fDeltaTime);


// 외부에서 메모리 건들지 못하게.
private : 
	CCore();
	~CCore();
};

