#pragma once

#include "../Game.h"

// 실제 장면을 담당하는 장면 클래스의 베이스 클래스이다.
// 이 클래스의 하위로는 레이어가 있다.
class CScene
{
protected:
	friend class CSceneManager;	// 씬 매니저만 이 클래스에 접근 가능하다.

protected : 
	CScene();
	virtual ~CScene() = 0;	// 순수 가상함수로!

public : 
	virtual bool Init();
};

