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
	HWND			m_hWnd;
	RESOLUTION		m_tRS;
	HDC				m_hDC;

// �ܺ� ������ �ʿ� ���� �޼ҵ��
private : 
	ATOM MyRegisterClass();
	BOOL Create();

private : 
	void Logic();
	// ���� �ð� ��� ó����.
	void Input(float fDeltaTime);	
	int Update(float fDeltaTime);
	// ������Ʈ�� ���� ���·� (�浹 ����) ��ó���� �ʿ��� ���
	int LateUpdate(float fDeltaTime); 
	void Collision(float fDeltaTime);
	void Render(float fDeltaTime);


// �ܺο��� �޸� �ǵ��� ���ϰ�.
private : 
	CCore();
	~CCore();
};

