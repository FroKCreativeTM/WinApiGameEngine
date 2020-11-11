#pragma once

#include "../Game.h"

// ���� ����� ����ϴ� ��� Ŭ������ ���̽� Ŭ�����̴�.
// �� Ŭ������ �����δ� ���̾ �ִ�.
class CScene
{
protected:
	friend class CSceneManager;	// �� �Ŵ����� �� Ŭ������ ���� �����ϴ�.

protected : 
	CScene();
	virtual ~CScene() = 0;	// ���� �����Լ���!

public : 
	virtual bool Init();
};

