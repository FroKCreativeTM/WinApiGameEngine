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
	HWND			m_Hwnd;
	RESOLUTION		m_tRS;

// 외부 공개할 필요 없는 메소드들
private : 
	ATOM MyRegisterClass();
	BOOL Create();
	void Logic();

// 외부에서 메모리 건들지 못하게.
private : 
	CCore();
	~CCore();
};

