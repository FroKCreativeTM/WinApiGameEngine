#pragma once

#include "CScene.h"

class CInGameScene : 
	public CScene
{
private : 
	friend class CSceneManager; // �� �Ŵ����� �� Ŭ������ ���� �����ϴ�.

private : 
	CInGameScene();
	~CInGameScene();

public :
	virtual bool Init();
};

