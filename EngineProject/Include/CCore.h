#pragma once

#include "Game.h"

// ������ �ھ�
class CCore
{
public : 
	static CCore* GetInst();
	static void DestroyInst();

// �̱���! 
// static�̶� �ᱹ�� ��������ȭ�Ǵ� �� �� ����!(��Ƽ������ �󿡼� Ư����)
// �޸� ���� ����! ���α׷� ������ ��
private : 
	static CCore* m_pInstance;

// �ܺο��� �޸� �ǵ��� ���ϰ�.
private : 
	CCore();
	~CCore();
};

