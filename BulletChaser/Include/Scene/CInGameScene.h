#pragma once

#include "CScene.h"

class CInGameScene : 
	public CScene
{
private : 
	friend class CSceneManager; // 씬 매니저만 이 클래스에 접근 가능하다.

private : 
	CInGameScene();
	~CInGameScene();

public :
	virtual bool Init();
};

