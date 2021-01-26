#pragma once
#include "CScene.h"

class CStartScene :
    public CScene
{
public:
	virtual bool Init();

public :
	void StartButtonCallback(float fDeltaTime);
	void EditButtonCallback(float fDeltaTime);
	void EndButtonCallback(float fDeltaTime);

private:
	friend class CSceneManager; // 씬 매니저만 이 클래스에 접근 가능하다.

private:
	CStartScene();
	~CStartScene();
};

