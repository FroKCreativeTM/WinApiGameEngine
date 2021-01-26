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
	friend class CSceneManager; // �� �Ŵ����� �� Ŭ������ ���� �����ϴ�.

private:
	CStartScene();
	~CStartScene();
};

