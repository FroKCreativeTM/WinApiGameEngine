#pragma once
#include "CScene.h"

class CStartScene :
    public CScene
{
private:
	friend class CSceneManager; // 씬 매니저만 이 클래스에 접근 가능하다.

private:
	CStartScene();
	~CStartScene();

public:
	virtual bool Init();
};

