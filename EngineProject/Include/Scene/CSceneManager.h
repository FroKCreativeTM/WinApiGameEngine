#pragma once

#include "../Game.h"

// 서브 관리자 객체기 때문에
// 싱글톤으로 생성할 것.
class CSceneManager
{
public : 
	bool Init();

	DECLARE_SINGLE(CSceneManager)
};

