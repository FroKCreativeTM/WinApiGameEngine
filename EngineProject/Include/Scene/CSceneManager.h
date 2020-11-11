#pragma once

#include "../Game.h"

// 서브 관리자 객체기 때문에
// 싱글톤으로 생성할 것.
class CSceneManager
{
private : 
	class CScene* m_pScene;
	class CScene* m_pNextScene;	// 장면 전환용 장면

public : 
	bool Init();

public : 
	template <typename T>
	T* CreateScene(SCENE_CREATE sc)
	{
		T* pScene = new T;

		if (!pScene->Init())
		{
			SAFE_DELETE(pScene);
			return nullptr;
		}

		// 장면을 전환한다.
		switch (sc)
		{
		case SC_CURRENT:
			SAFE_DELETE(m_pScene);
			m_pScene = pScene;
			break;
		case SC_NEXT:
			SAFE_DELETE(m_pNextScene);
			m_pNextScene = pScene;
			break;
		}

		return pScene;
	}

	DECLARE_SINGLE(CSceneManager)
};
