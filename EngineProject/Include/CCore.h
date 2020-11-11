#pragma once

#include "Game.h"

// ������ �ھ�
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

// �̱���! 
// static�̶� �ᱹ�� ��������ȭ�Ǵ� �� �� ����!(��Ƽ������ �󿡼� Ư����)
// �޸� ���� ����! ���α׷� ������ ��
private : 
	static CCore*	m_pInstance;
	static bool		m_bLoop;

// API ���� �������
private : 
	HINSTANCE		m_hInst;
	HWND			m_Hwnd;
	RESOLUTION		m_tRS;

// �ܺ� ������ �ʿ� ���� �޼ҵ��
private : 
	ATOM MyRegisterClass();
	BOOL Create();
	void Logic();

// �ܺο��� �޸� �ǵ��� ���ϰ�.
private : 
	CCore();
	~CCore();
};

