#pragma once
#include "CScene.h"

class CStartScene :
    public CScene
{
private:
	friend class CSceneManager; // �� �Ŵ����� �� Ŭ������ ���� �����ϴ�.

private:
	CStartScene();
	~CStartScene();

public:
	virtual bool Init();
};

